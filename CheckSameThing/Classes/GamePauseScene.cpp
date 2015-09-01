#include "GamePauseLayer.h"
#include "GamePauseScene.h"

bool GamePauseScene::init(){
	if (!Scene::init())
	{
		return false;
	}
	//add layers to this scene
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Layer* result_result1 = GamePauseLayer::create();
	result_result1->setAnchorPoint(ccp(0, 0));
	result_result1->setPosition(ccp(0, 0));
	this->addChild(result_result1);
	return true;
}