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
:FBO_WIDTH(1280)
,FBO_HEIGHT(1024)
//,mDigCanvasFbo()
{
    
}

void DigScreen::setup()
{
//    mDigCanvasFbo = ci::gl::Fbo::create( FBO_WIDTH, FBO_HEIGHT, format.colorTexture() );
    
    mObjectTexture = cinder::gl::Texture2d::create(loadImage(cinder::app::loadAsset("dirt1.jpg")));
    mDepthMap = cinder::gl::Texture2d::create(loadImage(cinder::app::loadAsset("textures/dragon_object_depth_map.png")));
    auto objectShaders = cinder::gl::GlslProg::create(cinder::app::loadAsset("vertex.vert"), cinder::app::loadAsset("object.frag"));
    
    geom::Rect rect = geom::Rect().rect(Rectf(vec2(0, 0), vec2(getWindowWidth(), getWindowHeight())));
    
    mObjectBatch = ci::gl::Batch::create( rect, objectShaders);
    
    
    mObjectBatch->getGlslProg()->uniform("uTex0", 0);
    mObjectBatch->getGlslProg()->uniform("uTex1", 1);
    mObjectBatch->getGlslProg()->uniform("uTex2", 2);
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
    
    ci::gl::ScopedColor color(ci::Color::white());
    ci::gl::ScopedFramebuffer fbScp( mDigCanvasFbo );
    ci::gl::enableAlphaBlending();

    ci::gl::ScopedViewport scpVp( ci::ivec2( 0 ), mDigCanvasFbo->getSize() );
//    ci::Area bounds = _dirtTexture->getBounds();
//    std::swap<int32_t>( bounds.y1, bounds.y2 );
//    
//    ci::gl::draw(_dirtTexture, bounds);
//    
    ci::gl::disableAlphaBlending();
}

void DigScreen::drawDigBrush(ci::ivec2 pos) {
    mCurrentDigCanvasFboIndex = 1 - mCurrentDigCanvasFboIndex;
    
    ci::gl::ScopedFramebuffer scopedFramebuffer(mDigCanvasFbo);
    ci::gl::ScopedViewport scopedViewport(mDigCanvasFbo->getSize());
    ci::gl::ScopedMatrices scopedMatrices;
    ci::gl::setMatricesWindowPersp(mDigCanvasFbo->getSize());
    ci::gl::translate(-ci::ivec2(FBO_WIDTH, FBO_HEIGHT) / 2 + mDigCanvasFbo->getSize() / 2);
    
    mDigCanvasFbo->getColorTexture()->bind(0);
//    mBrushTexture->bind(1);
//    mDigCanvasBatch->getGlslProg()->uniform("uPos", ci::vec2(0.5, -0.5) + ci::vec2(-pos.x, pos.y) / ci::vec2(mBrushTexture->getSize()));
    mDigCanvasBatch->draw();
}

void DigScreen::update()
{
    this->renderToFbo();
//    mObjectBatch->getGlslProg()->uniform("uBaseline", mDepthMapBaseline);
//    mObjectBatch->getGlslProg()->uniform("uThreshold", mDepthThreshold);
//    mObjectBatch->getGlslProg()->uniform("uSmooth", mDepthSmooth);
}

void DigScreen::draw()
{
    mObjectTexture->bind(0);
    mDepthMap->bind(1);
    mDigCanvasFbo->getColorTexture()->bind(2);
    mObjectBatch->draw();
}
