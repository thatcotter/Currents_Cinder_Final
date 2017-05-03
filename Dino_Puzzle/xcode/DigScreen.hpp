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


#ifndef DigScreen_hpp
#define DigScreen_hpp


class DigScreen;

typedef std::shared_ptr<DigScreen> DigScreenRef;

class DigScreen : public po::scene::NodeContainer
{
public:
    static DigScreenRef create();
    
    void mouseDown(po::scene::MouseEvent event);
    
    void update();
    void draw();
    
private:
    DigScreen();
    void setup();
    
    void renderToFbo();
    int FBO_WIDTH;
    int FBO_HEIGHT;
    
    ci::gl::FboRef      _dirtFbo;
    
    ci::gl::BatchRef    _dirtBatch;
//    ci::gl::GlslProg    _dirtShade;
    po::scene::ImageRef _dirt2;
    
    ci::gl::TextureRef  _dirtTexture;
    ci::gl::TextureRef  _maskTexture;
    
};
#endif /* DigScreen_hpp */
