#include "TopMenu.h"
#include "Chinese.h"
#include "GameData.h"
#include "GamePauseLayer.h"
#include "GameLayer.h"
#include "StarMatrix.h"
#include "SimpleAudioEngine.h"
#include "CallAndroidMethod.h"
#include "HelloWorldScene.h"
#include "Audio.h"

TopMenu* TopMenu::_instance = nullptr;
TopMenu::TopMenu(){
	this->init();
}

TopMenu* TopMenu::getInstance(){
	if(_instance == 0){
		_instance = new TopMenu();
	}
	return _instance;
}

bool TopMenu::init(){
	if(!Node::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	highestScore = Label::create(
		ChineseWord("highestScore") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getHistoryScore())->_string,
		"Verdana-Bold",24
		);
	highestScore->setPosition(visibleSize.width/2,visibleSize.height/2+350);
	this->addChild(highestScore);


	curScore = Label::create(
		cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getCurScore())->_string,
		"Verdana-Bold",50
		);
	curScore->setPosition(visibleSize.width/2,visibleSize.height/2 +300);
	this->addChild(curScore);

	auto goldBuyBtn = MenuItemImage::create(
		"gold_buy_normal.png","gold_buy_click.png",CC_CALLBACK_0(TopMenu::pay,this)
		);
	auto goldBuyMenu = Menu::create(goldBuyBtn, NULL);
	goldBuyMenu->setPosition(visibleSize.width/2-185,visibleSize.height-50);
	this->addChild(goldBuyMenu);

	playerGold =Label::create(String::createWithFormat("%d",
		GAMEDATA::getInstance()->getGoldNum())->_string,"Arial",24);
	playerGold->setPosition(visibleSize.width/2-147,visibleSize.height-56);
	playerGold->setAnchorPoint(Point(0,0.5));
	this->addChild(playerGold);

	MenuItemImage* PauseBtn = MenuItemImage::create(
		"pause.png","pause.png",CC_CALLBACK_0(TopMenu::PauseGame,this)
		);
	Menu* menuPause = Menu::create(PauseBtn, NULL);
	menuPause->alignItemsHorizontally();
	menuPause->setPosition(visibleSize.width/2-190,visibleSize.height/2+300);
	this->addChild(menuPause);

	 BombBtn = MenuItemImage::create(
		"bomb_normal.png","bomb_click.png",CC_CALLBACK_0(TopMenu::usePropsBomb,this)
		);
	 TimeBtn = MenuItemImage::create(
		"time_normal.png","time_click.png",CC_CALLBACK_0(TopMenu::usePropsTime,this)
		);
	Menu* menu = Menu::create(BombBtn,TimeBtn, NULL);
	menu->alignItemsHorizontally();
	menu->setPosition(visibleSize.width/2+155,visibleSize.height/2+300);
	this->addChild(menu);

	propBombNum = Label::create(
		cocos2d::String::createWithFormat("%d",500)->_string,
		"Verdana-Bold",18
		);
	propBombNum->setPosition(visibleSize.width/2+150,visibleSize.height/2+280);
	this->addChild(propBombNum);

	propTimeNum = Label::create(
		cocos2d::String::createWithFormat("%d",800)->_string,
		"Verdana-Bold",18
		);
	propTimeNum->setPosition(visibleSize.width/2+223,visibleSize.height/2+280);
	this->addChild(propTimeNum);


	return true;
}

void TopMenu::pay(){
	Audio::getInstance()->playClick();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		GameLayer::_PauseTime =true;
		CallAndroidMethod::getInstance()->pay(12);
    #endif
}

void TopMenu::refresh(int score){
	GAMEDATA* data = GAMEDATA::getInstance();
	data->setCurScore(data->getCurScore() + score);
	if(data->getCurScore() > data->getHistoryScore()){
		data->setHistoryScore(data->getCurScore());
	}
	char buf[64];
	sprintf(buf,"%d",data->getCurScore());
	curScore->setString(buf);
}

void TopMenu::cleanScore(){
	char buf[64];
	sprintf(buf,"%d",0);
	curScore->setString(buf);
	highestScore->setString(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getHistoryScore())->_string);
	refreshGold();
}

void TopMenu::refreshGold(){
	playerGold->setString(String::createWithFormat("%d",GAMEDATA::getInstance()->getGoldNum())->_string);
}

void TopMenu::usePropsBomb(){
	Audio::getInstance()->playClick();
	auto gold =GAMEDATA::getInstance()->getGoldNum();
	if(gold>=500){
		if(!(StarMatrix::BombClick)){
			StarMatrix::BombClick =true;
			auto scale1 = ScaleTo::create(1.0f,0.6,0.6,0);
			auto scale2 = ScaleTo::create(1.0f,1.0,1.0,0);
			// create the sequence of actions, in the order we want to run them
			auto seq1 = Sequence::create(scale1, scale2,nullptr);
			// run the sequence and repeat forever.
			BombBtn->runAction(RepeatForever::create(seq1));
		}
	}else{
		//����֧��
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		GameLayer::_PauseTime =true;
		CallAndroidMethod::getInstance()->pay(13);
#endif

	}

}

void TopMenu::stopScaleAction(){
	BombBtn->setScale(1.0);
	BombBtn->stopAllActions();
}


void TopMenu::usePropsTime(){
	Audio::getInstance()->playClick();
	auto gold =GAMEDATA::getInstance()->getGoldNum();
	if(gold>=800){
		if(!(StarMatrix::BombClick) && GameLayer::totalTime>1){
			Size visibleSize = Director::getInstance()->getVisibleSize();
			plusTimeWord =FloatWord::create("+10"+ChineseWord("miao"),12,Point(visibleSize.width/2+175,visibleSize.height/2+300));
			this->addChild(plusTimeWord);
			plusTimeWord->floatInTime(0.5,0,[=](){
				GameLayer::needPluse =true;
				GAMEDATA::getInstance()->setGoldNum(gold-800);
				GAMEDATA::getInstance()->saveGoldNum();
				propTimeNum->setString(String::createWithFormat("%d",800)->_string);
				refreshGold();
			});

		}
	}else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		GameLayer::_PauseTime =true;
		CallAndroidMethod::getInstance()->pay(13);
#endif
	}
}

void TopMenu::PauseGame(){
	Audio::getInstance()->playClick();
	GameLayer::_PauseTime =true;
	gamePause = GamePauseLayer::create(this);
	this->addChild(gamePause,1);
}


void TopMenu::updatePropsNum(){
	propTimeNum->setString(String::createWithFormat("%d",800)->_string );
	propBombNum->setString(String::createWithFormat("%d",500)->_string );
}
