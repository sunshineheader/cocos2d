#include "GameRebornLayer.h"
using namespace cocos2d;

bool GameRebornLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	addBackgroundSprite();
	addTextSprite();
	addSureButton();
	addRebornGoldNumber();
	addProgressBar();
	return true;
}
void GameRebornLayer::addBackgroundSprite()
{
	auto backgroundSprite = Sprite::create("gameReborn/tc.png");
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	addChild(backgroundSprite, -1);
}

void GameRebornLayer::addTextSprite()
{
	auto textSprite = Sprite::create("gameReborn/fh.png");
	textSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 170));
	addChild(textSprite);
}
void GameRebornLayer::addSureButton()
{
	MenuItemImage * sureButton = MenuItemImage::create("gameReborn/anniu_queding.png", "gameReborn/anniu_queding.png", CC_CALLBACK_0(GameRebornLayer::sureButtonCallback, this));
	Menu * sureButtonMenu = Menu::create(sureButton, nullptr);
	sureButtonMenu->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2 ));
	addChild(sureButtonMenu);
}
void GameRebornLayer::sureButtonCallback()
{

}
void GameRebornLayer::addRebornGoldNumber()
{
	auto goldSprite = Sprite::create("gameReborn/jinbi.png");
	goldSprite->setPosition(Vec2(visibleSize.width / 2 - 50, visibleSize.height / 2 + 110));
	addChild(goldSprite);
	showRebornGoldNumber();
}
void GameRebornLayer::showRebornGoldNumber()
{
	// GameData
	int goldNumber = 1000;
	LabelAtlas * goldLabel = LabelAtlas::create(String::createWithFormat("%d", goldNumber)->_string, "gameReborn/fh_shuzi.png", 22, 32, 48);
	goldLabel->setAnchorPoint(Vec2(0.0, 0.5));
	goldLabel->setPosition(Vec2(visibleSize.width / 2 - 20, visibleSize.height / 2 + 110));
	addChild(goldLabel);
}
void GameRebornLayer::addProgressBar()
{
	auto exepricesProgressBg = Sprite::create("gameReborn/fh_jdt2.png");
	exepricesProgressBg->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2 + 60));
	addChild(exepricesProgressBg);
	auto exepricesProgress = Sprite::create("gameReborn/fh_jdt3.png");

	ProgressTimer * progroessTimer = ProgressTimer::create(exepricesProgress);
	progroessTimer->setType(ProgressTimerType::BAR);
	progroessTimer->setMidpoint(Vec2(0, 0));
	progroessTimer->setBarChangeRate(Vec2(1, 0));
	progroessTimer->setPosition(Vec2(visibleSize.width / 2-13, visibleSize.height / 2 + 60));
	addChild(progroessTimer, 100);
	progroessTimer->setPercentage(100.0f);
}
