#include "StartScene.h"
#include "GameScene.h"
#include "Audio.h"
#include "GameData.h"
#include "SimpleAudioEngine.h"
#include "SignIn.h"
#include "CallAndroidMethod.h"
#include "BlinkTitle.h"
#include "GameState.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* StartScene::createScene()
{
	auto scene = Scene::create();

	auto layer = StartScene::create();

	scene->addChild(layer);

	return scene;
}

bool StartScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	//加载游戏场景中的资源
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("material_info.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("task_title.plist");

	Audio::getInstance()->playBGM(BACKGORUNDMUSIC);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* gamebg = Sprite::create("game_bg.png");
	gamebg->setAnchorPoint(ccp(0.5,0.5));
	gamebg->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(gamebg,-1);

	Sprite* boy = Sprite::create("game_start_boy.png");
	boy->setPosition(ccp(570,280));
	this->addChild(boy,1);

	Sprite* title = Sprite::create("game_title.png");
	title->setAnchorPoint(ccp(0,1));
	title->setPosition(ccp(10,380));
	this->addChild(title,2);

	Sprite* clock = Sprite::create("game_clock.png");
	clock->setPosition(ccp(85,135));
	this->addChild(clock);

	Sprite* star1 = Sprite::create("game_star.png");
	star1->setPosition(ccp(50,60));
	RotateBy* rotate = RotateBy::create(6,360);
	star1->runAction(RepeatForever::create(rotate));
	this->addChild(star1);

	Sprite* star2 = Sprite::create("game_star.png");
	star2->setPosition(ccp(600,100));
	ScaleTo* scale1 = ScaleTo::create(1,0.8);
	ScaleTo* scale2 = ScaleTo::create(1,1.0);
	Sequence* seq = Sequence::create(scale1,scale2,NULL);
	star2->runAction(RepeatForever::create(seq));
	this->addChild(star2);

	BlinkTitle* btitle = BlinkTitle::create("start_game_txt.png");;
	btitle->setPosition(visibleSize.width/2,100);
	this->addChild(btitle,2); 

	MenuItemImage* start = MenuItemImage::create("start_game_txt.png","start_game_txt.png",CC_CALLBACK_0(StartScene::startGame,this));
	Menu* menu = Menu::create(start,NULL);
	menu->setPosition(ccp(visibleSize.width/2,100));
	this->addChild(menu,1);

	MenuItemImage* musicBtnOn = MenuItemImage::create("bg_music_open.png","bg_music_open.png");
	MenuItemImage* musicBtnOff = MenuItemImage::create("bg_music_close.png","bg_music_close.png");
	MenuItemToggle* musicTog = MenuItemToggle::createWithTarget(this,menu_selector(StartScene::getMusicState),musicBtnOn,musicBtnOff,NULL);
	if (GAMEDATA::getInstance()->getMusicState())
	{
		musicTog->setSelectedIndex(0);
	}
	else
	{
		musicTog->setSelectedIndex(1);
	}
	Menu* musicMenu = Menu::create(musicTog,NULL);
	musicMenu->setPosition(745,450);
	this->addChild(musicMenu);

	helpButton = nullptr;
	MenuItemImage* helpItem = MenuItemImage::create("help.png","help.png",CC_CALLBACK_0(StartScene::showHelpView,this));
	Menu* help = Menu::create(helpItem,NULL);
	help->setPosition(685,450);
	this->addChild(help);

	MenuItemImage* image = MenuItemImage::create("more_game.png","more_game.png",CC_CALLBACK_0(StartScene::showMoreGame,this));
	moreGame = Menu::create(image, nullptr);
	moreGame->setPosition(720, 40);
	this->addChild(moreGame);
	moreGame->setVisible(false);
	schedule(schedule_selector(StartScene::updateScene), 1.0f, kRepeatForever,0);

#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	//签到没有东西可送先关闭
	/*if(!CallAndroidMethod::getInstance()->isSignToday()){
	SignIn* sg = SignIn::getInstance();
	sg->setAnchorPoint(ccp(0.5,0.5));
	this->addChild(sg,3);
	}else{
	schedule(schedule_selector(StartScene::autoStartGame), 3.0f, 0, 0);
	}*/
#endif
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			//quitDialog->setVisible(true);
			showQuit();
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//showQuit();//初始化游戏退出界面
	return true;
}


void StartScene::startGame(){
	//if(!quitDialog->isVisible())
		Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}


void StartScene::getMusicState(cocos2d::Ref* pSender){

	CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;  
	if (temp->getSelectedIndex()==1)  
	{   
		Audio::getInstance()->playSound(CLICK);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic(); 
		GAMEDATA::getInstance()->setMusicState(false);

	}  
	if (temp->getSelectedIndex()==0)  
	{  
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic(); 
		GAMEDATA::getInstance()->setMusicState(true);
	}
}


//游戏前3局自动开始游戏
void StartScene::autoStartGame(float dt){
	if(GAMEDATA::getInstance()->getLoginTimes()<3){
		Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
	}
}

void StartScene::showHelpView(){
	//if(nullptr != helpButton || quitDialog->isVisible())
	if (nullptr != helpButton){
		return;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	helpButton = Button::create("help_text.png","help_text.png");
	helpButton->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	helpButton->addTouchEventListener(CC_CALLBACK_2(StartScene::buttonTouchEvent, this));
	this->addChild(helpButton,3);
}

//帮助按钮的点击事件分发处理
void StartScene::buttonTouchEvent(Ref *pSender,Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;

	case Widget::TouchEventType::MOVED:
		break;

	case Widget::TouchEventType::ENDED:
		{
			helpButton->removeFromParent();
			helpButton = nullptr;
		}
		break;        
	case Widget::TouchEventType::CANCELED:
		break;          
	default:
		break;
	}
}

void StartScene::showQuit(){
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//quitDialog = Layer::create();
	//this->addChild(quitDialog,9);
	//Sprite* quit_bg = Sprite::create("quit_bg.png");
	//quit_bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	//quitDialog->addChild(quit_bg);
	//quitDialog->setVisible(false);
	//MenuItemImage* cancel = MenuItemImage::create("quit_cancel.png","quit_cancel.png",CC_CALLBACK_0(StartScene::cancelQuit,this));
	//MenuItemImage* confirm = MenuItemImage::create("quit_comfirm.png","quit_comfirm.png",CC_CALLBACK_0(StartScene::confirmQuit,this));
	//Menu* quit_Menu = Menu::create(confirm,cancel,NULL);
	//quit_Menu->alignItemsHorizontallyWithPadding(100);
	//quit_Menu->setPosition(visibleSize.width/2,visibleSize.height/2-100);
	//quitDialog->addChild(quit_Menu);
	CallAndroidMethod::getInstance()->quit();
}

//确定退出
void StartScene::confirmQuit(){
	Audio::getInstance()->playSound(CLICK);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CallAndroidMethod::getInstance()->quit();
	CallAndroidMethod::getInstance()->startNativeNotify();
#endif
	Director::getInstance()->end();
}

//取消退出
void StartScene::cancelQuit(){
	Audio::getInstance()->playSound(CLICK);
//	quitDialog->setVisible(false);
}

void StartScene::showMoreGame(){
	CallAndroidMethod::getInstance()->showMoreGame();
}

void StartScene::updateScene(float dt){
	if (GAMESTATE::getInstance()->getIsShowMoreGame()){
		moreGame->setVisible(true);
	}
	else{
		moreGame->setVisible(false);
	}
}
