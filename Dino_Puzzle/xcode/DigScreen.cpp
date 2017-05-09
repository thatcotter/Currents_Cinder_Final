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
    rows = 25;
    cols = 45;
    
    mRand = Rand();
    
    brown = Color( CM_HSV, 0.04, 0.24, 0.26 ) - Color( 0, 0, 0);
    
    for (int i = 0; i < cols + 10; i++) {
        std::vector<vec2> tempGridCol;
        std::vector<Color> tempHueCol;
        for (int j = 0; j < rows + 10; j++) {
            vec2 tempPoint = vec2( getWindowWidth()/cols * i,
                                  getWindowHeight()/rows * j);
            Color tempHue = Color( brown + Color(CM_HSV, 0.f,0.f,(mRand.nextFloat()*0.8f)-0.4f) );
            tempGridCol.push_back(tempPoint);
            tempHueCol.push_back(tempHue);
        }
        grid.push_back(tempGridCol);
        hues.push_back(tempHueCol);
    }
    
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            mParticles.push_back(Particle::create( grid[i][j], hues[i][j]));
        }
    }
    
    cout << "Particles: " << mParticles.size() << endl;
    
    mRepulsionFactor = 0.05f;
    
    grid.clear();
    hues.clear();
}

void DigScreen::mouseDown(ci::app::MouseEvent event)
{
    this->repulseFrom(event.getPos());
}

void DigScreen::repulseFrom(glm::vec2 position)
{
    // repulse function
    for (auto& p : mParticles){
        float distanceDiff = ci::length(p->getPosition() - position);
        if (distanceDiff < 20.f){
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

void DigScreen::update()
{
//    bounceFromEdge();
    for (auto& p : mParticles){
        p->update();
    }
}

void DigScreen::draw()
{
    gl::color(brown);
    Rectf rect( 0, 0, getWindowWidth(), getWindowHeight() );
    gl::drawSolidRect(rect);
    
//    for (int i = 0; i < grid.size(); i++) {
//        for (int j = 0; j < grid[i].size(); j++) {
//            gl::color( hues[i][j] );
//            Rectf drawrect(grid[i][j].x, grid[i][j].y, grid[i][j].x+6, grid[i][j].y+6);
//            gl::drawSolidRect(drawrect);
//            
//        }
//    }
    
    for (auto& p : mParticles){
        p->draw();
    }
    
}
