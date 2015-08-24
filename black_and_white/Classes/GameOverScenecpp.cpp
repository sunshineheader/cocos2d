#include "cocos2d.h"
#include "GameOverScenecpp.h"
#include "GameOverLabel.h"

using namespace cocos2d;

Scene*GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}
bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->addChild(GameOverLabel::create());
	return true;
}


