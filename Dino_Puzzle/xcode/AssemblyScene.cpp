//
//  AssemblyScene.cpp
//  Dino_Puzzle
//
//  Created by Danli Hu on 4/24/17.
//
//

#include "AssemblyScene.hpp"

AssemblySceneRef AssemblyScene::create(float _width, float _height){
    AssemblySceneRef ref = std::shared_ptr<AssemblyScene>(new AssemblyScene());
    ref -> setup(_width, _height);
    return ref;
}

AssemblyScene::AssemblyScene()
:mWidth(0.f)
,mHeight(0.f)
{
}

void AssemblyScene::setup(float _width, float _height){
    mWidth = _width;
    mHeight = _height;
    setbackground();
    
    head1 = Bones::create("head1.png",vec2(150.f,730.f),vec2(1000.f,230.f));
    head2 = Bones::create("head2.png",vec2(320.f,730.f),vec2(1040.f,335.f));
    backlegs = Bones::create("backlegs.png",vec2(470.f,730.f),vec2(540.f,380.f));
    frontlegs = Bones::create("frontlegs.png",vec2(650.f,730.f),vec2(787.f,355.f));
    midspine = Bones::create("midspine.png",vec2(850.f,730.f),vec2(645.f,230.f));
    tail = Bones::create("tail.png",vec2(1100.f,730.f),vec2(379.f,217.f));
    
    mBones.push_back(head1);
    mBones.push_back(head2);
    mBones.push_back(backlegs);
    mBones.push_back(frontlegs);
    mBones.push_back(midspine);
    mBones.push_back(tail);
    
    setBones();
    instruction();
    
    //Complete text
    ci::TextBox puzzleCompleteText = ci::TextBox();
    puzzleCompleteText.size(700, 400);
    puzzleCompleteText.color(ci::Color(1, 1, 1));
    std::string textComplete = "That is a Stegasaur!!";
    puzzleCompleteText.text(textComplete);
    puzzleCompleteText.font(ci::Font("Chalkboard", 40));
    
    completeText = po::scene::TextBox::create(puzzleCompleteText);
    completeText -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    completeText -> setPosition(800.f,870.f);
    completeText -> setVisible(false);
    addChild(completeText);
    
    //Replay Button
    mReplayButton = ReplayButton::create();
    mReplayButton -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    mReplayButton -> setPosition(640.f,770.f);
    mReplayButton -> setVisible(false);
    addChild(mReplayButton);
    
    mReplayButton->getToggleStateChangeSignal().connect(std::bind(&AssemblyScene::onToggleStateChange, this, std::placeholders::_1));
}

void AssemblyScene::instruction(){
    
    finger = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset("finger.png")));
    mFinger = po::scene::Image::create(finger);
    addChild(mFinger);
    
    mFinger -> setPosition(150.f,730.f);
    mFinger -> setAlpha(0.f);
    ci::app::timeline().apply(&mFinger->getPositionAnim(), vec2(1000.f,230.f), 3.f,ci::EaseOutExpo()).delay(2.f);
    ci::app::timeline().apply(&mFinger->getAlphaAnim(), 1.f, 0.5f,ci::EaseOutExpo()).delay(1.f);
    
    for (int i=0; i<mBones.size(); i++) {
        mBones[i]-> getBoneDragSignal().connect(std::bind(&AssemblyScene::ifDragHideInstruction, this));;
    }
}

void AssemblyScene::ifDragHideInstruction(){
    ci::app::timeline().apply(&mFinger->getAlphaAnim(), 0.f, 0.5f,ci::EaseOutExpo()).finishFn([&](){
        mFinger -> setVisible(false);
    });
}


void AssemblyScene::setbackground(){
    
    shadow = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset("background.jpg")));

    mBgRect = po::scene::Shape::createRect(mWidth,mHeight);
    mBgRect -> setPosition(vec2(0.f,0.f));
    mBgRect -> setFillColor(Color(0.8f,0.8f,0.8f));
    addChild(mBgRect);
    
    mShadow = po::scene::Image::create(shadow);
    mShadow -> setPosition(vec2(0.f,0.f));
    addChild(mShadow);
}

void AssemblyScene::setBones(){
    for (int i=0; i<mBones.size(); i++) {
        addChild(mBones[i]);
        mBones[i]->setVisible(false);
    }
}

void AssemblyScene::displayBones(vector<bool> _found){
    for (int i=0; i<mBones.size(); i++) {
        if (_found[i] == 1) {
            mBones[i]->setVisible(true);
        }
    }
}

void AssemblyScene::update(vec2 _mousePos, vector<bool> _found){
    for (int i=0; i<mBones.size(); i++) {
        mBones[i]-> update(_mousePos);
    }
    
    displayBones(_found);
    
    if (head1->isPlaced && head2->isPlaced && backlegs->isPlaced && frontlegs->isPlaced && midspine->isPlaced && tail->isPlaced) {
        puzzleComplete();
    }
}

void AssemblyScene::puzzleComplete(){
    cout << "Puzzle Complete!" << endl;
    completeText -> setVisible(true);
    mReplayButton -> setVisible(true);
}

void AssemblyScene::onToggleStateChange(bool state)
{
    if(state){

    }else{

    }
}
