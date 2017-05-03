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
:FBO_WIDTH(1280)
,FBO_HEIGHT(1024)
{
    
}

void DigScreen::setup()
{
    ci::gl::Fbo::Format format;
    _dirtFbo = ci::gl::Fbo::create( FBO_WIDTH, FBO_HEIGHT, format.colorTexture() );
    
    
    try
    {
        _dirtTexture = cinder::gl::Texture::create( loadImage( cinder::app::loadAsset( "dirt1.jpg" ) ) );
        
    } catch (ci::Exception& e)
    {
        ci::app::console() << e.what() << std::endl;
    }
    
    _dirt2 = po::scene::Image::create(_dirtTexture);
    _dirt2 -> setScale(0.5f);
    _dirt2 -> setPosition(ci::vec2(ci::app::getWindowWidth()/2, ci::app::getWindowHeight()/2-80));
    _dirt2 -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    addChild(_dirt2);
}

void DigScreen::mouseDown(po::scene::MouseEvent event)
{
    switch (event.getType()) {
        case po::scene::MouseEvent::DOWN_INSIDE:
            std::cout << "digscene clicked" << std::endl;
            break;
            
        default:
            break;
    }
}

void DigScreen::renderToFbo()
{
    ci::gl::ScopedFramebuffer fbScp( _dirtFbo );
    ci::gl::enableAlphaBlending();
    
    ci::gl::color( ci::ColorA( 1.f, 1.f, 1.f, 1.f) );
    
    ci::gl::ScopedViewport scpVp( ci::ivec2( 0 ), _dirtFbo->getSize() );
    
    ci::Area bounds = _dirtTexture->getBounds();
    std::swap<int32_t>( bounds.y1, bounds.y2 );
    
    ci::gl::draw(_dirtTexture, bounds);
    
    ci::gl::disableAlphaBlending();
}

void DigScreen::update()
{
    this->renderToFbo();
}

void DigScreen::draw()
{
    _dirtFbo->bindTexture();
//    ci::gl::drawSolidCircle(ci::app::getWindowCenter(), 10);
    ci::gl::draw( _dirtFbo->getColorTexture(), ci::Rectf( 0, 0, ci::app::getWindowWidth(), ci::app::getWindowWidth() ) );
}
