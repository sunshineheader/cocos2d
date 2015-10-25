#include "GameOverScene.h"
using namespace cocos2d;

bool GameOverScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	addChild(GameOverLayer::create());
	return true;
}