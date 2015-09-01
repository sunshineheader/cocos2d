#include "GameScene.h"
#include "GameLayer.h"
#include "GameGuiLayer.h"

bool GameScene::init(){
	if (!Scene::init())
	{
		return false;
	}
	//add layers to this scene
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Layer* game_layer = GameLayer::create();
	game_layer->setPosition(0, 0);
	game_layer->setAnchorPoint(ccp(0, 0));
	this->addChild(game_layer);
	//add gui layer to this scene
	Node* gui_layer = GameGuiLayer::create();
	gui_layer->setPosition(0, 0);
	gui_layer->setAnchorPoint(ccp(0, 0));
	this->addChild(gui_layer);
	return true;
}