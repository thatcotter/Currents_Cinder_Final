//
//  DigScreen.cpp
//  Dino_Puzzle
//
//  Created by Andrew Cotter on 4/26/17.
//
//

#include "DigScreen.hpp"


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
    
}

void DigScreen::update()
{
    
}

void DigScreen::draw()
{
    
}
