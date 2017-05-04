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
    void update(vec2 _mousePos);
    void getMousePos(vec2 _mousePos);
    
private:
    AssemblyScene();
    void setup(float _width, float _height);
    void setBones();
    void setbackground();
    void instruction();
    void ifDragHideInstruction();
    
    bool head1Founded, head2Founded, backlegsFounded, frontlegsFounded, midspineFounded, tailFounded;

    gl::TextureRef shadow;
    gl::TextureRef finger;
    
    //background
    po::scene::ShapeRef mBgRect;
    po::scene::ImageRef mShadow;
    po::scene::ImageRef mFinger;
    
    float mWidth, mHeight;
    vec2 mousePos;
    //Bone Class
    vector<BonesRef> mBones;
};