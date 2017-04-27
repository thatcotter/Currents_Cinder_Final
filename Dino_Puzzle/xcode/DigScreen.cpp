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

//DigScreen::DigScreen()
//{
//    
//}

void DigScreen::setup()
{
    try
    {
//        _dirtTexture = cinder::gl::Texture::create( loadImage( cinder::app::loadAsset( "it_me.jpg" ) ) );
//        _dirtSurface = loadImage( cinder::app::loadAsset( "it_me.jpg" ) );
        
    } catch (ci::Exception& e)
    {
        ci::app::console() << e.what() << std::endl;
    }
}

void DigScreen::mouseDown(po::scene::MouseEvent event)
{
    switch (event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
            
            break;
            
        default:
            break;
    }
}

void DigScreen::update()
{
    
}

void DigScreen::draw()
{
    
}
