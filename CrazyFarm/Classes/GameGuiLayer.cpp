#include "GameGuiLayer.h"
#include "GamePauseLayer.h"
#include "GameResultScene.h"
bool GameGuiLayer::init(){
	if ( !Layer::init() )
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//add pause btn to this layer
	MenuItemImage* start_btn = MenuItemImage::create("btn_bg_normal.png","btn_bg_click.png",CC_CALLBACK_0(GameGuiLayer::pauseGame,this));
	Menu* start_game = Menu::create(start_btn,NULL);
	start_game->setPosition(50,visibleSize.height-50);
	this->addChild(start_game);


	initTime();
	scheduleUpdate();
	return true;
}

void GameGuiLayer::initTime(){
	passTime = 0;
}

void GameGuiLayer::pauseGame(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Layer* pause_layer = GamePauseLayer::create();
	pause_layer->setAnchorPoint(ccp(0,0));
	pause_layer->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(pause_layer,2);
}

void GameGuiLayer::gotoResult(){
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameResultScene::create()));

}

void GameGuiLayer::update(float dt){
	//test 10s goto result scene
	passTime+=dt;
	if(passTime>=5){
		//gotoResult();
	}
}