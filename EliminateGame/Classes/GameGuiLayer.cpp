#include "GameGuiLayer.h"
#include "GamePauseLayer.h"
#include "GameResultScene.h"
#include "GameData.h"
#include "GameState.h"
#include "Audio.h"

bool GameGuiLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	gotoResultLayer = false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//add pause btn to this layer
	MenuItemImage* start_btn = MenuItemImage::create(
		"btn_setting.png", "btn_setting.png", CC_CALLBACK_0(GameGuiLayer::pauseGame, this));
	Menu* start_game = Menu::create(start_btn, NULL);
	start_game->setPosition(visibleSize.width - 30, visibleSize.height - 30);
	this->addChild(start_game);
	//add player score 
	playerScore = LabelAtlas::create(
		cocos2d::String::createWithFormat("%d", GAMEDATA::getInstance()->getScore())->_string, "game_result_score_num.png", 49, 70, '0');
	playerScore->setScale(0.8f);
	playerScore->setAnchorPoint(ccp(0.5, 0.5));
	playerScore->setPosition(ccp(240, 760));
	this->addChild(playerScore);
	//init palyer time 
	initTime();

	//add time progress
	gameSlioder = GameSlioder::create();
	gameSlioder->setAnchorPoint(ccp(0, 0));
	gameSlioder->setPosition(ccp(0, 0));
	this->addChild(gameSlioder);
	//add play time 
	LabelAtlas* zero = LabelAtlas::create("00", "time_num.png", 17, 20, '0');
	zero->setPosition(ccp(195, 695));
	this->addChild(zero);

	Sprite* devide = Sprite::create("time_devide_icon.png");
	devide->setPosition(ccp(234, 707));
	this->addChild(devide);
	std::string time_string = "";
	if (totalTime - passTime < 10){
		std::string time_string = "0";
	}
	palyTime = LabelAtlas::create(time_string +
		cocos2d::String::createWithFormat("%d", (int)(totalTime - passTime))->_string, "time_num.png", 17, 20, '0');
	palyTime->setPosition(ccp(240, 695));
	this->addChild(palyTime);
	scheduleUpdate();
	schedule(schedule_selector(GameGuiLayer::updateTime), 1.0f, kRepeatForever, 0);
	return true;
}

void GameGuiLayer::initTime(){
	totalTime = 10;
	passTime = 0;
	countTime = 0;
}

void GameGuiLayer::pauseGame(){
	Audio::getInstance()->playSound(CLICK);
	GAMESTATE::getInstance()->setGamePause(true);
	Layer* pause_layer = GamePauseLayer::create();
	pause_layer->setAnchorPoint(ccp(0, 0));
	pause_layer->setPosition(0, 0);
	this->addChild(pause_layer, 2);
}

void GameGuiLayer::gotoResult(){
	if (!gotoResultLayer){
		Director::getInstance()->replaceScene(TransitionFade::create(1, GameResultScene::create()));
		gotoResultLayer = true;
	}

}

void GameGuiLayer::update(float dt){
	countTime += dt;
	if (countTime > 0.5f){
		updateShowScore();
		countTime -= 0.5f;
	}
}

void GameGuiLayer::updateTime(float dt){
	//test 10s goto result scene
	if (!GAMESTATE::getInstance()->getGamePause()){
		passTime += 1;
		if (totalTime - passTime <= 0){
			gotoResult();
		}
	}
	gameSlioder->updateTimeProgress(totalTime - passTime, totalTime);
	updateShowTime();
}

//刷新玩家的分数显示
void GameGuiLayer::updateShowScore(){
	CCLOG("score = %d", GAMEDATA::getInstance()->getScore());
	playerScore->setString(cocos2d::String::createWithFormat("%d", GAMEDATA::getInstance()->getScore())->_string);
}


void GameGuiLayer::updateShowTime(){
	if ((int)(totalTime - passTime) < 10){
		palyTime->setString("0" + cocos2d::String::createWithFormat("%d", (int)(totalTime - passTime))->_string);
	}
	else{
		palyTime->setString(cocos2d::String::createWithFormat("%d", (int)(totalTime - passTime))->_string);
	}
}
