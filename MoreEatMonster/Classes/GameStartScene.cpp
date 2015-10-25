#include "GameStartScene.h"
using namespace cocos2d;

bool GameStartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	addChild(GameStart::create());
	return true;
}