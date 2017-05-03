#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "poScene.h"
#include "poShape.h"
#include "poTextBox.h"

#include "AssemblyScene.hpp"
#include "DigScreen.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class Dino_PuzzleApp : public App {
  public:
	void setup() override;
	void mouseMove( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    DigScreenRef mDigScreen;
    
    po::scene::SceneRef mScene;
    po::scene::NodeContainerRef mNodeContainer_Assembly;
    po::scene::NodeContainerRef mNodeContainer_Dig;
    
    AssemblySceneRef mAssemblyScene;
    float windowWidth = 1280;
    float windowHeight = 1024;
    
    vec2 mousePos;
};

void Dino_PuzzleApp::setup()
{
    mNodeContainer_Assembly = po::scene::NodeContainer::create();
    mNodeContainer_Dig = po::scene::NodeContainer::create();
    mScene = po::scene::Scene::create(mNodeContainer_Assembly);
    
    ci::app::setWindowSize(windowWidth,windowHeight);
    
    //Assembly Scene
    mAssemblyScene = AssemblyScene::create(windowWidth,windowHeight);
    mAssemblyScene -> setPosition(vec2(0.f,0.f));
    mNodeContainer_Assembly -> addChild(mAssemblyScene);
    
    //Dig Scene
    mDigScreen = DigScreen::create();
    mAssemblyScene -> setPosition(vec2(0.f,0.f));
    mNodeContainer_Assembly -> addChild(mDigScreen);
}

void Dino_PuzzleApp::mouseMove( MouseEvent event )
{
    mousePos = event.getPos();
}

void Dino_PuzzleApp::update()
{
    mScene -> update();
    mAssemblyScene -> update(mousePos);
    mDigScreen->update();
}

void Dino_PuzzleApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    mScene -> draw();
    mDigScreen->draw();
}

CINDER_APP( Dino_PuzzleApp, RendererGl )
