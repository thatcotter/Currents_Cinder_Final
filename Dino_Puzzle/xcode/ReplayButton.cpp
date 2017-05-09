//
//  ReplayButton.cpp
//  Dino_Puzzle
//
//  Created by Danli Hu on 5/9/17.
//
//

#include "ReplayButton.hpp"

ReplayButtonRef ReplayButton::create(){
    ReplayButtonRef ref = std::shared_ptr<ReplayButton>(new ReplayButton());
    ref->setup();
    return ref;
}

ReplayButton::ReplayButton()
:mRadius(0.f)
,mLength(0.f)
,mColor(ci::Color::white())
,mActiveColor(ci::Color::white())
,mIsActivated(false)
{
}

void ReplayButton::setup(){
    mRadius = 30.f;
    mLength = 60.f;
    mColor = ci::Color::hex(0xffde6d);
    mActiveColor = ci::Color::hex(0xffca16);
    
    addShape();
    
    getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&ReplayButton::onMouseEvent, this, std::placeholders::_1));
    
    std::string s = "REPLAY";
    ci::TextBox ciTextBox = ci::TextBox();
    ciTextBox.size(180.f,30.f);
    ciTextBox.color(ci::Color(1, 1, 1));
    ciTextBox.text(s);
    ciTextBox.alignment(ci::TextBox::Alignment::CENTER);
    ciTextBox.font(ci::Font("Chalkboard", 30));
    
    mText = po::scene::TextBox::create(ciTextBox);
//    mText -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    mText -> setPosition(0.f,8.f);
    
    addChild(mText);
}

void ReplayButton::onMouseEvent(po::scene::MouseEvent &event){
    switch (event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
            mIsActivated = !mIsActivated;
            if (mIsActivated){
                ci::app::timeline().apply(&mCircleLeft->getFillColorAnim(), mActiveColor, 0.5f,ci::EaseOutExpo());
                ci::app::timeline().apply(&mCircleRight->getFillColorAnim(), mActiveColor, 0.5f,ci::EaseOutExpo());
                ci::app::timeline().apply(&mRect->getFillColorAnim(), mActiveColor, 0.5f,ci::EaseOutExpo());
                mToggleStateChangeSignal.emit(true);
            }else{
                ci::app::timeline().apply(&mCircleLeft->getFillColorAnim(), mColor, 0.5f,ci::EaseOutExpo());
                ci::app::timeline().apply(&mCircleRight->getFillColorAnim(), mColor, 0.5f,ci::EaseOutExpo());
                ci::app::timeline().apply(&mRect->getFillColorAnim(), mColor, 0.5f,ci::EaseOutExpo());
                mToggleStateChangeSignal.emit(false);
            }
            break;
        default:
            break;
    }
}

void ReplayButton::addShape(){
    mCircleLeft = po::scene::Shape::createCircle(mRadius * 2.f);
    mCircleRight = po::scene::Shape::createCircle(mRadius * 2.f);
    mRect = po::scene::Shape::createRect(mRadius * 2.f + mLength, mRadius * 2.f);
    
    mCircleLeft->setPosition(glm::vec2(0.f));
    mRect->setPosition(glm::vec2(mRadius, 0.f));
    mCircleRight->setPosition(glm::vec2(mRadius * 2.f + mLength, 0.f));
    
    mCircleRight->setFillColor(mColor);
    mRect->setFillColor(mColor);
    mCircleLeft->setFillColor(mColor);
    
    addChild(mCircleLeft);
    addChild(mRect);
    addChild(mCircleRight);
}