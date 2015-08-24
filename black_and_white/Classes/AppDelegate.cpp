#include "AppDelegate.h"
#include"GameStartScene.h"
#include "GameLayerScene.h"
#include "GameOverScenecpp.h"
#include "ChineseWorld.h"
#include "GameDefinition.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if(!glview) {
        glview = GLViewImpl::create(ChineseWord("game_name"));
		//glview->setFrameSize(WINDOW_WITDH, WINDOW_HEIGHT);
		//glview->setDesignResolutionSize(480, 800,ResolutionPolicy::SHOW_ALL);
        director->setOpenGLView(glview);
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview->setFrameSize(480, 800);
#endif
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (visibleSize.height / visibleSize.width > 800 / 480){
		glview->setDesignResolutionSize(480, 800, ResolutionPolicy::EXACT_FIT);
	}
	else{
		glview->setDesignResolutionSize(480, 800, ResolutionPolicy::NO_BORDER);
	}

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	auto frame_size = glview->getFrameSize();
	
	//float width_rote=frame_size.width/


    // create a scene. it's an autorelease object
    auto scene = GameStart::createScene();
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
