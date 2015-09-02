#include "GameScene.h"
#include "GameLayer.h"
#include "GameGuiLayer.h"
#include "LevelScene.h"

bool GameScene::init(){
	if ( !Scene::init() )
	{
		return false;
	}
	//add layers to this scene
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Layer* game_layer = GameLayer::create();
	game_layer->setPosition(0,0);
	game_layer->setAnchorPoint(ccp(0,0));
	this->addChild(game_layer,0);
	//add gui layer to this scene
	Layer* gui_layer = GameGuiLayer :: create();
	gui_layer->setPosition(0,0);
	gui_layer->setAnchorPoint(ccp(0,0));
	this->addChild(gui_layer,1);
	//²âÊÔÓÃ·½·¨
	Size visibleSzie = Director::getInstance()->getVisibleSize();
	MenuItemImage* gotoLevelScene = MenuItemImage::create("content.png", "content.png", CC_CALLBACK_0(GameScene::gotoLevelScene, this));
	gotoLevelScene->setScale(0.2);
	auto menu = Menu::create(gotoLevelScene, NULL);
	menu->setPosition(ccp(visibleSzie.width-100, visibleSzie.height-100));
	this->addChild(menu);

	return true;
}

void GameScene::gotoLevelScene(){
	Director::getInstance()->replaceScene(TransitionFade::create(1, LevelScene::create()));
}