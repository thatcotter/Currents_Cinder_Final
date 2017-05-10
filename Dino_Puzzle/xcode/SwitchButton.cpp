//
//  SwitchButton.cpp
//  Dino_Puzzle
//
//  Created by Danli Hu on 5/10/17.
//
//

#include "SwitchButton.hpp"

SwitchButtonRef SwitchButton::create(std::string _text){
    SwitchButtonRef ref = std::shared_ptr<SwitchButton>(new SwitchButton());
    ref->setup(_text);
    return ref;
}

SwitchButton::SwitchButton()
:mRadius(0.f)
,mColor(ci::Color::white())
,mActiveColor(ci::Color::white())
,mIsActivated(false)
{
}

void SwitchButton::setup(std::string _text){
    mRadius = 30.f;
    mColor = ci::Color::hex(0xffca16);
//    mActiveColor = ci::Color::hex(0xffca16);
    
    getSignal(po::scene::MouseEvent::UP_INSIDE).connect(std::bind(&SwitchButton::onMouseEvent, this, std::placeholders::_1));

    ci::TextBox ciTextBox = ci::TextBox();
    ciTextBox.size(200.f,75.f);
    ciTextBox.color(ci::Color(1, 1, 1));
    ciTextBox.text(_text);
    ciTextBox.alignment(ci::TextBox::Alignment::CENTER);
    ciTextBox.font(ci::Font("Chalkboard", 50));
    
    mText = po::scene::TextBox::create(ciTextBox);
    mText -> setPosition(0.f,0.f);
    mText -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    
    addShape();
    addChild(mText);
}

void SwitchButton::onMouseEvent(po::scene::MouseEvent &event){
    switch (event.getType()) {
        case po::scene::MouseEvent::UP_INSIDE:
            mIsActivated = !mIsActivated;
            if (mIsActivated){
//                ci::app::timeline().apply(&mCircle->getFillColorAnim(), mActiveColor, 0.5f,ci::EaseOutExpo());
                mSwitchButtonChangeSignal.emit(true);
            }else{
//                ci::app::timeline().apply(&mCircle->getFillColorAnim(), mColor, 0.5f,ci::EaseOutExpo());
                mSwitchButtonChangeSignal.emit(false);
            }
            break;
            
        default:
            break;
    }
}

void SwitchButton::addShape(){
    mCircle = po::scene::Shape::createCircle(mRadius * 2.f);
    mCircle -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    mCircle->setPosition(0.f,0.f);
    mCircle->setFillColor(mColor);
    addChild(mCircle);

}