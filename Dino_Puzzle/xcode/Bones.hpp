//
//  Bones.hpp
//  DinoPuzzle_Assembly_test
//
//  Created by Danli Hu on 4/26/17.
//
//

#pragma once

#include "poNodeContainer.h"
#include "poShape.h"
#include "poImage.h"
#include "cinder/Signals.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Bones;

typedef std::shared_ptr<Bones> BonesRef;

class Bones: public po::scene::NodeContainer{
public:
    Bones();
    static BonesRef create(fs::path _path,vec2 _currentPos,vec2 _targetPos);
    void update(vec2 _mousePos);
    void display();
    
private:
    void setup(fs::path _path,vec2 _currentPos,vec2 _targetPos);
    void loadImage(fs::path _pathf);
    void mouseDrag(vec2 _mousePos);
    void onMouseEvent(po::scene::MouseEvent &event);
    void toTarget();
    
    bool isFound;
    bool isDrag;
    bool isPlaced;
    vec2 currentPos;
    vec2 targetPos;
    vec2 mousePos;
    gl::TextureRef mTexture;
    po::scene::ImageRef mImage;
};