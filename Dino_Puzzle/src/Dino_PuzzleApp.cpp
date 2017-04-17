#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Dino_PuzzleApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void Dino_PuzzleApp::setup()
{
}

void Dino_PuzzleApp::mouseDown( MouseEvent event )
{
}

void Dino_PuzzleApp::update()
{
}

void Dino_PuzzleApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( Dino_PuzzleApp, RendererGl )
