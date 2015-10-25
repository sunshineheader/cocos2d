#include "GamePauseLayer.h"


bool GamePauseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	scheduleUpdate();
	addBackgroundSprite();
	addContuineGameButton();
	addBackGameButton();
	return true;
}

void GamePauseLayer::update(float dt)
{

}
void GamePauseLayer::addBackgroundSprite()
{
	auto backgroundSprite = Sprite::create("PauseLayerBg.png");
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(backgroundSprite, -1);
}

void GamePauseLayer::addContuineGameButton()
{
	auto contuineGameButton = MenuItemImage::create("contiune_normal.png", "contiune_selected.png", CC_CALLBACK_0(GamePauseLayer::ContuineGameCallBack, this));
	auto contuineMenu = Menu::create(contuineGameButton, nullptr);
	contuineMenu->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 - 200));
	addChild(contuineMenu);
}
void GamePauseLayer::ContuineGameCallBack()
{
	removeAndRemuse();
}
void GamePauseLayer::addBackGameButton()
{
	auto backGameButton = MenuItemImage::create("back_normal.png", "back_selected.png", CC_CALLBACK_0(GamePauseLayer::ContuineGameCallBack, this));
	auto backMenu = Menu::create(backGameButton, nullptr);
	backMenu->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 200));
	addChild(backMenu);
}
void GamePauseLayer::BackGameCallBack()
{
	removeAndRemuse();
}

void GamePauseLayer::removeAndRemuse()
{
	Director::getInstance()->resume();
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent(), true);
	removeFromParent();
}