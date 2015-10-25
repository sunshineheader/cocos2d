#include "GameOverLayer.h"

Scene * GameOver::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = GameOver::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
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
	addBackgroundSprite();
	addTitleSprite();
	addBridAimation();
	showCurrcertSorceSprite();
	showHistorySorceSprite();
	showCuccertGoldsNumberSprite();
	showBackButton();
	showRestartButton();
	return true;
}
void GameOver::addBackgroundSprite()
{
	auto backgroundSprite = Sprite::create("background.png");
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(backgroundSprite, -1);
}
void GameOver::addTitleSprite()
{
	BlinkTitle * title = BlinkTitle::create("title.png");
	title->setPosition(Vec2(120, visibleSize.height / 2 + 265));
	addChild(title);
}
void GameOver::addBridAimation()
{
	Brid *brid = Brid::create();
	brid->setPosition(Vec2(35, visibleSize.height / 2 + 290));
	//brid->initBridAmination();
	addChild(brid);
	auto scaleSmall = ScaleTo::create(0.8f, 0.8f);
	auto scaleBigger = ScaleTo::create(0.8f, 1.2f);
	auto delay = DelayTime::create(0.0f);
	auto squence = Sequence::create(scaleSmall, delay, scaleBigger, delay->clone(), nullptr);
	brid->runAction(RepeatForever::create(squence));
}
void GameOver::showCurrcertSorceSprite()
{
	auto currcert = Sprite::create("currcert.png");
	currcert->setPosition(Vec2(visibleSize.width / 2 - 80, visibleSize.height / 2 +30));
	addChild(currcert);
	sendCurrcertSorce();
}
void GameOver::sendCurrcertSorce()
{
	// Game Data
	int currcertSorceNumber = GameData::getInstance()->getCurrcertSource();
	LabelAtlas * CurrcertSorce = LabelAtlas::create(String::createWithFormat("%d", currcertSorceNumber)->_string, "white_number.png", 19, 38, 48);
	CurrcertSorce->setAnchorPoint(Vec2(0.0f, 0.5f));
	CurrcertSorce->setPosition(Vec2(visibleSize.width / 2 + 20, visibleSize.height / 2 + 30));
	addChild(CurrcertSorce);
}
void GameOver::showHistorySorceSprite()
{
	auto history = Sprite::create("history.png");
	history->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
	addChild(history);
	sendHistorySorce();
}
void GameOver::sendHistorySorce()
{
	// Game Data
	int history=GameData::getInstance()->CompareSorce();
	int historySorceNumber = history;
	LabelAtlas * historySorce = LabelAtlas::create(String::createWithFormat("%d", historySorceNumber)->_string, "white_number.png", 19, 38, 48);
	//historySorce->setAnchorPoint(Vec2(0.0f, 0.5f));
	historySorce->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 75));
	addChild(historySorce);
}

void GameOver::showCuccertGoldsNumberSprite()
{
	auto currcertGolds = Sprite::create("currcertGolds.png");
	currcertGolds->setPosition(Vec2(visibleSize.width / 2 - 80, visibleSize.height / 2 -55));
	addChild(currcertGolds);
	sendCuccertGoldsNumber();
}
void GameOver::sendCuccertGoldsNumber()
{
	// Game Data
	int goldnumber = 5 * GameData::getInstance()->getCurrcertSource();
	GameData::getInstance()->setGoldNumber(goldnumber);
	int CuccertGoldsNumber = GameData::getInstance()->SaveAllGolds();
	LabelAtlas * CuccertGolds = LabelAtlas::create(String::createWithFormat("%d", CuccertGoldsNumber)->_string, "white_number.png", 19, 38, 48);
	CuccertGolds->setAnchorPoint(Vec2(0.0f, 0.5f));
	CuccertGolds->setPosition(Vec2(visibleSize.width / 2 + 20, visibleSize.height / 2 - 55));
	addChild(CuccertGolds);
}
void GameOver::showBackButton()
{
	auto backGameButton = MenuItemImage::create("back_normal.png", "back_selected.png", CC_CALLBACK_0(GameOver::backButtonCallBack, this));
	auto backMenu = Menu::create(backGameButton, nullptr);
	backMenu->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 200));
	addChild(backMenu);
}
void GameOver::backButtonCallBack()
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameStart::createScene()));
}
void GameOver::showRestartButton()
{
	auto restartGameButton = MenuItemImage::create("restart_normal.png", "restart_seclcted.png", CC_CALLBACK_0(GameOver::reStartButtonCallBack, this));
	auto restartMenu = Menu::create(restartGameButton, nullptr);
	restartMenu->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 -200));
	addChild(restartMenu);
}
void GameOver::reStartButtonCallBack()
{
	auto scene = GameScene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -98.0f));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = GameLayer::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}
void GameOver::upadte(float dt)
{
}
