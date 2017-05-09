//
//  DigScreen.hpp
//  Dino_Puzzle
//
//  Created by Andrew Cotter on 4/26/17.
//
//

#include "poNodeContainer.h"
#include "poShape.h"
#include "poImage.h"

#include "cinder/Rand.h"

//#include "ParticleSystem.hpp"
#include "Particle.hpp"

#ifndef DigScreen_hpp
#define DigScreen_hpp


class DigScreen;

typedef std::shared_ptr<DigScreen> DigScreenRef;

class DigScreen : public po::scene::NodeContainer
{
public:
    static DigScreenRef create();
    
    void mouseDown(ci::app::MouseEvent event);
    
    void update();
    void draw();
    
    void drawDigBrush( ci::ivec2 pos );
    void repulseFrom( ci::vec2 pos );
    void bounceFromEdge();
    
private:
    DigScreen();
    void setup();
    
    void renderToFbo();
    int FBO_WIDTH;
    int FBO_HEIGHT;
    
    float mDepthMapBaseline = 1.f;
    float mDepthThreshold = 1.f;
    float mDepthSmooth = 1.f;
    
    int mCurrentDigCanvasFboIndex;
    
    ci::gl::FboRef         mDigCanvasFbo;
    ci::gl::Fbo::Format format;
    
    ci::gl::TextureRef  mObjectTexture;
    ci::gl::TextureRef  mDepthMap;
    
    ci::gl::BatchRef    mObjectBatch;
    ci::gl::BatchRef    mDigCanvasBatch;
    
    cinder::Rand mRand;
    
    int rows;
    int cols;
    std::vector<std::vector<ci::vec2>> grid;
    std::vector<std::vector<ci::Color>> hues;
    ci::Color brown;
    
//    ParticleSystem mSystem;
    std::vector<ParticleRef> mParticles;
    
    float			mRange;
    float			mRepulsionFactor;
    
};
#endif /* DigScreen_hpp */
