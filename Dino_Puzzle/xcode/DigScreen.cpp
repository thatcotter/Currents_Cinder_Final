//
//  DigScreen.cpp
//  Dino_Puzzle
//
//  Created by Andrew Cotter on 4/26/17.
//
//

#include "DigScreen.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;


DigScreenRef DigScreen::create()
{
    DigScreenRef ref = std::shared_ptr<DigScreen>( new DigScreen());
    ref->setup();
    return ref;
}

DigScreen::DigScreen()
{
    
}

void DigScreen::setup()
{
    rows = 12;
    cols = 12;
    
    auto img = ci::loadImage( ci::app::loadAsset("bg_rocks.png") );
    mTex = ci::gl::Texture2d::create(img);
    
    mRand = Rand();
    
    brown = Color( CM_HSV, 0.04, 0.24, 0.26 ) - Color( 0, 0, 0);
    
    for (int i = -2; i < cols + 5; i++) {
        std::vector<vec2> tempGridCol;
        std::vector<Color> tempHueCol;
        for (int j = -2; j < rows + 5; j++) {
            vec2 tempPoint = vec2( getWindowWidth()/cols * i,
                                  getWindowHeight()/rows * j);
            Color tempHue = Color( brown + Color(CM_HSV, 0.f,0.f,(mRand.nextFloat()*0.8f)-0.4f) );
            tempGridCol.push_back(tempPoint);
            tempHueCol.push_back(tempHue);
        }
        grid.push_back(tempGridCol);
        hues.push_back(tempHueCol);
    }
    
    std::string asset1 = "rockTex1.png";
    std::string asset2 = "rockTex2.png";
    std::string asset3 = "rockTex3.png";
    std::string asset4 = "rockTex4.png";
    std::string asset5 = "rockTex5.png";
    std::string asset6 = "rockTex6.png";
    std::string asset7 = "rockTex7.png";
    
    
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            
            std::string asset;
            
            int chance = int( mRand.nextInt(7));
            
            switch (chance) {
                case 0:
                    asset = asset1;
                    break;
                case 1:
                    asset = asset2;
                    break;
                case 2:
                    asset = asset3;
                    break;
                case 3:
                    asset = asset4;
                    break;
                case 4:
                    asset = asset5;
                    break;
                case 5:
                    asset = asset6;
                    break;
                case 6:
                    asset = asset7;
                    break;
                    
                default:
                    break;
            }
            
            
            mParticles.push_back(Particle::create( grid[i][j], asset));
        }
    }
    
    mRepulsionFactor = 0.05f;
    
    //make the bones
    BonesRef head1, head2, backlegs, frontlegs, midspine, tail;
    
    head1 = Bones::create("head1.png",vec2(200.f,200.f),vec2(0.f,0.f));
//    head1->isFound = true;
    
    mBones.push_back(head1);
    this->addChild(mBones[0]);
    
    //define textures
    auto head1Img = loadImage( loadAsset( "head1.png" ) );
    mHead = gl::Texture2d::create( head1Img );
    
    bonesTex.push_back(mHead);
    
    auto head2Img = loadImage( loadAsset( "head2.png" ) );
    mHead = gl::Texture2d::create( head2Img );
    
    bonesTex.push_back(mHead);
    
    auto backLegsImg = loadImage( loadAsset( "backlegs.png" ) );
    mHead = gl::Texture2d::create( backLegsImg );
    
    bonesTex.push_back(mHead);
    
    auto frontLegsImg = loadImage( loadAsset( "frontlegs.png" ) );
    mHead = gl::Texture2d::create( frontLegsImg );
    
    bonesTex.push_back(mHead);
    
    auto midspineImg = loadImage( loadAsset( "midspine.png" ) );
    mHead = gl::Texture2d::create( midspineImg );
    
    bonesTex.push_back(mHead);
    
    auto tailImg = loadImage( loadAsset( "tail.png" ) );
    mHead = gl::Texture2d::create( tailImg );
    
    bonesTex.push_back(mHead);
    
    
    //bone locations
    vec2 head1Pos, head2Pos, backlegsPos, frontlegsPos, midspinePos, tailPos;
    
    //    head1Pos = vec2( mRand.nextFloat(100, 1100), mRand.nextFloat( 100, 700));
    //    head2Pos = vec2( mRand.nextFloat(100, 1100), mRand.nextFloat( 100, 700));
    //    backlegsPos = vec2( mRand.nextFloat(100, 1100), mRand.nextFloat( 100, 700));
    //    frontlegsPos = vec2( mRand.nextFloat(100, 1100), mRand.nextFloat( 100, 700));
    //    midspinePos = vec2( mRand.nextFloat(100, 1100), mRand.nextFloat( 100, 700));
    //    tailPos = vec2( mRand.nextFloat(100, 1100), mRand.nextFloat( 100, 700));
    
    head1Pos = vec2( 900, 440);
    head2Pos = vec2( 900, 600);
    backlegsPos = vec2( 200, 200);
    frontlegsPos = vec2( 700, 600);
    midspinePos = vec2( 600, 300);
    tailPos = vec2( 400, 500);
    
    bonesPos.push_back(head1Pos);
    bonesPos.push_back(head2Pos);
    bonesPos.push_back(backlegsPos);
    bonesPos.push_back(frontlegsPos);
    bonesPos.push_back(midspinePos);
    bonesPos.push_back(tailPos);
    
    //size offsets
    
    int head1Off, head2Off, backlegsOff, frontlegsOff, midspineOff, tailOff;
    head1Off = 100;
    head2Off = 50;
    backlegsOff = 125;
    frontlegsOff = 125;
    midspineOff = 125;
    tailOff = 200;
    
    bonesOff.push_back(head1Off);
    bonesOff.push_back(head2Off);
    bonesOff.push_back(backlegsOff);
    bonesOff.push_back(frontlegsOff);
    bonesOff.push_back(midspineOff);
    bonesOff.push_back(tailOff);
    
    //set bools
    for (int i = 0; i < bonesTex.size(); i++) {
        bool temp = false;
        bonesFound.push_back(temp);
    }
    
    grid.clear();
    hues.clear();
    
    //brush
    brush = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset("brush.png")));
    
    ci::TextBox puzzleCompleteText0 = ci::TextBox();
    puzzleCompleteText0.size(700, 400);
    puzzleCompleteText0.color(ci::Color(1, 1, 1));
    std::string textComplete0 = "Bones Found:" + to_string(0) + "/6";
    puzzleCompleteText0.text(textComplete0);
    puzzleCompleteText0.font(ci::Font("Chalkboard", 40));
    
    completeText0 = po::scene::TextBox::create(puzzleCompleteText0);
    completeText0 -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    completeText0 -> setPosition(100.f,100.f);
    completeText0 -> setVisible(false);
    addChild(completeText0);
    
    ci::TextBox puzzleCompleteText1 = ci::TextBox();
    puzzleCompleteText1.size(700, 400);
    puzzleCompleteText1.color(ci::Color(1, 1, 1));
    std::string textComplete1 = "Bones Found:" + to_string(1) + "/6";
    puzzleCompleteText1.text(textComplete1);
    puzzleCompleteText1.font(ci::Font("Chalkboard", 40));
    
    completeText1 = po::scene::TextBox::create(puzzleCompleteText1);
    completeText1 -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    completeText1 -> setPosition(100.f,100.f);
    completeText1 -> setVisible(false);
    addChild(completeText1);
    //
    ci::TextBox puzzleCompleteText2 = ci::TextBox();
    puzzleCompleteText2.size(700, 400);
    puzzleCompleteText2.color(ci::Color(1, 1, 1));
    std::string textComplete2 = "Bones Found:" + to_string(2) + "/6";
    puzzleCompleteText2.text(textComplete2);
    puzzleCompleteText2.font(ci::Font("Chalkboard", 40));
    
    completeText2 = po::scene::TextBox::create(puzzleCompleteText2);
    completeText2 -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    completeText2 -> setPosition(100.f,100.f);
    completeText2 -> setVisible(false);
    addChild(completeText2);
    
    ci::TextBox puzzleCompleteText3 = ci::TextBox();
    puzzleCompleteText3.size(700, 400);
    puzzleCompleteText3.color(ci::Color(1, 1, 1));
    std::string textComplete3 = "Bones Found:" + to_string(3) + "/6";
    puzzleCompleteText3.text(textComplete3);
    puzzleCompleteText3.font(ci::Font("Chalkboard", 40));
    
    completeText3 = po::scene::TextBox::create(puzzleCompleteText3);
    completeText3 -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    completeText3 -> setPosition(100.f,100.f);
    completeText3 -> setVisible(false);
    addChild(completeText3);
    
    ci::TextBox puzzleCompleteText4 = ci::TextBox();
    puzzleCompleteText4.size(700, 400);
    puzzleCompleteText4.color(ci::Color(1, 1, 1));
    std::string textComplete4 = "Bones Found:" + to_string(4) + "/6";
    puzzleCompleteText4.text(textComplete4);
    puzzleCompleteText4.font(ci::Font("Chalkboard", 40));
    
    completeText4 = po::scene::TextBox::create(puzzleCompleteText4);
    completeText4 -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    completeText4 -> setPosition(100.f,100.f);
    completeText4 -> setVisible(false);
    addChild(completeText4);
    //
    ci::TextBox puzzleCompleteText5 = ci::TextBox();
    puzzleCompleteText5.size(700, 400);
    puzzleCompleteText5.color(ci::Color(1, 1, 1));
    std::string textComplete5 = "Bones Found:" + to_string(5) + "/6";
    puzzleCompleteText5.text(textComplete5);
    puzzleCompleteText5.font(ci::Font("Chalkboard", 40));
    
    completeText5 = po::scene::TextBox::create(puzzleCompleteText5);
    completeText5 -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    completeText5 -> setPosition(100.f,100.f);
    completeText5 -> setVisible(false);
    addChild(completeText5);
    
    ci::TextBox puzzleCompleteText6 = ci::TextBox();
    puzzleCompleteText6.size(700, 400);
    puzzleCompleteText6.color(ci::Color(1, 1, 1));
    std::string textComplete6 = "Bones Found:" + to_string(6) + "/6";
    puzzleCompleteText6.text(textComplete6);
    puzzleCompleteText6.font(ci::Font("Chalkboard", 40));
    
    completeText6 = po::scene::TextBox::create(puzzleCompleteText6);
    completeText6 -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    completeText6 -> setPosition(100.f,100.f);
    completeText6 -> setVisible(false);
    addChild(completeText6);
}

void DigScreen::mouseDown(ci::app::MouseEvent event)
{
    brushPos = vec2(event.getPos().x-55.f,event.getPos().y-50.f);
    this->repulseFrom(event.getPos());
}

void DigScreen::repulseFrom(glm::vec2 position)
{
    // repulse function
    for (auto& p : mParticles){
        float distanceDiff = ci::length(p->getPosition() - position);
        if (distanceDiff < 80.f){
            glm::vec2 repulsion = (p->getPosition() - position) * mRepulsionFactor;
            //            cout << "repulsion: " << repulsion << endl;
            p->applyForce(repulsion);
        }
    }
}

void DigScreen::bounceFromEdge()
{
    for (auto& p : mParticles){
        // define reaction when hit wall
        if (p->getPosition().x <= 0.f || p->getPosition().x >= ci::app::getWindowWidth()){
            p->bounceForce(0.95, false);
        }
        
        if (p->getPosition().y <= 0.f || p->getPosition().y >= ci::app::getWindowHeight()){
            p->bounceForce(0.95, true);
        }
    }
}

void DigScreen::checkFound()
{
    
    for (int i = 0; i < bonesPos.size(); i++) {
        int num = 0;
        for (int j = 0; j < mParticles.size(); j++) {
            float distanceDiff = ci::length( bonesPos[i]-mParticles[j]->getPos() );
            if (distanceDiff > 100.f) {
                num++;
            }
        }
        if (num >= mParticles.size()) {
            bonesFound[i] = true;
//            cout << "Found bone " << i << endl;
        }
    }
    
}

void DigScreen::updateText()
{
    int found = 0;
    for (int i = 0; i < bonesFound.size(); i++) {
        if (bonesFound[i]) {
            found++;
            //            completeText->setVisible(true);
        }
    }
    switch (found) {
        case 0:
            completeText0->draw();
            break;
        case 1:
            completeText1->draw();
            break;
        case 2:
            completeText2->draw();
            break;
        case 3:
            completeText3->draw();
            break;
        case 4:
            completeText4->draw();
            break;
        case 5:
            completeText5->draw();
            break;
        case 6:
            completeText6->draw();
            break;
            
        default:
            break;
    }
}

void DigScreen::update(vec2 _MousePos)
{
//    brushPos = _MousePos;
    
    //    bounceFromEdge();
    checkFound();
    for (auto& p : mParticles){
        p->update();
    }
}


void DigScreen::draw()
{
    Rectf destRect = Rectf(0,0,1280,1024);
    gl::draw(mTex, Area(destRect.getCenteredFit(mTex->getBounds(), true)), destRect);
    
    
    for ( int i = 0; i < bonesTex.size(); i++) {
        Rectf destRectHead = Rectf(bonesPos[i].x-bonesOff[i],bonesPos[i].y-bonesOff[i],bonesPos[i].x+bonesOff[i],bonesPos[i].y+bonesOff[i]);
        gl::draw(bonesTex[i], Rectf(bonesTex[i]->getBounds()).getCenteredFit(destRectHead, true));
    }
    
    for (auto& p : mParticles){
        p->draw();
    }
    
    gl::pushModelMatrix();
    
    gl::translate(vec2(100, 600));
    updateText();
    
    gl::popModelMatrix();
    
    gl::draw(brush,brushPos);
    
    
}

