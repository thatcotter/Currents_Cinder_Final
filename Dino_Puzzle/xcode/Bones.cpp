//
//  Bones.cpp
//  DinoPuzzle_Assembly_test
//
//  Created by Danli Hu on 4/26/17.
//
//

#include "Bones.hpp"

BonesRef Bones::create(fs::path _path,vec2 _currentPos,vec2 _targetPos,bool _isFound){
    BonesRef ref = std::shared_ptr<Bones>(new Bones());
    ref -> setup(_path, _currentPos, _targetPos, _isFound);
    return ref;
}

Bones::Bones()
:isFound(true)
,isDrag(false)
,isPlaced(false)
,currentPos(vec2(0.f,0.f))
,targetPos(vec2(0.f,0.f))
{
}

void Bones::loadImage(fs::path _path){
    try {
        mTexture = gl::Texture::create(ci::loadImage(loadAsset(_path)));
    } catch (exception &e) {
        ci::app::console() << e.what() << std::endl;
    }
    mImage = po::scene::Image::create(mTexture);
    addChild(mImage);
}

void Bones::setup(fs::path _path,vec2 _currentPos,vec2 _targetPos,bool _isFound){
    loadImage(_path);
    currentPos = _currentPos;
    targetPos = _targetPos;
    isFound = _isFound;
    
    mAnimationTime = 0.2f;
    fullScale = 0.25f;
    smallScale = 0.15f;
    
    mImage -> setPosition(currentPos);
    mImage -> setScale(smallScale, smallScale);
    mImage -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    
    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&Bones::onMouseEvent, this, std::placeholders::_1));
    
    //Text
    ciTextBox = ci::TextBox();
    ciTextBox.size(300, 200);
    ciTextBox.color(ci::Color(1, 1, 1));
    
    std::string text1 = "Wow! What is it?";
    std::string text2 = "What a cool piece!";
    std::string text3 = "Look at what you've found!";
    std::string text4 = "Where to put it?";
    dragTexts.push_back(text1);
    dragTexts.push_back(text2);
    dragTexts.push_back(text3);
    dragTexts.push_back(text4);
    
    ciTextBox.font(ci::Font("Chalkboard", 20));
    
    int n = ci::randInt(0,4);
    if (n == 0) {
        ciTextBox.text(dragTexts[0]);
    }else if(n == 1){
        ciTextBox.text(dragTexts[1]);
    }else if(n == 2){
        ciTextBox.text(dragTexts[2]);
    }else{
        ciTextBox.text(dragTexts[3]);
    }
    
    dragText = po::scene::TextBox::create(ciTextBox);
}

void Bones::mouseDrag(vec2 _mousePos){
    mousePos = _mousePos;
    if (isDrag) {
        dragText -> setPosition(mousePos.x-50,mousePos.y+70);
        addChild(dragText);
        
        currentPos = mousePos;
        cout << currentPos << endl;
        mBoneDragSignal.emit(true);
    }
}

void Bones::onMouseEvent(po::scene::MouseEvent &event){
    
    switch (event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
            isDrag = !isDrag;
            break;
        default:
            break;
    }
}

void Bones::toTarget(){
    float distance = sqrt(((currentPos.x-targetPos.x)*(currentPos.x-targetPos.x))+((currentPos.y-targetPos.y)*(currentPos.y-targetPos.y)));
    int threshold = 30;
    if(!isDrag){
        if(distance < threshold){
            currentPos = targetPos;
            isPlaced = true;
        }
    }
    
    if (isPlaced) {
        cout << "Correct" << endl;
        mImage -> setFillColor(ci::Color(1.f,1.f,1.f));
    }else{
        mImage -> setFillColor(ci::Color(0.6f,0.6f,0.6f));
    }
}

void Bones::update(vec2 _mousePos){
    mouseDrag(_mousePos);
    toTarget();
    display();
    if (currentPos.y < 600) {
//        cout << "Bigger" << endl;
        ci::app::timeline().apply(&mImage->getScaleAnim(), vec2(0.25f,0.25f), mAnimationTime,ci::EaseOutExpo());
        ci::app::timeline().apply(&dragText->getAlphaAnim(), 0.f, mAnimationTime);
    }else{
        ci::app::timeline().apply(&mImage->getScaleAnim(), vec2(0.15f,0.15f), mAnimationTime,ci::EaseOutExpo());
    }
}

void Bones::display(){
    
    mImage -> setPosition(currentPos);
    mImage -> setVisible(false);
    mImage -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    
    if (isFound == true) {
        mImage -> setVisible(true);
    }
}