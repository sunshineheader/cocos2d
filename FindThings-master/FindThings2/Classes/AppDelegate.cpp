#include "AppDelegate.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
#include "CallAndroidMethod.h"
#include "GameState.h"

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
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Find Game");
		director->setOpenGLView(glview);
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	glview->setDesignResolutionSize(800, 480, kResolutionExactFit);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if(visibleSize.width/visibleSize.height > 800.0/480.0){
		glview->setDesignResolutionSize(800, 480, ResolutionPolicy::EXACT_FIT);
	}
	else{
		glview->setDesignResolutionSize(800, 480, ResolutionPolicy::NO_BORDER);
	}
#endif
	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	auto scene = StartScene::createScene();

    CallAndroidMethod::getInstance()->isShowMoreGame();
	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	if (GAMEDATA::getInstance()->getMusicState()){
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}
