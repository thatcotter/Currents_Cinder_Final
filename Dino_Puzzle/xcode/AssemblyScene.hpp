//
//  AssemblyScene.hpp
//  Dino_Puzzle
//
//  Created by Danli Hu on 4/24/17.
//
//

#pragma once

#include "poNodeContainer.h"
#include "poShape.h"
#include "poImage.h"
#include "cinder/Signals.h"
#include "Bones.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

//check if piece is found
//position of the pieces

class AssemblyScene;

typedef std::shared_ptr<AssemblyScene> AssemblySceneRef;

class AssemblyScene: public po::scene::NodeContainer{
    
public:
    static AssemblySceneRef create(float _width, float _height);
    void update();
    
private:
    AssemblyScene();
    void setup(float _width, float _height);
    void setBones();
//    void loadImages();
//    void drag();
    void setbackground();
    
    bool head1Founded, head2Founded, backlegsFounded, frontlegsFounded, midspineFounded, tailFounded;
    
    //current position
//    vec2 head1Pos, head2Pos, backlegsPos, frontlegsPos, midspinePos, tailPos;
    
    //target position
//    vec2 head1Target, head2Target, backlegsTarget, frontlegsTarget, midspineTarget, tailTarget;
    
//    gl::TextureRef head1, head2, backlegs, frontlegs, midspine, tail;
    gl::TextureRef shadow;
    
    //background
    po::scene::ShapeRef mBgRect;
    po::scene::ImageRef mShadow;
    
//    po::scene::ImageRef mHead1, mHead2, mBacklegs, mFrontlegs, mMidspine, mTail;
//    vector<po::scene::ImageRef> Bones;
//    vector<bool> pieceFounded;
    
    float mWidth, mHeight;
    
    //add Bones Class
//    Bones mHead1, mHead2, mBacklegs, mFrontlegs, mMidspine, mTail;
    vector<Bones> Bones;
};