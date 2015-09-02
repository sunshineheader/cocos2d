#include "AppDelegate.h"

#include "Utils/Properties.h"
#include "Utils/SceneHelper.h"
#include "Scenes/SceneMain.h"
#include "Scenes/SceneLevelSelect.h"
#include "Scenes/SceneLoading.h"
#include "NodeReaders/SceneMainReader.h"
#include "NodeReaders/SceneLevelSelectReader.h"
#include "NodeReaders/SceneGameReader.h"

USING_NS_CC;

static const char *s_kConfigFilepath = "Data/Config.json";
static const float s_kDesignResolutionWidth = 1136.0f;
static const float s_kDesignResolutionHeight = 640.0f;

AppDelegate::AppDelegate() 
{
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

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

static void registerReaderObjects()
{
	CSLoader::getInstance()->registReaderObject("SceneMainReader", (ObjectFactory::Instance)SceneMainReader::getInstance);
	CSLoader::getInstance()->registReaderObject("SceneLevelSelectReader", (ObjectFactory::Instance)SceneLevelSelectReader::getInstance);
	CSLoader::getInstance()->registReaderObject("SceneGameReader", (ObjectFactory::Instance)SceneGameReader::getInstance);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		Properties properties(s_kConfigFilepath);
		glview = GLViewImpl::create(properties.getStringForKey("GameName"));
		glview->setFrameSize(s_kDesignResolutionWidth, s_kDesignResolutionHeight);
        director->setOpenGLView(glview);
    }

	register_all_packages();
	registerReaderObjects();

	glview->setDesignResolutionSize(s_kDesignResolutionWidth, 
		s_kDesignResolutionHeight, 
		ResolutionPolicy::FIXED_HEIGHT);

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
	director->runWithScene(SceneHelper::createStartScene());

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
