#include "LobbyScene.h"
#include "GameScene.h"
#include "GamePauseLayer.h"
#include "Audio.h"

Scene* LobbyScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LobbyScene::create();

	scene->addChild(layer);

	return scene;
}

bool LobbyScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

    Audio::getInstance()->playBGM(BACKGORUND_MUSIC);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//add game bg to layer
	Sprite* lobby_bg = Sprite::create("lobby_bg.png");
	lobby_bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(lobby_bg,-1);
	//add statr menu to layer

	MenuItemImage* start_btn = MenuItemImage::create("start_game_btn_normal.png","start_game_btn_clicked.png",CC_CALLBACK_0(LobbyScene::startGame,this));
	Menu* start_game = Menu::create(start_btn,NULL);
	start_game->setPosition(visibleSize.width/2,visibleSize.height/5);
	this->addChild(start_game);

	//add setting btn 
	MenuItemImage* setting_btn = MenuItemImage::create("btn_setting01.png", "btn_setting02.png", CC_CALLBACK_0(LobbyScene::goToSetting, this));
	Menu* setting = Menu::create(setting_btn, NULL);
	setting->setPosition(visibleSize.width-30, visibleSize.height-30);
	this->addChild(setting);

	return true;
}

void LobbyScene::startGame(){
	 Audio::getInstance()->playSound(CLICK);
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}

void LobbyScene::goToSetting(){
	Layer* pause_layer = GamePauseLayer::create();
	pause_layer->setAnchorPoint(ccp(0, 0));
	pause_layer->setPosition(0, 0);
	this->addChild(pause_layer, 2);
}
