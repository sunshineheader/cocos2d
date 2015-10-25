#include "GameLayer.h"
USING_NS_CC;

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	
	border = nullptr;
	monsterSpriteUp = nullptr;
	monsterSptiteDown = nullptr;
	checkSprite = nullptr;
	ball = nullptr;
	ratation = 90;
	currcertSorce = 0;
	CurrcertSorce = nullptr;
	currcertSpeed = 0;
	scheduleUpdate();
	genCheckBorder();
	addBackgroundSprite();
	addPauseGameButton();
	showCurrcertSorceSprite();
	genMonster();
	genBorder();
	genBall();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void GameLayer::addBackgroundSprite()
{
	auto backgroundSprite = Sprite::create("beijing.png");
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(backgroundSprite, -1);
}
void GameLayer::addPauseGameButton()
{
	MenuItemImage * pauseGameButton = MenuItemImage::create("anniu_zt.png", "anniu_zt.png", CC_CALLBACK_0(GameLayer::pauseGameCallback, this));
	Menu * pauseGameMenu = Menu::create(pauseGameButton, nullptr);
	pauseGameMenu->setPosition(Vec2(visibleSize.width / 2 - 200, visibleSize.height / 2 + 330));
	addChild(pauseGameMenu);
}
void GameLayer::pauseGameCallback()
{
	Director::getInstance()->pause();
	addChild(GamePause::create());
}
void GameLayer::showCurrcertSorceSprite()
{
	auto sorcce = Sprite::create("yx_defen.png");
	sorcce->setPosition(Vec2(visibleSize.width / 2 + 120, visibleSize.height / 2 + 330));
	addChild(sorcce);
	showCurrcertSorceNumber();
}
void GameLayer::showCurrcertSorceNumber()
{
	// GameData
//	GameData::getInstance()->setCurrcertSorce(10000);
    currcertSorce = GameData::getInstance()->getCurrcertSorce();
	CurrcertSorce = LabelAtlas::create(String::createWithFormat("%d", currcertSorce)->_string, "yx_shuzi.png", 18, 24, 48);
	CurrcertSorce->setAnchorPoint(Vec2(0.0, 0.5));
	CurrcertSorce->setPosition(Vec2(visibleSize.width / 2 + 120, visibleSize.height / 2 + 330));
	addChild(CurrcertSorce);
}

void GameLayer::genBall()
{
	ball = Ball::create();
	ball->initWithFile("gameObjects/qiu.png");
	ball->addBall();
	addChild(ball);
}
void GameLayer::genMonster()
{
	monsterSpriteUp = Sprite::create("gameObjects/monster_2.png");
	monsterSpriteUp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(monsterSpriteUp);
	monsterSptiteDown = Sprite::create("gameObjects/monster_1.png");
	monsterSptiteDown->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	monsterSptiteDown->setVisible(false);
	addChild(monsterSptiteDown);
}

void GameLayer::genBorder()
{
	border = Border::create();
	border->initWithFile("gameObjects/yx_quan.png");
	border->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(border);
}

void GameLayer::genCheckBorder()
{
	checkSprite = Sprite::create("check.png");
	checkSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(checkSprite);
}

void GameLayer::update(float dt)
{
	// Ìí¼Ó¶¯»­
	monsterSpriteUp->setVisible(true);
	monsterSptiteDown->setVisible(false);
	if (ball->getBoundingBox().intersectsCircle(visibleSize/2,8))
	{
		monsterSptiteDown->setVisible(true);
		monsterSpriteUp->setVisible(false);
		ball->getBallState();
		ball->addBall();
		updateSorce();
	}
	if (ball->getBoundingBox().intersectsRect(checkSprite->getBoundingBox()))
	{
		Director::getInstance()->replaceScene(TransitionFade::create(0.02, GameOverScene::create()));
	}
	updateSpeed();

}

bool GameLayer::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	border->setRotation(ratation);
	checkSprite->setRotation(ratation);
	ratation += 90;
	return false;
}

void GameLayer::updateSorce()
{
	currcertSorce++;
	GameData::getInstance()->setCurrcertSorce(currcertSorce);
	CurrcertSorce->setString(String::createWithFormat("%d", GameData::getInstance()->getCurrcertSorce())->_string);
}
void GameLayer::updateSpeed()
{
	currcertSpeed = GameData::getInstance()->getBallSpeed();
	if (currcertSorce%10==9)
	{
		currcertSpeed += 2;
		ball->setBallSpeed(currcertSpeed);
	}
}