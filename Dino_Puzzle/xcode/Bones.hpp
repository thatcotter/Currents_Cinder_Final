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
#include "poTextBox.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Bones;

typedef std::shared_ptr<Bones> BonesRef;
typedef ci::signals::Signal<void(bool state)> BoneDragSignal;

class Bones: public po::scene::NodeContainer{
public:
    Bones();
    static BonesRef create(fs::path _path,vec2 _currentPos,vec2 _targetPos);
//    static BonesRef create(fs::path _path,vec2 _currentPos,vec2 _targetPos,bool _isFound);
    void update(vec2 _mousePos);
    void display();
    BoneDragSignal &getBoneDragSignal(){return mBoneDragSignal;}
    
    bool isFound;
    bool isPlaced;
private:
//    void setup(fs::path _path,vec2 _currentPos,vec2 _targetPos,bool _isFound);
    void setup(fs::path _path,vec2 _currentPos,vec2 _targetPos);
    void loadImage(fs::path _pathf);
    void mouseDrag(vec2 _mousePos);
    void onMouseEvent(po::scene::MouseEvent &event);
    void toTarget();
    
    bool isDrag;

    vec2 currentPos;
    vec2 targetPos;
    vec2 mousePos;
    gl::TextureRef mTexture;
    po::scene::ImageRef mImage;
    po::scene::TextBoxRef dragText;
    
    vector<std::string> dragTexts;
    ci::TextBox ciTextBox;
    
    float mAnimationTime;
    float fullScale, smallScale;
    
    BoneDragSignal mBoneDragSignal;
};