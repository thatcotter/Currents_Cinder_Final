//
//  SwitchButton.hpp
//  Dino_Puzzle
//
//  Created by Danli Hu on 5/10/17.
//
//

#pragma once

#include "poNodeContainer.h"
#include "poShape.h"
#include "poTextBox.h"

#include "cinder/Signals.h"

class SwitchButton;
typedef std::shared_ptr<SwitchButton> SwitchButtonRef;
typedef ci::signals::Signal<void(bool state)> SwitchButtonChangeSignal;

class SwitchButton : public po::scene::NodeContainer{
public:
    static SwitchButtonRef create(std::string _text);
    SwitchButtonChangeSignal& getSwitchButtonChangeSignal(){return mSwitchButtonChangeSignal;}
    
private:
    SwitchButton();
    
    void setup(std::string _text);
    void onMouseEvent(po::scene::MouseEvent &event);
    void addShape();
    po::scene::ShapeRef mCircle;
    po::scene::TextBoxRef mText;
    
    
    float mRadius;
    ci::Color mColor;
    ci::Color mActiveColor;
    
    SwitchButtonChangeSignal mSwitchButtonChangeSignal;
    
    bool mIsActivated;
};