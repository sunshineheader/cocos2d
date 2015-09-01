#include "GamePauseLayer.h"
#include"GameGuiLayer.h"
#include"GameResultScene.h"
#include"GameData.h"
#include"LobbyScene.h"
#include"Audio.h"
#include"CallAndroidMethod.h"
using namespace cocos2d;
GamePauseLayer* GamePauseLayer::create(){
	GamePauseLayer* ret = new GamePauseLayer();
	if(ret && ret->init()){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}


bool GamePauseLayer::init(){
if ( !Layer::init() )
	{
		return false;
	}

EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

listener->setSwallowTouches(true);

listener->onTouchBegan = CC_CALLBACK_2(GamePauseLayer::onTouchBegan, this);
listener->onTouchMoved = CC_CALLBACK_2(GamePauseLayer::onTouchMoved, this);
listener->onTouchEnded = CC_CALLBACK_2(GamePauseLayer::onTouchEnded, this);

_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
setTouchEnabled(true);
  //add sprite to this scene
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite* pause_bg = Sprite::create("pause_bg.png");
	this->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(pause_bg);

	//add daoju gift pic
	auto daoju = Menu::create();
	auto sp = Sprite::create("gift_package.png");
	auto sp1 = Sprite::create("gift_package.png");

	auto daojuBtn = MenuItemSprite::create(sp, sp1, nullptr, CC_CALLBACK_0(GamePauseLayer::getdaoju, this));
	daojuBtn->setPosition(Point(0, 0));
	daoju->addChild(daojuBtn);
	daoju->setPosition(0, 100);
	this->addChild(daoju);

	
	//add  achieve
	auto achieve_game = Menu::create();
	auto spriteNormal = Sprite::create("achieve.png");
	spriteNormal->setScale(0.8, 0.8);
	auto spriteSelected = Sprite::create("achieve.png");
	spriteSelected->setScale(0.9, 0.9);

	auto achieve = MenuItemSprite::create(spriteNormal, spriteSelected, nullptr, CC_CALLBACK_0(GamePauseLayer::getGift, this));
	achieve->setPosition(Point(0,0));
	achieve_game->addChild(achieve);
	achieve_game->setPosition(Point(20,-200));
	this->addChild(achieve_game);
	
	//add resume btn to this layer
	auto resume_btn = Menu::create();
	auto spriteNormal1 = Sprite::create("game_resume.png");
	spriteNormal1->setAnchorPoint(Point(0.5, 0.5));
		spriteNormal1->setScale(0.7, 0.7);
	auto spriteSelected1 = Sprite::create("game_resume.png");
	spriteSelected1->setAnchorPoint(Point(0.5, 0.5));
	spriteSelected1->setScale(0.8, 0.8);
	auto resume = MenuItemSprite::create(spriteNormal1, spriteSelected1, CC_CALLBACK_0(GamePauseLayer::resumeGame, this));
	resume->setPosition(Point(-50, -300));
	resume_btn->addChild(resume);
	resume_btn->setPosition(Point(0,0));
	this->addChild(resume_btn);

	//add delay
	auto delay_btn = Menu::create();
	auto spriteNormal2 = Sprite::create("delay.png");
	spriteNormal2->setScale(0.7, 0.7);
	auto spriteSelected2 = Sprite::create("delay.png");
	spriteSelected2->setScale(0.8, 0.8);
	auto delay = MenuItemSprite::create(spriteNormal2, spriteSelected2, CC_CALLBACK_0(GamePauseLayer::delayTen, this));
	delay->setPosition(Point(120, -300));
	delay_btn->addChild(delay);
	delay_btn->setPosition(Point(0, 0));

	this->addChild(delay_btn);

	MenuItemImage* close_btn = MenuItemImage::create("close_nomal.png", "close_click.png", CC_CALLBACK_0(GamePauseLayer::goBack, this));
	Menu* close_game = Menu::create(close_btn, NULL);
	close_game->setPosition(200, 300);

	this->addChild(close_game);


	return true;
}



void GamePauseLayer::resumeGame(){
	//TODO resume game
	Audio::getInstance()->playBtnEffect();
	this->resume();
	this->removeFromParentAndCleanup(true);
	GAMEDATA::getInstance()->setstate(0);
}


void GamePauseLayer::getdaoju(){
	//TODO getGift
	Audio::getInstance()->playBtnEffect();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	CallAndroidMethod::getInstance()->pay(11);

#endif
}

void GamePauseLayer::getGift(){
	//TODO getGift
	Audio::getInstance()->playBtnEffect();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	
		CallAndroidMethod::getInstance()->pay(11);

#endif
}
void GamePauseLayer::goBack(){
	Audio::getInstance()->playBtnEffect();
	this->removeFromParentAndCleanup(true);
	Director::getInstance()->replaceScene(TransitionFade::create(1,LobbyScene::createScene()));
	

	
}

void GamePauseLayer::delayTen(){
	//TODO dalayTen
	Audio::getInstance()->playBtnEffect();
	int addtime = GAMEDATA::getInstance()->getaddtimeNum();
	int addtime1 = addtime - 1;

	if (addtime1 >0){
		GAMEDATA::getInstance()->setaddtimeNum(addtime1);
		GameGuiLayer:: addTime = true;
		GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() + 10);
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (addtime1 <= 0){
		GameGuiLayer::addTime = false;
		CallAndroidMethod::getInstance()->pay(10);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (addtime1 <= 0){
		GAMEDATA::getInstance()->setaddtimeNum(0);
		GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime());
		GameGuiLayer::addTime = false;
	}
#endif
	this->removeFromParentAndCleanup(true);
	GAMEDATA::getInstance()->setstate(0);

}
bool GamePauseLayer::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return true;
}
