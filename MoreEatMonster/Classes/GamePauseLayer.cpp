#include "GamePauseLayer.h"
bool GamePause::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	contiueGameSprite();
	restartGameSprite();
	return true;
}
void GamePause::contiueGameSprite()
{
	auto contiueGameSprite = MenuItemImage::create("gamePause/anniu_jixu.png", "gamePause/anniu_jixu.png", CC_CALLBACK_0(GamePause::contiueGameCallback,this));
	auto menu = Menu::create(contiueGameSprite, nullptr);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	addChild(menu);
}
void GamePause::contiueGameCallback()
{
	removeFromParent();
	Director::getInstance()->resume();
}

void GamePause::restartGameSprite()
{
	auto restartGameSprite = MenuItemImage::create("gamePause/anniu_chongxin.png", "gamePause/anniu_chongxin.png", CC_CALLBACK_0(GamePause::restartGameCallback, this));
	auto menu = Menu::create(restartGameSprite, nullptr);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
	addChild(menu);
}

void GamePause::restartGameCallback()
{
	removeFromParent();
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(1, GameStartScene::create()));
}