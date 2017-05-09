//
//  ReplayButton.hpp
//  Dino_Puzzle
//
//  Created by Danli Hu on 5/9/17.
//
//

#pragma once

#include "poNodeContainer.h"
#include "poShape.h"
#include "poTextBox.h"

#include "cinder/Signals.h"

class ReplayButton;
typedef std::shared_ptr<ReplayButton> ReplayButtonRef;
typedef ci::signals::Signal<void(bool state)> ToggleStateChangeSignal;

class ReplayButton : public po::scene::NodeContainer{
public:
    static ReplayButtonRef create();
    ToggleStateChangeSignal& getToggleStateChangeSignal(){return mToggleStateChangeSignal;}
    
private:
    ReplayButton();
    
    void setup();
    void onMouseEvent(po::scene::MouseEvent &event);
    void addShape();
    po::scene::ShapeRef mCircleLeft;
    po::scene::ShapeRef mCircleRight;
    po::scene::ShapeRef mRect;
    po::scene::TextBoxRef mText;

    
    float mRadius;
    float mLength;
    ci::Color mColor;
    ci::Color mActiveColor;
    
    ToggleStateChangeSignal mToggleStateChangeSignal;
    
    bool mIsActivated;
};