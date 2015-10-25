#include "GameLayer.h"
// on "init" you need to initialize your instance
bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
	brid = nullptr;
	gold = nullptr;
	checkBorder = nullptr; 
	//myTimer = 0;
	sorce = 0;
	Pipline::piplineList.clear();
	scheduleUpdate();
	addBackgroundSprite();
	addWithPhysics();
	showGoldSprite();
	addUIButton();
	addBridWithAmination();
	addBall();
	addPiplineUp();
	addPiplineDown();
	//addcheckBorder();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	return true;
}
void GameLayer::addWithPhysics()
{
	auto node = Node::create();
	auto nodeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	node->setPhysicsBody(nodeBody);
	node->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	addChild(node, 0);
}

void GameLayer::addBackgroundSprite()
{
	auto backgroundSprite = Sprite::create("background.png");
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(backgroundSprite, -1);
}
void GameLayer::showGoldSprite()
{
	auto goldSprite = Sprite::create("gold.png");
	goldSprite->setPosition(Vec2(visibleSize.width / 2 + 135, visibleSize.height / 2 + 290));
	addChild(goldSprite, 100);
	showGoldNumber();
}
void GameLayer::showGoldNumber()
{
	//Game Data
	GameData::getInstance()->setCurrcertSource(0);
	int gpldNumber = GameData::getInstance()->getCurrcertSource();
	gold = LabelAtlas::create(String::createWithFormat("%d", gpldNumber)->_string, "balck.png", 19, 38, 48);
	gold->setAnchorPoint(Vec2(0.0f, 0.0f));
	gold->setPosition(Vec2(visibleSize.width / 2 + 135, visibleSize.height / 2 + 272));
	addChild(gold,101);
}
void GameLayer::addUIButton()
{
	auto pauseGameButton = MenuItemImage::create("btnPause.png", "btnPause.png", CC_CALLBACK_0(GameLayer::pauseGameCallBack, this));
	Menu * puaseGameMenu = Menu::create(pauseGameButton, nullptr);
	puaseGameMenu->setPosition(visibleSize.width / 2 - 170, visibleSize.height / 2 + 290);
	addChild(puaseGameMenu,100);
}
void GameLayer::pauseGameCallBack()
{
	pauseGane();
}
void GameLayer::pauseGane()
{
	addChild(GamePauseLayer::create());
	Director::getInstance()->pause();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);
}

void GameLayer::addBridWithAmination()
{
	brid = Brid::create();
	brid->setTag(bridTag);
	brid->setPhysicsConfiger();
	//brid->getPhysicsBody()->setDynamic(false);
	brid->setPosition(visibleSize.width / 2 , visibleSize.height / 2);
	addChild(brid);
}
void GameLayer::addBall()
{
	Ball * ball= Ball::create();
	ball->initWithFile("ball.png");
	ball->setPhysicsConfiger();
	ball->setTag(ballTag);
	addChild(ball);
}
void GameLayer::addPiplineUp()
{
	int distance = 0;
	for (size_t i = 0; i < 4; i++)
	{
		int dy = std::rand() % 150 - 50;
		Pipline * piplineUp = Pipline::create("bound_up.png");
		piplineUp->setPiplineState(Pipline::PiplineState::Top);
		piplineUp->setPhysicsConfiger();
		piplineUp->setTag(piplineTag);
		piplineUp->setPosition(Vec2(visibleSize.width+ 50 + distance, visibleSize.height + dy));
		addChild(piplineUp, 2);
		distance += 200;
		Pipline::piplineList.pushBack(piplineUp);

	}
}
void GameLayer::addPiplineDown()
{
	int distance = 0;
	for (size_t i = 0; i < 4; i++)
	{
		int dy = std::rand() % 150 - 50;
		Pipline * piplineDown = Pipline::create("bound_Down.png");
		piplineDown->setPiplineState(Pipline::PiplineState::Down);
		piplineDown->setPhysicsConfiger();
		piplineDown->setTag(piplineTag);
		piplineDown->setPosition(Vec2(visibleSize.width + 50 + distance, 0 + dy));
		addChild(piplineDown, 2);
		distance += 150;
    	//Pipline::piplineList.pushBack(piplineDown);
	}
}
void GameLayer::addcheckBorder()
{
	checkBorder = Sprite::create("Broder.png");
	auto body = PhysicsBody::createBox(checkBorder->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	body->setDynamic(false);
	body->setCategoryBitmask(0x01);
	body->setCollisionBitmask(0x01);
	body->setContactTestBitmask(0x01);
	checkBorder->setPhysicsBody(body);
	checkBorder->setTag(broderTag);
	checkBorder->setPosition(Vec2(visibleSize.width /2-100 , visibleSize.height/2));
	addChild(checkBorder);
}

void GameLayer::doGameOver()
{
	log("test test test");
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameOver::createScene()));
}
//
void GameLayer::doVisit()
{
	//int listSize = Pipline::piplineList.size();
	Vector<Pipline*>::iterator iter;
	for (iter = Pipline::piplineList.begin(); iter != Pipline::piplineList.end(); iter++)
	{
		Pipline *pip = (Pipline*)(*iter);
		if (pip->getPositionX() < -50)
		{
			sorce++;
			GameData::getInstance()->setCurrcertSource(sorce);
			gold->setString(String::createWithFormat("%d", GameData::getInstance()->getCurrcertSource())->_string);
			break;
		}
		//break;
	}
}

void GameLayer::updateSorce(float time)
{
	doVisit();
	//myTimer += time;
	//log("my timer %f", myTimer);
	/*if (myTimer >= 1)
	{
		myTimer = 0;
		sorce++;
		GameData::getInstance()->setCurrcertSource(sorce);
	}
	gold->setString(String::createWithFormat("%d", GameData::getInstance()->getCurrcertSource())->_string);*/
}
bool GameLayer::onContactBegin(PhysicsContact& contact)
{
	auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	if (nodeA->getTag() == bridTag && nodeB->getTag() == piplineTag
		|| nodeB->getTag() == bridTag && nodeA->getTag() == piplineTag)
	{
		GameAudio::getInstance()->playHitEffect();
		doGameOver();
	}
	else  if (nodeA->getTag() == bridTag && nodeB->getTag() == ballTag
		|| nodeB->getTag() == bridTag && nodeA->getTag() == ballTag)
	{
		GameAudio::getInstance()->playHitEffect();
		doGameOver();
	}
	//else if (nodeA->getTag() == ballTag && nodeB->getTag() == piplineTag
	//	|| nodeB->getTag() == ballTag && nodeA->getTag() == piplineTag)
	//{
	//	log("test");
	//}
	return true;
}

bool GameLayer::onTouchBegan(Touch * touch, Event * event)
{
	brid->getPhysicsBody()->setVelocity(Vect(0.0f,98.0f));
	return false;
}

void GameLayer::update(float dt)
{
	updateSorce(dt);
}
