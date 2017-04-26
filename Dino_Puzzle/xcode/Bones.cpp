//
//  Bones.cpp
//  DinoPuzzle_Assembly_test
//
//  Created by Danli Hu on 4/26/17.
//
//

#include "Bones.hpp"

BonesRef Bones::create(string _path,vec2 _currentPos,vec2 _targetPos){
    BonesRef ref = std::shared_ptr<Bones>(new Bones());
    ref -> setup(_path, _currentPos, _targetPos);
    return ref;
}

Bones::Bones()
:isFound(false)
,isDrag(false)
,isPlaced(false)
,currentPos(vec2(0.f,0.f))
,targetPos(vec2(0.f,0.f))
{
}

void Bones::loadImage(string _path){
    try {
        imagePath = app::getAssetPath(_path);
        mTexture = gl::Texture::create(loadImage(loadAsset(imagePath)));
    } catch (exception &e) {
        ci::app::console() << e.what() << std::endl;
    }
    mImage = po::scene::Image::create(mTexture);
    addChild(mImage);
}

void Bones::setup(string _path,vec2 _currentPos,vec2 _targetPos){
    loadImage(_path);
    currentPos = _currentPos;
    targetPos = _targetPos;
    
    mImage -> setPosition(currentPos);
    mImage -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    
    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&Bar::onMouseEvent, this, std::placeholders::_1));
}

void Bones::mouseDrag(vec2 _mousePos){
    mousePos = _mousePos;
    if (isDrag) {
        currentPos = mousePos;
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
    int threshold = 10;
    if(!isDrag){
        if(distance < threshold){
            currentPos = targetPos;
            isPlaced = true;
        }
    }
}

void Bones::update(vec2 _mousePos){
    mouseDrag(_mousePos);
    toTarget();
}

void Bones::display(){
    mImage -> setVisible(false);
    
    if (isFound == true) {
        mImage -> setVisible(true);
    }
}