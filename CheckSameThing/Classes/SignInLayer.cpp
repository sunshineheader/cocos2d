#include"SignInLayer.h"
#include"GameData.h"
#include"GameScene.h"
#include"LobbyScene.h"
using namespace cocos2d;
SignInLayer* SignInLayer::_instance = nullptr;
SignInLayer::SignInLayer(){
	this->init();
}

SignInLayer* SignInLayer::getInstance(){
	if (_instance == 0){
		_instance = new SignInLayer();
	}
	return _instance;
}




bool SignInLayer::init()
{
	if (!Node::init()){
		return false;
	}

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(SignInLayer::onTouchBegan, this);


	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//addBG
	Sprite* sign_layer = Sprite::create("pause_bg.png");
	this->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(sign_layer);
	//add signin

	auto signInbg = Sprite::create("qwindow.png");
	signInbg->setPosition(12, 0);
	this->addChild(signInbg);

	auto title = Sprite::create("qeveryday.png");
	title->setPosition(12, 210);
	this->addChild(title);

	auto itemBg1 = Sprite::create("qget.png");
	itemBg1->setPosition(-118, 125);
	this->addChild(itemBg1);

	auto day1 = Sprite::create("qone.png");
	day1->setPosition(-118, 180);
	day1->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(day1);

	auto goldPack1 = Sprite::create("qrefresh.png");
	goldPack1->setPosition(-118, 115);
	this->addChild(goldPack1);

	auto itemGoldNum1 = Sprite::create("qoneD.png");
	itemGoldNum1->setPosition(-118, 70);
	itemGoldNum1->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(itemGoldNum1);

	auto itemBg2 = Sprite::create("qget.png");
	itemBg2->setPosition(-33, 125);
	this->addChild(itemBg2);

	auto day2 = Sprite::create("qtwo.png");
	day2->setPosition(-33, 180);
	day2->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(day2);

	auto goldPack2 = Sprite::create("qtip.png");
	goldPack2->setPosition(-33, 115);
	this->addChild(goldPack2);

	auto itemGoldNum2 = Sprite::create("qtwoD.png");
	itemGoldNum2->setPosition(-33, 70);
	itemGoldNum2->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(itemGoldNum2);

	auto itemBg3 = Sprite::create("qget.png");
	itemBg3->setPosition(52, 125);
	this->addChild(itemBg3);

	auto day3 = Sprite::create("qthree.png");
	day3->setPosition(52, 180);
	day3->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(day3);

	auto goldPack3 = Sprite::create("qtime.png");
	goldPack3->setPosition(52, 115);
	this->addChild(goldPack3);

	auto itemGoldNum3 = Sprite::create("qthreeD.png");
	itemGoldNum3->setPosition(52, 70);
	itemGoldNum3->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(itemGoldNum3);

	auto itemBg4 = Sprite::create("qget.png");
	itemBg4->setPosition(137, 125);
	this->addChild(itemBg4);

	auto day4 = Sprite::create("qfour.png");
	day4->setPosition(137, 180);
	day4->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(day4);

	auto goldPack4 = Sprite::create("qtime.png");
	goldPack4->setPosition(137, 115);
	this->addChild(goldPack4);

	auto itemGoldNum4 = Sprite::create("qfourD.png");
	itemGoldNum4->setPosition(137, 70);
	itemGoldNum4->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(itemGoldNum4);

	auto itemBg5 = Sprite::create("qget.png");
	itemBg5->setPosition(-118, -25);
	this->addChild(itemBg5);

	auto day5 = Sprite::create("qfive.png");
	day5->setPosition(-118, 30);
	day5->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(day5);

	auto goldPack5 = Sprite::create("qrefresh.png");
	goldPack5->setPosition(-118, -35);
	this->addChild(goldPack5);

	auto itemGoldNum5 = Sprite::create("qfiveD.png");
	itemGoldNum5->setPosition(-118, -80);
	itemGoldNum5->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(itemGoldNum5);

	auto itemBg6 = Sprite::create("qget.png");
	itemBg6->setPosition(-33, -25);
	this->addChild(itemBg6);

	auto day6 = Sprite::create("qsix.png");
	day6->setPosition(-33, 30);
	day6->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(day6);

	auto goldPack6 = Sprite::create("qtip.png");
	goldPack6->setPosition(-33, -35);
	this->addChild(goldPack6);

	auto itemGoldNum6 = Sprite::create("qsixD.png");
	itemGoldNum6->setPosition(-33, -80);
	itemGoldNum6->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(itemGoldNum6);


	auto itemBg7 = Sprite::create("qget.png");
	itemBg7->setPosition(52, -25);
	this->addChild(itemBg7);

	auto day7 = Sprite::create("qseven.png");
	day7->setPosition(52, 30);
	day7->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(day7);

	auto goldPack7 = Sprite::create("qtime.png");
	goldPack7->setPosition(52, -35);
	this->addChild(goldPack7);

	auto itemGoldNum7 = Sprite::create("qsevenD.png");
	itemGoldNum7->setPosition(52, -80);
	itemGoldNum7->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(itemGoldNum7);

	//add jiangli
	int  m = GAMEDATA::getInstance()->getTimes();
	auto signedBg = Sprite::create("sign_out_shine_bg.png");
	signedBg->setPosition(-118, 125);
	signedBg->setScale(0.65);

	auto signedBg1 = Sprite::create("sign_out_shine_bg.png");
	signedBg1->setPosition(-33, 125);
	signedBg1->setScale(0.65);

	auto signedBg2 = Sprite::create("sign_out_shine_bg.png");
	signedBg2->setPosition(52, 125);
	signedBg2->setScale(0.65);

	auto signedBg3 = Sprite::create("sign_out_shine_bg.png");
	signedBg3->setPosition(137, 125);
	signedBg3->setScale(0.65);

	auto signedBg4 = Sprite::create("sign_out_shine_bg.png");
	signedBg4->setPosition(-118, -25);
	signedBg4->setScale(0.65);
	switch (m%7)
	{
	case 0:
	{auto hasSignMark = Sprite::create("sing_in_shine_bg.png");
	hasSignMark->setPosition(-118, 125);
	hasSignMark->setScale(0.65);
	this->addChild(hasSignMark); }
		break;

	case 1:
	{
	auto hasSignMark = Sprite::create("sing_in_shine_bg.png");
	hasSignMark->setPosition(-33, 125);
	hasSignMark->setScale(0.65);
	this->addChild(signedBg);
	this->addChild(hasSignMark); }
		break;

	case 2:
	{
	auto hasSignMark = Sprite::create("sing_in_shine_bg.png");
	hasSignMark->setPosition(52, 125);
	hasSignMark->setScale(0.65);
	this->addChild(signedBg);
	this->addChild(signedBg1);
	this->addChild(hasSignMark); }
		break;

	case 3:
	{
	auto hasSignMark = Sprite::create("sing_in_shine_bg.png");
	hasSignMark->setPosition(137, 125);
	hasSignMark->setScale(0.65);
	this->addChild(signedBg);
	this->addChild(signedBg1);
	this->addChild(signedBg2);
	this->addChild(hasSignMark); }
		break;

	case 4:
	{
	auto hasSignMark = Sprite::create("sing_in_shine_bg.png");
	hasSignMark->setPosition(-118, -25);
	hasSignMark->setScale(0.65);
	this->addChild(signedBg);
	this->addChild(signedBg1);
	this->addChild(signedBg2);
	this->addChild(signedBg3);
	this->addChild(hasSignMark); }
		break;

	case 5:
	{
	auto hasSignMark = Sprite::create("sing_in_shine_bg.png");
	hasSignMark->setPosition(-33, -25);
	hasSignMark->setScale(0.65);
	this->addChild(signedBg);
	this->addChild(signedBg1);
	this->addChild(signedBg2);
	this->addChild(signedBg3);
	this->addChild(signedBg4);
	this->addChild(hasSignMark); }
		break;

	case 6:
	{
	auto signedBg5 = Sprite::create("sign_out_shine_bg.png");
	signedBg5->setPosition(-33, -25);
	signedBg5->setScale(0.65);
	auto hasSignMark = Sprite::create("sing_in_shine_bg.png");
	hasSignMark->setPosition(52, -25);
	hasSignMark->setScale(0.65);
	this->addChild(signedBg);
	this->addChild(signedBg1);
	this->addChild(signedBg2);
	this->addChild(signedBg3);
	this->addChild(signedBg4);
	this->addChild(signedBg5);
	this->addChild(hasSignMark); }
		break;

	
	default:
		break;
	}
	
	

	//add getgift

	auto getgift = Menu::create();
	auto getNormal = Sprite::create("qgetgift.png");
	getNormal->setScale(0.7, 0.7);
	auto getSelected = Sprite::create("qgetgift.png");
	getSelected->setScale(0.8, 0.8);
	auto get = MenuItemSprite::create(getNormal, getSelected, CC_CALLBACK_0(SignInLayer::geteveryGift, this));
	get->setPosition(52,-150);
	getgift->setAnchorPoint(Point(0.5, 0.5));
	getgift->addChild(get);
	getgift->setPosition(Point(0.5, 0.5));

	this->addChild(getgift);

	return true;

}

void SignInLayer::geteveryGift(){
	
	GAMEDATA::getInstance()->setTimes(GAMEDATA::getInstance()->getTimes() + 1);
	GAMEDATA::getInstance()->setLoginTimes(GAMEDATA::getInstance()->getLoginTimes()+1);

	int n = GAMEDATA::getInstance()->getTimes();
	
	switch (n)
	{
	case 1:
		GAMEDATA::getInstance()->setrefreshNum(GAMEDATA::getInstance()->getrefreshNum() + 2);
		break;
	case 2:
		GAMEDATA::getInstance()->settipNum(GAMEDATA::getInstance()->gettipNum() + 2);
		break;
	case 3:
		GAMEDATA::getInstance()->setaddtimeNum(GAMEDATA::getInstance()->getaddtimeNum() + 2);
		break;
	case 4:
		GAMEDATA::getInstance()->setaddtimeNum(GAMEDATA::getInstance()->getaddtimeNum() + 3);
		break;
	case 5:
		GAMEDATA::getInstance()->setrefreshNum(GAMEDATA::getInstance()->getrefreshNum() + 5);
		break;
	case 6:
		GAMEDATA::getInstance()->settipNum(GAMEDATA::getInstance()->gettipNum() + 5);
		break;
	case 7:
		GAMEDATA::getInstance()->setaddtimeNum(GAMEDATA::getInstance()->getaddtimeNum() + 5);
		break;
	default:
		break;
	}
	this->resume();
	this->removeAllChildrenWithCleanup(true);
//	Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::createScene()));
	

}

void SignInLayer::update(float dt){
	
	
}


//´¥Ãþº¯ÊýccTouchBegan£¬·µ»Øtrue
bool SignInLayer::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return true;
}

