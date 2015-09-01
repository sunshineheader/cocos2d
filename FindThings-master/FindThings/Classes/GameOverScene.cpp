#include "GameOverScene.h"
#include "GameOverLayer.h"

bool GameOverScene::init(){
	if(!Scene::init()){
		return false;
	}
	this->addChild(GameOverLayer::create());
	return true;
} 