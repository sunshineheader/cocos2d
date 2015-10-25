#include "GameScene.h"

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	addChild(GameLayer::create());
	return true;
}
