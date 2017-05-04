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
,head1Founded(true)
,head2Founded(true)
,backlegsFounded(true)
,frontlegsFounded(true)
,midspineFounded(true)
,tailFounded(true)
{
}

void AssemblyScene::setup(float _width, float _height){
    mWidth = _width;
    mHeight = _height;
    setbackground();
    
    BonesRef head1, head2, backlegs, frontlegs, midspine, tail;
    
    head1 = Bones::create("head1.png",vec2(150.f,680.f),vec2(1000.f,230.f),head1Founded);
    head2 = Bones::create("head2.png",vec2(320.f,680.f),vec2(1040.f,335.f),head2Founded);
    backlegs = Bones::create("backlegs.png",vec2(500.f,680.f),vec2(540.f,380.f),backlegsFounded);
    frontlegs = Bones::create("frontlegs.png",vec2(700.f,680.f),vec2(778.f,344.f),frontlegsFounded);
    midspine = Bones::create("midspine.png",vec2(900.f,680.f),vec2(645.f,230.f),midspineFounded);
    tail = Bones::create("tail.png",vec2(1100.f,680.f),vec2(310.f,260.f),tailFounded);
    
    mBones.push_back(head1);
    mBones.push_back(head2);
    mBones.push_back(backlegs);
    mBones.push_back(frontlegs);
    mBones.push_back(midspine);
    mBones.push_back(tail);
    
    setBones();
    instruction();
}

void AssemblyScene::instruction(){
    
    finger = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset("finger.png")));
    mFinger = po::scene::Image::create(finger);
    addChild(mFinger);
    
    mFinger -> setPosition(150.f,680.f);
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
    }
}

void AssemblyScene::update(vec2 _mousePos){
    for (int i=0; i<mBones.size(); i++) {
        mBones[i]-> update(_mousePos);
    }
}
