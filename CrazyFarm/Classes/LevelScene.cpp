#include "LevelScene.h"
#include "LevelLayer.h"

bool LevelScene::init(){

	Size visibleSize = Director::getInstance()->getVisibleSize(); 
	
	auto sceneBg = Sprite::create("lobby_bg.jpg");
	sceneBg->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(sceneBg);

	auto levelLayer = LevelLayer::create();
	levelLayer->setAnchorPoint(ccp(0,0));
	levelLayer->setPosition(0, 0);
	this->addChild(levelLayer);

	return true;
}