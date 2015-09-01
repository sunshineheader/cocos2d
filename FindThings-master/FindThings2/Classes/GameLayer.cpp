#include "GameLayer.h"
#include "BottomMenu.h"
#include "TaskMenu.h"
#include "GameOverScene.h"
#include "GameView.h"
#include "GameData.h"
#include "GameState.h"
#include "CallAndroidMethod.h"
#include "Audio.h"

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	GAMEDATA::getInstance()->cleanDatas();
	GAMESTATE::getInstance()->reset();
	GAMEDATA::getInstance()->setLoginTimes();//¼ÇÂ¼Íæ¼ÒµÇÂ½´ÎÊý
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//Ìí¼Ó±³¾°Í¼Æ¬
	Sprite* bg = Sprite::create("game_bg.png");
	bg->setAnchorPoint(Point(0,0));
	this->addChild(bg,-1);
	loadGameView();
	scheduleUpdate();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(GAMEDATA::getInstance()->getLoginTimes()==1){
		if(!GAMESTATE::getInstance()->getIsPaying()){
			GAMESTATE::getInstance()->setGamePause(true);
			CallAndroidMethod::getInstance()->pay(1);
			GAMESTATE::getInstance()->setIsPaying(true);
		}
	}else if(GAMEDATA::getInstance()->getLoginTimes()==2){
		if(!GAMESTATE::getInstance()->getIsPaying()){
			GAMESTATE::getInstance()->setGamePause(true);
			CallAndroidMethod::getInstance()->pay(6);
			GAMESTATE::getInstance()->setIsPaying(true);
		}
	}
#endif
	return true;
}

void GameLayer::loadGameView(){

	GameView* view =GameView::create();
	view->setAnchorPoint(Point(0,0));
	view->setPosition(0,0);
	this->addChild(view,-1);

	auto bottomMenu = BottomMenu::getInstance();
	bottomMenu->initGameTime();
	this->addChild(bottomMenu,1);

	auto taskMenu = TaskMenu::getInstance();
	taskMenu->cleanTaskMenu();
	this->addChild(taskMenu,2);

}

void GameLayer::update(float dt){
	if(GAMESTATE::getInstance()->getGameOver()){
		Director::getInstance()->replaceScene(TransitionFade::create(0.5,GameOverScene::create()));
	}
	if(GAMESTATE::getInstance()->getIsRevive()){
		BottomMenu::getInstance()->plusGameTime(TOTALTIME);
		GAMESTATE::getInstance()->setIsRevive(false);
		Audio::getInstance()->playSound(QUICKFIND);
	}
}