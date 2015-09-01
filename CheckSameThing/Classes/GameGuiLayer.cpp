#include "GameGuiLayer.h"
#include "GamePauseLayer.h"
#include "GameResultScene.h"
#include"GameTimer.h"
#include"GamePauseLayer.h"
#include"GameData.h"
#include"MapInfo.h"
#include"Matrix.h"
#include"Audio.h"
#include"GameLayer.h"
#include "CallAndroidMethod.h"

GameGuiLayer * GameGuiLayer::_instance = nullptr;
bool GameGuiLayer::addTime = false;
bool GameGuiLayer::help = false;
bool GameGuiLayer::refresh = false;

GameGuiLayer * GameGuiLayer::getInstance()
{
	if (_instance == 0)
	{
		_instance = new GameGuiLayer();
	}
	return _instance;
}
bool GameGuiLayer::init(){
	
	if (!Node::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//add pause btn to this layer
	MenuItemImage* start_btn = MenuItemImage::create("btn_bg_normal.png", "btn_bg_click.png", CC_CALLBACK_0(GameGuiLayer::pauseGame, this));
	Menu* start_game = Menu::create(start_btn, NULL);
	start_game->setPosition(50, visibleSize.height - 30);
	start_btn->setScale(0.8);
	this->addChild(start_game);

	auto stop = Sprite::create("stop.png");
	stop->setPosition(50, visibleSize.height - 30);
	stop->setScale(0.8);
	addChild(stop);

	//add progressbar
	float stime = GAMEDATA::getInstance()->gettime();
	//add help
	auto help = Menu::create();
	auto spriteNomal1 = Sprite::create("help.png");
	spriteNomal1->setScale(0.8, 0.8);
	auto spriteSelect1 = Sprite::create("help.png");
	spriteSelect1->setScale(0.9, 0.9);
	auto helptip = MenuItemSprite::create(spriteNomal1, spriteSelect1, CC_CALLBACK_0(GameGuiLayer::helpTip, this));
	helptip->setPosition(80, 65);
	help->addChild(helptip);
	help->setPosition(Point(0, 0));
	this->addChild(help);

	Sprite* helpbg = Sprite::create("numBG.png");
	helpbg->setPosition(100, 90);
	helpbg->setScale(0.8);
	addChild(helpbg);

	label1 = CCLabelTTF::create();
	ccColor3B color1;
	color1.r = 240;
	color1.g = 255;
	color1.b = 255;
	label1->setColor(color1);
	label1->setScale(1.2);
	label1->setPosition(100, 90);
	this->addChild(label1);

	notime = Sprite::create("no_time_hint.png");
	notime->setPosition(240, 360);
	notime->setVisible(false);
	addChild(notime);

	//add refresh
	auto refresh = Menu::create();
	auto spriteNomal2 = Sprite::create("refresh.png");
	spriteNomal2->setScale(0.8, 0.8);
	auto spriteSelect2 = Sprite::create("refresh.png");
	spriteSelect2->setScale(0.9, 0.9);
	auto refresh_btn = MenuItemSprite::create(spriteNomal2, spriteSelect2, CC_CALLBACK_0(GameGuiLayer::refreshBtn, this));
	refresh_btn->setPosition(390, 65);
	refresh->addChild(refresh_btn);
	refresh->setPosition(Point(0, 0));
	this->addChild(refresh);

	Sprite*refreshbg = Sprite::create("numBG.png");
	refreshbg->setPosition(410, 90);
	refreshbg->setScale(0.8);
	addChild(refreshbg);


	label2 = CCLabelTTF::create();
	ccColor3B color2;
	color2.r = 240;
	color2.g = 255;
	color2.b = 255;
	label2->setColor(color2);
	label2->setScale(1.2);
	label2->setPosition(410, 90);
	this->addChild(label2);
	GameTimer * m_timer = GameTimer::createTimer(stime+2);
	this->addChild(m_timer, 1);

	
	Ascore = LabelAtlas::create(String::createWithFormat("%d", 0)->_string, "percent.png", 16, 22, '0');
	Ascore->setPosition(Vec2(230,30));
	this->addChild(Ascore);

	scheduleUpdate();
	return true;
}

void GameGuiLayer:: updateScore(){
	CCLOG("updateScore");
	//add Ascore
	int Ascores = GAMEDATA::getInstance()->getAchievescore();
	int count = -1;//储存位数
	int i = 1;
	do
	{
		++count;
		i *= 10;
	} while (i <= Ascores);
	Ascore->setString(String::createWithFormat("%d", (int)Ascores)->_string);
	Ascore->setPosition(Vec2(230 - count * 16, 30));
}

void GameGuiLayer::pauseGame(){
	//stop layer
	Audio::getInstance()->playBtnEffect();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Layer* pause_layer = GamePauseLayer::create();
	pause_layer->setAnchorPoint(ccp(0, 0));
	pause_layer->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(pause_layer,2);
	GAMEDATA::getInstance()->setstate(1);
	
}

void GameGuiLayer::gotoResult(){
	Audio::getInstance()->timeover();
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameResultScene::create()));

}

void GameGuiLayer::update(float dt){

	if (GAMEDATA::getInstance()->updateScore){
		GAMEDATA::getInstance()->updateScore = false;
		updateScore();
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto right = ProgressTimer::create(Sprite::create("progressbar.png"));
	right->setType(ProgressTimer::Type::BAR);
	right->setScaleY(0.95f);
	right->setPosition(240, 712);
	auto to4 = ProgressTo::create(GAMEDATA::getInstance()->gettime(), 0);
	right->setMidpoint(ccp(0, 0));
	right->setBarChangeRate(ccp(1, 0));
	right->setPercentage(GAMEDATA::getInstance()->gettime() * 10);
	this->addChild(right, 0);
	right->runAction(to4);

	//add addtime
	auto addtime = Menu::create();
	auto spriteNomal = Sprite::create("addtime.png");
	spriteNomal->setScale(0.8, 0.8);
	auto spriteSelect = Sprite::create("addtime.png");
	spriteSelect->setScale(0.9, 0.9);
	auto add_time = MenuItemSprite::create(spriteNomal, spriteSelect, CC_CALLBACK_0(GameGuiLayer::addTimeBtn, this));
	add_time->setPosition(400, visibleSize.height - 80);
	addtime->addChild(add_time);
	addtime->setPosition(Point(0, 0));
	this->addChild(addtime);

	Sprite* timebg = Sprite::create("numBG.png");
	timebg->setPosition(435, visibleSize.height - 85);
	timebg->setScale(0.8);
	addChild(timebg);

	label = CCLabelTTF::create();
	ccColor3B color;
	color.r = 240;
	color.g = 255;
	color.b = 255;
	label->setColor(color);
	label->setScale(1.2);
	label->setPosition(435, visibleSize.height - 85);

	this->addChild(label);

	char* time = new char[100];
	int addtimenum = GAMEDATA::getInstance()->getaddtimeNum();

	if (addtimenum<0)
	{
		addtimenum == 0;
	}
	sprintf(time, "%d", addtimenum);
	label->setString(time);

	char* tip_num = new char[100];
	int tipnum = GAMEDATA::getInstance()->gettipNum();
	if (tipnum<0)
	{
		tipnum == 0;
	}
	sprintf(tip_num, "%d", tipnum);
	label1->setString(tip_num);

	char* refresh_num = new char[100];
	int refreshnum = GAMEDATA::getInstance()->getrefreshNum();
	if (refreshnum<0)
	{
		refreshnum == 0;
	}
	sprintf(refresh_num, "%d", refreshnum);
	label2->setString(refresh_num);

	//add tree
	auto tree = Sprite::create("tree.png");
	tree->setPosition(70, visibleSize.height - 140);
	tree->setScale(0.8);
	addChild(tree);


	// goto result scene
	float stime = GAMEDATA::getInstance()->gettime();
	if (stime<=3){
		notime->setVisible(true);
		
	}
	if (stime <= 2.5){
		notime->setVisible(false);

	}
	if (stime <= 2){
		notime->setVisible(true);

	}
	if (stime <= 1.5){
		notime->setVisible(false);

	}
	if (stime <= 1){
		notime->setVisible(true);

	}
	if (stime <= 0.5){
		notime->setVisible(false);

	}
	if (stime<0){
		GAMEDATA::getInstance()->settime(11);
		Audio::getInstance()->timeover();
		Director::getInstance()->replaceScene(TransitionFade::create(1, GameResultScene::create()));
	}

	
}

void GameGuiLayer::addTimeBtn(){
	Audio::getInstance()->playBtnEffect();
	int addtime = GAMEDATA::getInstance()->getaddtimeNum();
	int addtime1= addtime-1;

	if (addtime1 >0){
		GAMEDATA::getInstance()->setaddtimeNum(addtime1);
		addTime=true;
		GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() + 10);
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (addtime1 <=0){
		addTime=false;
		CallAndroidMethod::getInstance()->pay(10);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (addtime1 <= 0){
		GAMEDATA::getInstance()->setaddtimeNum(0);
		GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() );
		addTime = false;
	}
#endif
}

void GameGuiLayer::helpTip(){
	Audio::getInstance()->playBtnEffect();
	int  tip = GAMEDATA::getInstance()->gettipNum();
	if (tip > 0){
		GAMEDATA::getInstance()->settipNum(tip-1);
		help = true;
		GAMEDATA::getInstance()->needTipPos = true;
	}
	else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	
		help = false;
		CallAndroidMethod::getInstance()->pay(8);
#endif
	}


}

void GameGuiLayer::refreshBtn(){
	Audio::getInstance()->playBtnEffect();
	int cpunt = GAMEDATA::getInstance()->getrefreshNum();
	if (refresh >1){
		GAMEDATA::getInstance()->setrefreshNum(cpunt - 1);
		Sprite*sprite = Sprite::create("fresh.png");
		sprite->setPosition(240, 400);
		auto sp = Sequence::create(
			RotateBy::create(2.0f,360), FadeOut::create(0),
			nullptr);
		addChild(sprite, 2);
		sprite-> runAction(sp);
		refresh = true;
		//使用道具
		GAMEDATA::getInstance()->needResetMap = true;
		//道具个数减1
	}
	else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	
		refresh=false;
		CallAndroidMethod::getInstance()->pay(9);
#endif
	}

}






