#include "GameScene.h"
#include "GameLayer.h"

bool GameScene::init(){
	if(!Scene::init()){
		return false;
	}
	this->addChild(GameLayer::create());
	return true;
} 