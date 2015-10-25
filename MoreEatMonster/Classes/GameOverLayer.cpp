#include "GameOverLayer.h"
#include "ui\UIScrollView.h"
using namespace cocos2d;

bool GameOverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	addBackgroundSprite();
	showNewHistory();
	addHistorySorceShow();
	showreturnGameButton();
	showresatrtGameButton();
	return true;
}

void GameOverLayer::addBackgroundSprite()
{
	auto backgroundSprite = Sprite::create("gameOver/js_bejing.png");
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(backgroundSprite, -1);
}
void GameOverLayer::showNewHistory()
{
	auto newHistory = Sprite::create("gameOver/js_jilu.png");
	newHistory->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	addChild(newHistory);
	showNewHistoryNumber();
}
void GameOverLayer::showNewHistoryNumber()
{
	// Game Data
	int sorceNumber = GameData::getInstance()->getCurrcertSorce();
	LabelAtlas * labelNumber = LabelAtlas::create(String::createWithFormat("%d", sorceNumber)->_string, "gameOver/js_shuzi.png", 49, 75, 48);
	labelNumber->setAnchorPoint(Vec2(0.5, 0.5));
	labelNumber->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	addChild(labelNumber);
}
void GameOverLayer::addHistorySorceShow()
{
	auto history = Sprite::create("js_lishi.png");
	history->setPosition(Vec2(visibleSize.width / 2 - 50, visibleSize.height / 2 + 10));
	addChild(history);
	showHistorySorceNumber();
}
void GameOverLayer::showHistorySorceNumber()
{
	// Game Data
	int sorceNumber = 100;
	LabelAtlas * labelNumber = LabelAtlas::create(String::createWithFormat("%d", sorceNumber)->_string, "fh_shuzi.png", 22, 32, 48);
	labelNumber->setAnchorPoint(Vec2(0.0, 0.5));
	labelNumber->setPosition(Vec2(visibleSize.width / 2 + 50, visibleSize.height / 2  + 10));
	addChild(labelNumber);
}

void GameOverLayer::showreturnGameButton()
{
	MenuItemImage * retunGameButton = MenuItemImage::create("gameOver/anniu_fanhui.png", "gameOver/anniu_fanhui.png", CC_CALLBACK_0(GameOverLayer::retunGameButtonCallback, this));
	Menu * retunGameButtonMeun = Menu::create(retunGameButton, nullptr);
	retunGameButtonMeun->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 150));
	addChild(retunGameButtonMeun);
}
void GameOverLayer::retunGameButtonCallback()
{
	GameData::getInstance()->setCurrcertSorce(0);
	Director::getInstance()->replaceScene(TransitionCrossFade::create(1, GameScene::create()));
}
void GameOverLayer::showresatrtGameButton()
{
	auto restartGameButton = MenuItemImage::create("gameOver/anniu_chonglai.png", "gameOver/anniu_chonglai.png", CC_CALLBACK_0(GameOverLayer::restartGameButtonCallback, this));
	Menu * restartGameButtonMeun = Menu::create(restartGameButton, nullptr);
	restartGameButtonMeun->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 - 150));
	addChild(restartGameButtonMeun);
}
void GameOverLayer::restartGameButtonCallback()
{
	GameData::getInstance()->setCurrcertSorce(0);
	Director::getInstance()->replaceScene(TransitionCrossFade::create(1, GameStartScene::create()));
}