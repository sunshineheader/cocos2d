#include "GameScene.h"
using namespace cocos2d;

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	addChild(GameLayer::create(),-1);
	//addChild(GameShopLayer::create());
	//addChild(GameRebornLayer::create());
	return true;
}