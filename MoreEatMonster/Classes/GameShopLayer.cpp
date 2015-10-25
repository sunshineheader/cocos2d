#include "GameShopLayer.h"
USING_NS_CC_EXT;
using namespace cocos2d;

bool GameShopLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	addBackgroundSprite();
	addCloseButton();
	addGoldNumber();
	addRectArea();
	return true;
}
void GameShopLayer::addBackgroundSprite()
{
	auto backgroundSprite = Sprite::create("gameShop/sc.png");
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2-50));
	addChild(backgroundSprite, -1);
}

void GameShopLayer::addCloseButton()
{
	MenuItemImage * closeButton = MenuItemImage::create("gameShop/anniu_gb.png", "gameShop/anniu_gb.png", CC_CALLBACK_0(GameShopLayer::closeButtonCallback, this));
	Menu * closeButtonMenu = Menu::create(closeButton, nullptr);
	closeButtonMenu->setPosition(Vec2(visibleSize.width / 2 + 180, visibleSize.height / 2 +220));
	addChild(closeButtonMenu);
}

void GameShopLayer::closeButtonCallback()
{
	removeFromParent();
}

void GameShopLayer::addRectArea()
{
	auto rectArea = Sprite::create("gameShop/sc_lan.png");
	rectArea->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2));
	addChild(rectArea);

	auto goldSprite = Sprite::create("gameShop/sc_jinbi.png");
	goldSprite->setPosition(Vec2(visibleSize.width / 2-150, visibleSize.height / 2));
	addChild(goldSprite);
}

void GameShopLayer::addGoldNumber()
{
	auto goldSprite = Sprite::create("gameShop/sc_jinbikuang.png");
	goldSprite->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2+160));
	addChild(goldSprite);
	showGoldNumber();
}
void GameShopLayer::showGoldNumber()
{
	// GameData
	int goldNumber = 1000;
	LabelAtlas * goldLabel = LabelAtlas::create(String::createWithFormat("%d", goldNumber)->_string, "gameShop/sc_shuzi.png",14,19,48);
	goldLabel->setAnchorPoint(Vec2(0.0, 0.5));
	goldLabel->setPosition(Vec2(visibleSize.width / 2 - 120, visibleSize.height / 2 + 157));
	addChild(goldLabel);
}