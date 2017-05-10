#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "poScene.h"
#include "poShape.h"
#include "poTextBox.h"

#include "AssemblyScene.hpp"
#include "DigScreen.hpp"

#include "SwitchButton.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class Dino_PuzzleApp : public App {
  public:
	void setup() override;
	void mouseMove( MouseEvent event ) override;
    void mouseDrag( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void onSwitchLeftChange(bool state);
    void onSwitchRightChange(bool state);
    
    po::scene::SceneRef mScene;
    
    po::scene::NodeContainerRef mNodeContainer;
//    po::scene::NodeContainerRef mNodeContainer_Dig;
    
    AssemblySceneRef mAssemblyScene;
    DigScreenRef mDigScreen;
    
    float windowWidth = 1280;
    float windowHeight = 1024;
    
    vec2 mousePos;
    
    SwitchButtonRef mSwitchLeftButton;
    SwitchButtonRef mSwitchRightButton;
};

void Dino_PuzzleApp::setup()
{
    ci::app::setFullScreen(true);
    
    mNodeContainer = po::scene::NodeContainer::create();
    mScene = po::scene::Scene::create(mNodeContainer);
    
    ci::app::setWindowSize(windowWidth,windowHeight);
    
    //Dig Scene
    mDigScreen = DigScreen::create();
    mDigScreen -> setPosition(vec2(0.f,0.f));
    mNodeContainer -> addChild(mDigScreen);
    
    //Assembly Scene
    mAssemblyScene = AssemblyScene::create(windowWidth,windowHeight);
    mAssemblyScene -> setPosition(vec2(1280.f,0.f));
    mNodeContainer -> addChild(mAssemblyScene);
    
    //Switch Button
    mSwitchLeftButton = SwitchButton::create("<");
//    mSwitchLeftButton -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    mSwitchLeftButton -> setPosition(40.f,450.f);
    mSwitchLeftButton -> setAlpha(0.f);
    mNodeContainer -> addChild(mSwitchLeftButton);
    
    mSwitchRightButton = SwitchButton::create(">");
    //    mSwitchLeftButton -> setAlignment(po::scene::Alignment::CENTER_CENTER);
    mSwitchRightButton -> setPosition(1240.f,450.f);
    mSwitchRightButton -> setAlpha(1.f);
    mNodeContainer -> addChild(mSwitchRightButton);
    
    mSwitchLeftButton->getSwitchButtonChangeSignal().connect(std::bind(&Dino_PuzzleApp::onSwitchLeftChange, this, std::placeholders::_1));
    mSwitchRightButton->getSwitchButtonChangeSignal().connect(std::bind(&Dino_PuzzleApp::onSwitchRightChange, this, std::placeholders::_1));
}

void Dino_PuzzleApp::onSwitchLeftChange(bool state)
{
    if(state){
        ci::app::timeline().apply(&mAssemblyScene->getPositionAnim(), vec2(1280.f,0.f), 1.f);
        ci::app::timeline().apply(&mDigScreen->getPositionAnim(), vec2(0.f,0.f), 1.f);
        ci::app::timeline().apply(&mSwitchRightButton->getAlphaAnim(), 1.f, 0.5f,ci::EaseOutExpo());
        ci::app::timeline().apply(&mSwitchLeftButton->getAlphaAnim(), 0.f, 0.5f,ci::EaseOutExpo());
    }
}

void Dino_PuzzleApp::onSwitchRightChange(bool state)
{
    if(state){
        ci::app::timeline().apply(&mDigScreen->getPositionAnim(), vec2(-1280.f,0.f), 1.f);
        ci::app::timeline().apply(&mAssemblyScene->getPositionAnim(), vec2(0.f,0.f), 1.f);
        ci::app::timeline().apply(&mSwitchLeftButton->getAlphaAnim(), 1.f, 0.5f,ci::EaseOutExpo());
        ci::app::timeline().apply(&mSwitchRightButton->getAlphaAnim(), 0.f, 0.5f,ci::EaseOutExpo());
    }else{
        
    }
}

void Dino_PuzzleApp::mouseMove( MouseEvent event )
{
    mousePos = event.getPos();
}

void Dino_PuzzleApp::mouseDrag( MouseEvent event )
{
    mDigScreen->mouseDown(event);
    //    cout << "TEST: " << event.getPos() << endl;
}

void Dino_PuzzleApp::update()
{
    mScene -> update();
    mAssemblyScene -> update(mousePos,mDigScreen->bonesFound);
    mDigScreen->update(mousePos);
  
//    bool bones1Found = mDigScreen->bonesFound[0];
    
    cout << mDigScreen->bonesFound[0] << endl;
}

void Dino_PuzzleApp::draw()
{
	gl::clear( Color( 1, 1, 1 ) );
    mScene -> draw();
}

CINDER_APP( Dino_PuzzleApp, RendererGl )
