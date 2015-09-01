#include "TopMenu.h"
#include "Chinese.h"
#include "GameData.h"
#include "GamePauseLayer.h"
#include "GameLayer.h"
#include "StarMatrix.h"
#include "SimpleAudioEngine.h"
#include "CallAndroidMethod.h"
#include "HelloWorldScene.h"
#include "Audio.h"

TopMenu* TopMenu::_instance = nullptr;
TopMenu::TopMenu(){
	this->init();
}

TopMenu* TopMenu::getInstance(){
	if(_instance == 0){
		_instance = new TopMenu();
	}
	return _instance;
}

bool TopMenu::init(){
	if(!Node::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/*highestScore = Label::create(
	ChineseWord("highestScore") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getHistoryScore())->_string,
	"Verdana-Bold",24
	);
	highestScore->setPosition(visibleSize.width/2,visibleSize.height/2+350);
	this->addChild(highestScore);*/
	rePlay =NULL;
	level = Label::create(
		ChineseWord("guanqia") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextLevel())->_string,
		"Verdana-Bold",24
		);
	level->setPosition(visibleSize.width/2-130,visibleSize.height/2+344);
	this->addChild(level);

	targetScore = Label::create(
		ChineseWord("mubiao") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextScore())->_string,
		"Verdana-Bold",24
		);
	targetScore->setPosition(visibleSize.width/2,visibleSize.height/2+344);
	this->addChild(targetScore);


	curScore = Label::create(
		cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getCurScore())->_string,
		"Verdana-Bold",50
		);
	curScore->setPosition(visibleSize.width/2,visibleSize.height/2 +300);
	this->addChild(curScore);

	auto goldBuyBtn = MenuItemImage::create(
		"gold_buy_normal.png","gold_buy_click.png",CC_CALLBACK_0(TopMenu::pay,this)
		);
	auto goldBuyMenu = Menu::create(goldBuyBtn, NULL);
	goldBuyMenu->setPosition(visibleSize.width/2+200,visibleSize.height-50);
	this->addChild(goldBuyMenu);

	playerGold =Label::create(String::createWithFormat("%d",
		GAMEDATA::getInstance()->getGoldNum())->_string,"Arial",24);
	playerGold->setPosition(visibleSize.width/2+170,visibleSize.height-56);
	playerGold->setAnchorPoint(Point(1,0.5));
	this->addChild(playerGold);

	MenuItemImage* PauseBtn = MenuItemImage::create(
		"pause.png","pause.png",CC_CALLBACK_0(TopMenu::PauseGame,this)
		);
	Menu* menuPause = Menu::create(PauseBtn, NULL);
	menuPause->alignItemsHorizontally();
	menuPause->setPosition(visibleSize.width/2-200,visibleSize.height/2+350);
	this->addChild(menuPause);

	MenuItemImage* giftBtn = MenuItemImage::create(
		"box.png","box.png",CC_CALLBACK_0(TopMenu::payGift,this)
		);
	auto scale1= ScaleTo::create(1.0f,0.7f);
	auto scale2= ScaleTo::create(1.0f,1.0f);
	auto seq =Sequence::create(scale1,scale2,nullptr);
	giftBtn->runAction(RepeatForever::create(seq));
	menuGift = Menu::create(giftBtn, NULL);
	menuGift->alignItemsHorizontally();
	menuGift->setAnchorPoint(Point(0.5,0.5));
	menuGift->setPosition(visibleSize.width/2+180,visibleSize.height-115);
	if(GAMEDATA::getInstance()->getIsBuySuperGift()){
		menuGift->setVisible(false);
	}
	this->addChild(menuGift);


	hammerBtn = MenuItemImage::create(
		"item_hammer_normal.png","item_hammer_click.png",CC_CALLBACK_0(TopMenu::usePropsHammer,this)
		);
	magicBtn = MenuItemImage::create(
		"item_magic_normal.png","item_magic_click.png",CC_CALLBACK_0(TopMenu::usePropsMagic,this)
		);
	rainbowBtn = MenuItemImage::create(
		"item_rearrange_normal.png","item_rearrange_click.png",CC_CALLBACK_0(TopMenu::usePropsRainBow,this)
		);
	bombBtn = MenuItemImage::create(
		"bomb_normal.png","bomb_click.png",CC_CALLBACK_0(TopMenu::usePropsBomb,this)
		);
	props = Menu::create(hammerBtn,magicBtn,rainbowBtn,bombBtn, NULL);
	props->alignItemsHorizontallyWithPadding(60);
	props->setPosition(visibleSize.width/2,visibleSize.height/2-346);
	props->setVisible(false);
	this->addChild(props);

	price_hammer = Label::create("800","Arial",18);
	price_hammer->setPosition(visibleSize.width/2-185,visibleSize.height/2 -385);
	price_hammer->setVisible(false);
	this->addChild(price_hammer);

	price_magic = Label::create("800","Arial",18);
	price_magic->setPosition(visibleSize.width/2-68,visibleSize.height/2 -385);
	price_magic->setVisible(false);
	this->addChild(price_magic);

	price_rainbow = Label::create("600","Arial",18);
	price_rainbow->setPosition(visibleSize.width/2+64,visibleSize.height/2 -385);
	price_rainbow->setVisible(false);
	this->addChild(price_rainbow);

	price_bomb = Label::create("1000","Arial",18);
	price_bomb->setPosition(visibleSize.width/2+179,visibleSize.height/2 -385);
	price_bomb->setVisible(false);
	this->addChild(price_bomb);

	propInfo =Label::create("","Verdana-Bold",18);
	propInfo->setPosition(visibleSize.width/2-20,visibleSize.height/2 -355);
	propInfo->setAlignment(TextHAlignment::CENTER);
	propInfo->setLineBreakWithoutSpace(true);
	propInfo->setWidth(220);
	propInfo->setVisible(false);
	this->addChild(propInfo);


	MenuItemImage* cancelBtn = MenuItemImage::create(
		"btn_cancel_normal.png","btn_cancel_click.png",CC_CALLBACK_0(TopMenu::cancelUseProp,this)
		);
	cancelBtn->setScaleX(0.6f);
	cancel = Menu::create(cancelBtn, NULL);
	cancel->setPosition(visibleSize.width/2+180,visibleSize.height/2-352);
	cancel->setVisible(false);
	this->addChild(cancel);
	return true;
}

void TopMenu::pay(){
	Audio::getInstance()->playClick();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CallAndroidMethod::getInstance()->pay(5);
#endif
}

void TopMenu::payGift(){
	if(!menuGift->isVisible()){
		return;
	}
	Audio::getInstance()->playClick();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CallAndroidMethod::getInstance()->pay(11);
#endif
}

void TopMenu::hideMenuGift(){
	menuGift->setVisible(false);
}

void TopMenu::refresh(int score){
	
	GAMEDATA* data = GAMEDATA::getInstance();
	data->setCurScore(data->getCurScore() + score);
	if(data->getCurScore() > data->getHistoryScore()){
		data->setHistoryScore(data->getCurScore());
	}
	char buf[64];
	sprintf(buf,"%d",data->getCurScore());
	curScore->setString(buf);
}


void TopMenu::refreshTargetScore(){
	targetScore->setString(ChineseWord("mubiao") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextScore())->_string);
	level->setString(ChineseWord("guanqia") + cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextLevel())->_string);
}

void TopMenu::cleanScore(){
	char buf[64];
	sprintf(buf,"%d",0);
	curScore->setString(buf);
	//highestScore->setString(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getHistoryScore())->_string);
	refreshGold();
}

void TopMenu::refreshGold(){
	playerGold->setString(String::createWithFormat("%d",GAMEDATA::getInstance()->getGoldNum())->_string);
}

void TopMenu::PauseGame(){
	Audio::getInstance()->playClick();
	gamePause = GamePauseLayer::create(this);
	this->addChild(gamePause,1);
}

void TopMenu::usePropsHammer(){
	Audio::getInstance()->playClick();
	auto gold =GAMEDATA::getInstance()->getGoldNum();
	if(gold>=800 || GAMEDATA::getInstance()->getChuiNum() > 0){
		if(!StarMatrix::HammerClick){
			StarMatrix::HammerClick=true;
			magicBtn->setVisible(false);
			rainbowBtn->setVisible(false);
			bombBtn->setVisible(false);
			propInfo->setString(ChineseWord("hammmer"));
			propInfo->setVisible(true);
			cancel->setVisible(true);
			price_hammer->setVisible(false);
			price_magic->setVisible(false);
			price_rainbow->setVisible(false);
			price_bomb->setVisible(false);
		}
	}else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->pay(6);
#endif
	}
}

void TopMenu::usePropsMagic(){
	Audio::getInstance()->playClick();
	auto gold =GAMEDATA::getInstance()->getGoldNum();
	if(gold>=800 || GAMEDATA::getInstance()->getBiNum() > 0){
		if(!StarMatrix::MagicClick){
			Size visibleSize = Director::getInstance()->getVisibleSize();
			StarMatrix::MagicClick=true;
			props->runAction(MoveTo::create(0.2,Point(visibleSize.width/2-124,visibleSize.height/2-352)));
			hammerBtn->setVisible(false);
			rainbowBtn->setVisible(false);
			bombBtn->setVisible(false);
			propInfo->setString(ChineseWord("pen"));
			propInfo->setVisible(true);
			cancel->setVisible(true);
			price_hammer->setVisible(false);
			price_magic->setVisible(false);
			price_rainbow->setVisible(false);
			price_bomb->setVisible(false);
		}
	}else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->pay(6);
#endif
	}
}

void TopMenu::usePropsRainBow(){
	Audio::getInstance()->playClick();
	auto gold =GAMEDATA::getInstance()->getGoldNum();
	if(gold>=600){
		if(!StarMatrix::RainBowClick){
			Size visibleSize = Director::getInstance()->getVisibleSize();
			StarMatrix::RainBowClick=true;
			props->runAction(MoveTo::create(0.2,Point(visibleSize.width/2-238,visibleSize.height/2-352)));
			hammerBtn->setVisible(false);
			magicBtn->setVisible(false);
			bombBtn->setVisible(false);
			propInfo->setString(ChineseWord("rainbow"));
			propInfo->setVisible(true);
			cancel->setVisible(true);
			price_hammer->setVisible(false);
			price_magic->setVisible(false);
			price_rainbow->setVisible(false);
			price_bomb->setVisible(false);
		}
	}else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->pay(6);
#endif
	}
}

void TopMenu::usePropsBomb(){
	Audio::getInstance()->playClick();
	auto gold =GAMEDATA::getInstance()->getGoldNum();
	if(gold>=1000){
		if(!(StarMatrix::BombClick)){
			Size visibleSize = Director::getInstance()->getVisibleSize();
			StarMatrix::BombClick=true;
			props->runAction(MoveTo::create(0.2,Point(visibleSize.width/2-364,visibleSize.height/2-352)));
			hammerBtn->setVisible(false);
			rainbowBtn->setVisible(false);
			magicBtn->setVisible(false);
			propInfo->setString(ChineseWord("bomb"));
			propInfo->setVisible(true);
			cancel->setVisible(true);
			price_hammer->setVisible(false);
			price_magic->setVisible(false);
			price_rainbow->setVisible(false);
			price_bomb->setVisible(false);
		}
	}else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->pay(6);
#endif
	}
}

void TopMenu::cancelUseProp(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	props->setPosition(visibleSize.width/2,visibleSize.height/2-352);
	StarMatrix::removeAnim=true;
	propInfo->setVisible(false);
	cancel->setVisible(false);
	magicBtn->setVisible(true);
	rainbowBtn->setVisible(true);
	hammerBtn->setVisible(true);
	bombBtn->setVisible(true);
	price_hammer->setVisible(true);
	price_magic->setVisible(true);
	price_rainbow->setVisible(true);
	price_bomb->setVisible(true);
}

void  TopMenu::hideProps(){
	props->setVisible(false);
	price_hammer->setVisible(false);
	price_magic->setVisible(false);
	price_rainbow->setVisible(false);
	price_bomb->setVisible(false);
}

void TopMenu::showProps(){
	props->setVisible(true);
	price_hammer->setVisible(true);
	price_magic->setVisible(true);
	price_rainbow->setVisible(true);
	price_bomb->setVisible(true);
}

void TopMenu::showRePaly(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	rePlay = Sprite::create("target_not_reach_bg.png");
	rePlay->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(rePlay);
	MenuItemImage* con = MenuItemImage::create("conti_reach_btn_normal.png","conti_reach_btn_click.png",CC_CALLBACK_0(TopMenu::rePlayResultSuccess,this));
	Menu* conMenu = Menu::create(con,NULL);
	conMenu->setAnchorPoint(ccp(0.5,0.5));
	conMenu -> setPosition(visibleSize.width/2-10,visibleSize.height/2-300);
	rePlay->addChild(conMenu);
	MenuItemImage* cancel = MenuItemImage::create("close_btn_normal.png","close_btn_click.png",CC_CALLBACK_0(TopMenu::rePlayResultFail,this));
	Menu* canMenu = Menu::create(cancel,NULL);
	canMenu-> setPosition(visibleSize.width/2+170,visibleSize.height/2-70);
	rePlay->addChild(canMenu);
	
}


void TopMenu::rePlayResultSuccess(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(NULL != rePlay ){
	   rePlay->removeFromParent();
	   rePlay= NULL;
	}
	if(GAMEDATA::getInstance()->getGoldNum()>=3000){
		GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()-3000);
	   GameLayer::needRevive=true;
       GameLayer::gameOver=false;
	}else{
		CallAndroidMethod::getInstance()->pay(7);
	}	
#endif
}

void TopMenu::rePlayResultFail(){
	if(NULL != rePlay ){
	   rePlay->removeFromParent();
	   rePlay= NULL;
	}
	GameLayer::needRevive=false;
    GameLayer::gameOver=true;
}
