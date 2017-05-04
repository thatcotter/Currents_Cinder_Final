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
    fullScale = 0.8f;
    smallScale = 0.4f;
    
    mImage -> setPosition(currentPos);
    mImage -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    
    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&Bones::onMouseEvent, this, std::placeholders::_1));
}

void Bones::mouseDrag(vec2 _mousePos){
    mousePos = _mousePos;
    if (isDrag) {
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
    int threshold = 100;
    if(!isDrag){
        if(distance < threshold){
            currentPos = targetPos;
            isPlaced = true;
        }
    }
    
    if (isPlaced) {
        cout << "Correct" << endl;
        mImage -> setFillColor(ci::Color(0.2f,0.2f,0.2f));
    }
}

void Bones::update(vec2 _mousePos){
    mouseDrag(_mousePos);
    toTarget();
    display();
    if (currentPos.y < 600) {
//        cout << "Bigger" << endl;
        ci::app::timeline().apply(&mImage->getScaleAnim(), vec2(1.f,1.f), mAnimationTime,ci::EaseOutExpo());
    }else{
        ci::app::timeline().apply(&mImage->getScaleAnim(), vec2(0.5f,0.5f), mAnimationTime,ci::EaseOutExpo());
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