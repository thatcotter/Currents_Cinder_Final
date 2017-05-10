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
//    loadImages();
    setbackground();
    
    BonesRef head1, head2, backlegs, frontlegs, midspine, tail;
    
    head1 = Bones::create("head1.png",vec2(200.f,200.f),vec2(0.f,0.f));
//    head2 = Bones::create("head2.png",vec2(0.f,0.f),vec2(0.f,0.f));
//    backlegs = Bones::create("backlegs.png",vec2(0.f,0.f),vec2(0.f,0.f));
//    frontlegs = Bones::create("frontlegs.png",vec2(0.f,0.f),vec2(0.f,0.f));
//    midspine = Bones::create("midspine.png",vec2(0.f,0.f),vec2(0.f,0.f));
//    tail = Bones::create("tail.png",vec2(0.f,0.f),vec2(0.f,0.f));
    
    mBones.push_back(head1);
//    mBones.push_back(head2);
//    mBones.push_back(backlegs);
//    mBones.push_back(frontlegs);
//    mBones.push_back(midspine);
//    mBones.push_back(tail);
}

void AssemblyScene::setbackground(){
    
    shadow = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset("shadow.png")));

    mBgRect = po::scene::Shape::createRect(mWidth,mHeight);
    mBgRect -> setPosition(vec2(0.f,0.f));
    mBgRect -> setFillColor(Color(0.8f,0.8f,0.8f));
    addChild(mBgRect);
    
    mShadow = po::scene::Image::create(shadow);
    mShadow -> setScale(0.4f);
    mShadow -> setPosition(vec2(mWidth/2, mHeight/2-80));
    mShadow -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    addChild(mShadow);
    
}

void AssemblyScene::update(vec2 _mousePos){
    for (int i=0; i<mBones.size(); i++) {
        mBones[i]-> update(_mousePos);
    }
}
