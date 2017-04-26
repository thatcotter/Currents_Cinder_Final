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
    for (int i=0; i<6; i++) {
        <#statements#>
    }
    
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

//void AssemblyScene::loadImages(){
//    try {
//        head1 = gl::Texture::create(loadImage(loadAsset("head1.png")));
//        head2 = gl::Texture::create(loadImage(loadAsset("head2.png")));
//        backlegs = gl::Texture::create(loadImage(loadAsset("backlegs.png")));
//        frontlegs = gl::Texture::create(loadImage(loadAsset("frontlegs.png")));
//        midspine = gl::Texture::create(loadImage(loadAsset("midspine.png")));
//        tail = gl::Texture::create(loadImage(loadAsset("tail.png")));
//    } catch (exception &e) {
//        ci::app::console()<< e.what()<<std::endl; //cout
//    }
//    
//    mHead1 = po::scene::Image::create(head1);
//    mHead2 = po::scene::Image::create(head2);
//    mBacklegs = po::scene::Image::create(backlegs);
//    mFrontlegs = po::scene::Image::create(frontlegs);
//    mMidspine = po::scene::Image::create(midspine);
//    mTail = po::scene::Image::create(tail);
//}
//
//void AssemblyScene::setBones(){
//    
//    po::scene::ImageRef Bones[] = {mHead1, mHead2, mBacklegs, mFrontlegs, mMidspine, mTail};
//    bool pieceFounded[] = {head1Founded, head2Founded, backlegsFounded, frontlegsFounded, midspineFounded, tailFounded};
//    
//    for (int i=0; i<6; i++) {
//        Bones[i] -> setScale(0.5f);
//        Bones[i] -> setAlignment(po::scene::Alignment::CENTER_CENTER);
//        Bones[i] -> setPosition(180*i+200, 650);
//        Bones[i] -> setVisible(false);
//        addChild(Bones[i]);
//        
//        if (pieceFounded[i] == true) {
//            Bones[i] -> setVisible(true);
//        }
//    }
//}

void AssemblyScene::update(){
    setBones();
}
