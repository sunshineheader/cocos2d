#include "GameResultScene.h"
#include "GameResultLayer.h"

bool GameResultScene::init(){
	if(!Scene::init()){
		return false;
	}
	this->addChild(GameResultLayer::create());
	return true;
} 