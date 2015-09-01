
#include "MenuScene.h"
#include "MenuLayer.h"

bool MenuScene::init(){
	if(!Scene::init()){
		return false;
	}
	this->addChild(MenuLayer::create());
	return true;
} 