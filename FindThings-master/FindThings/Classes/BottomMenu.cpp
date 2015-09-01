#include "BottomMenu.h"
#include "Chinese.h"
#include "GameOverScene.h"
#include "GameData.h"
#include "GameState.h"
#include "CallAndroidMethod.h"
#include "Audio.h"


BottomMenu* BottomMenu::instance=NULL;
bool BottomMenu::clickFindBtn = false;
bool BottomMenu::clickTimeBtn = false;

BottomMenu* BottomMenu::getInstance(){
	if (instance == NULL){
		instance = new BottomMenu();
		instance->init();
	}
	return instance;
}

bool BottomMenu::init(){
	if(!Node::init()){
		return false;
	}
	auto visibleSize= Director::getInstance()->getVisibleSize();

	Sprite* prop_bg = Sprite::create("prop_bg.png");
	prop_bg->setPosition(120,30);
	this->addChild(prop_bg,2);

	Button* quickFind = Button::create("quick_find.png","quick_find.png");
	quickFind->setPosition(ccp(62,32));
	quickFind->addTouchEventListener(CC_CALLBACK_2(BottomMenu::findTouchEvent, this));
	this->addChild(quickFind,3);

	find_prop_num = LabelAtlas::create(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getPropFindNum())->_string,"prop_number.png",20,30,'0');
	find_prop_num->setPosition(87,16);
	this->addChild(find_prop_num,3);

	Button* plusTime = Button::create("plus_time.png","plus_time.png");
	plusTime->setPosition(ccp(158,32));
	plusTime->addTouchEventListener(CC_CALLBACK_2(BottomMenu::timeTouchEvent, this));
	this->addChild(plusTime,3);

	time_prop_num = LabelAtlas::create(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getPropTimeNum())->_string,"prop_number.png",20,30,'0');
	time_prop_num->setPosition(182,16);
	this->addChild(time_prop_num,3);  

	Sprite* score_bg = Sprite::create("prop_bg.png");
	score_bg->setPosition(380,30);
	this->addChild(score_bg,2);

	Sprite* score = Sprite::create("jilu.png");
	score->setScale(0.8);
	score->setPosition(Point(visibleSize.width/2-45,10));
	score->setAnchorPoint(Point(1,0));
	this->addChild(score,3);

	curScore = LabelAtlas::create(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getScore())->_string,"prop_number.png",20,30,'0');
	curScore->setPosition(Point(visibleSize.width/2+5,10));
	curScore->setAnchorPoint(Point(1,0));
	this->addChild(curScore,3);

	Sprite* split = Sprite::create("split.png");
	split->setAnchorPoint(ccp(0,0));
	split->setPosition(visibleSize.width/2+5,10);
	this->addChild(split,3); 

	record = LabelAtlas::create(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getRecord())->_string,"prop_number.png",20,30,'0');
	record->setPosition(Point(visibleSize.width/2+25,10));
	record->setAnchorPoint(Point(0,0));
	this->addChild(record,3);

	Sprite* time_bg = Sprite::create("task_bg.png");
	time_bg->setPosition(visibleSize.width-100,25);
	this->addChild(time_bg,2);

	Sprite* timeTitle = Sprite::create("shijian.png");
	timeTitle->setScale(0.8);
	timeTitle->setPosition(Point(visibleSize.width-160,10));
	timeTitle->setAnchorPoint(Point(0,0));
	this->addChild(timeTitle,3);

	gameTime = LabelAtlas::create(cocos2d::String::createWithFormat("%d",playTime)->_string,"prop_number.png",20,30,'0');
	gameTime->setPosition(Point(visibleSize.width-85,12));
	gameTime->setAnchorPoint(Point(0,0));
	this->addChild(gameTime,3);
	return true;
}


void BottomMenu::initGameTime(){
	playTime=TOTALTIME;
	gameTime->setString(cocos2d::String::createWithFormat("%d",playTime)->_string);
	schedule(schedule_selector(BottomMenu::updateTime), 1.0f, kRepeatForever, 0);
	curScore->setString(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getScore())->_string);
	record->setString(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getRecord())->_string);
}

void BottomMenu::updateScore(){
	curScore->setString(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getScore())->_string);
}

void BottomMenu::updatePropNum(){
	find_prop_num->setString(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getPropFindNum())->_string);
	time_prop_num->setString(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getPropTimeNum())->_string);
}

void BottomMenu::updateTime(float dt){
	if(playTime!=0 && !GAMESTATE::getInstance()->getGamePause()){
		playTime--;
	}else{
		return;
	}
	//倒计时显示
	if(playTime <= 5 && playTime > 0){
		Audio::getInstance()->playSound(COUNTDOWN);//倒计时音效
		//倒计时动画显示
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Sprite* count_down = Sprite::create("count_down.png");
		count_down->setPosition(visibleSize.width/2,visibleSize.height/2);
		this->addChild(count_down,1);
		CCBlink*  action = CCBlink::create(1,1);
		CCCallFunc* callback =  CCCallFunc::create([=](){
			count_down->removeFromParentAndCleanup(true);
		});
		Sequence* seq = Sequence::create(action,callback,NULL);
		count_down->runAction(seq);
	}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(playTime<=TOTALTIME/2&&playTime>0){
		//可以触发提示计费点
		auto current = GAMEDATA::getInstance()->getCurrentTime();
		auto last = GAMEDATA::getInstance()->getLastClikTime();
		if(current-last>5000 && !GAMESTATE::getInstance()->getIsShowPayFind()){
			if(!GAMESTATE::getInstance()->getIsPaying()){
				GAMESTATE::getInstance()->setGamePause(true);
				GAMESTATE::getInstance()->setIsShowPayFind(true);
				CallAndroidMethod::getInstance()->pay(3);
				GAMESTATE::getInstance()->setIsPaying(true);
			}
		}
	}
	//弹出增加时间计费点
	if(playTime<10 && !GAMESTATE::getInstance()->getIsShowPayTime()){
		if(!GAMESTATE::getInstance()->getIsPaying()){
			GAMESTATE::getInstance()->setGamePause(true);
			GAMESTATE::getInstance()->setIsShowPayTime(true);
			CallAndroidMethod::getInstance()->pay(4);
			GAMESTATE::getInstance()->setIsPaying(true);
		}
	}
	//game over 复活计费点
	if(playTime<=0){		
		if(!GAMESTATE::getInstance()->getIsPaying()){
			GAMESTATE::getInstance()->setGamePause(true);
			CallAndroidMethod::getInstance()->pay(2);
			GAMESTATE::getInstance()->setIsPaying(true);
		}
	}
	//弹出消除物品的成绩计费点
	if(GAMEDATA::getInstance()->getScore()%20==0 && GAMEDATA::getInstance()->getScore()>=20){
		auto lag = (GAMEDATA::getInstance()->getScore()/20)%3;
		if(lag == 1 &&  GAMEDATA::getInstance()->getFindTimes()==0){
			//送20秒
			if(!GAMESTATE::getInstance()->getIsPaying()){
				GAMESTATE::getInstance()->setGamePause(true);
				CallAndroidMethod::getInstance()->pay(9);
				GAMESTATE::getInstance()->setIsPaying(true);
				GAMEDATA::getInstance()->setFindTimes(1);
			}
		}else if(lag == 2  && GAMEDATA::getInstance()->getFindTimes()==1){
			//买20秒
			if(!GAMESTATE::getInstance()->getIsPaying()){
				GAMESTATE::getInstance()->setGamePause(true);
				CallAndroidMethod::getInstance()->pay(7);
				GAMESTATE::getInstance()->setIsPaying(true);
				GAMEDATA::getInstance()->setFindTimes(2);
			}
		}else if(lag == 0 && GAMEDATA::getInstance()->getFindTimes()==2){
			//买20秒
			if(!GAMESTATE::getInstance()->getIsPaying()){
				GAMESTATE::getInstance()->setGamePause(true);
				CallAndroidMethod::getInstance()->pay(7);
				GAMESTATE::getInstance()->setIsPaying(true);
				GAMEDATA::getInstance()->setFindTimes(3);
			}
		}
	}
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	if(playTime<=0){
		Director::getInstance()->replaceScene(TransitionFade::create(0.5,GameOverScene::create()));
	}
#endif
	gameTime->setString(cocos2d::String::createWithFormat("%d",playTime)->_string);
}

void BottomMenu::plusGameTime(int time){
	playTime+=time;
}

//查找按钮的点击事件分发处理
void BottomMenu::findTouchEvent(Ref *pSender,Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;

	case Widget::TouchEventType::MOVED:
		break;

	case Widget::TouchEventType::ENDED:
		{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
			clickFindBtn = true;
			GAMEDATA* data = GAMEDATA::getInstance();
			if(data->getPropFindNum()>0){
				data->setPropFindNum(data->getPropFindNum()-1);
				GAMESTATE::getInstance()->setUsePropFind(true);
				GAMESTATE::getInstance()->setGamePause(false);
			}else{if(!GAMESTATE::getInstance()->getIsPaying()){
				GAMESTATE::getInstance()->setGamePause(true);
				GAMESTATE::getInstance()->setIsShowPayFind(true);
				CallAndroidMethod::getInstance()->pay(3);
				GAMESTATE::getInstance()->setIsPaying(true);
			}}	
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
			GAMESTATE::getInstance()->setUsePropFind(true);
#endif	
		}
		break;        
	case Widget::TouchEventType::CANCELED:
		break;          
	default:
		break;
	}
}

//加时按钮
void BottomMenu::timeTouchEvent(Ref *pSender,Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;

	case Widget::TouchEventType::MOVED:
		break;

	case Widget::TouchEventType::ENDED:
		{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
			clickTimeBtn = true;
			GAMEDATA* data = GAMEDATA::getInstance();
			if(data->getPropTimeNum()>0){
				data->setPropTimeNum(data->getPropTimeNum()-1);
				GAMESTATE::getInstance()->setUsePropTime(true);
				GAMESTATE::getInstance()->setGamePause(false);
			}else{
				if(!GAMESTATE::getInstance()->getIsPaying()){
					GAMESTATE::getInstance()->setGamePause(true);
					GAMESTATE::getInstance()->setIsShowPayFind(true);
					CallAndroidMethod::getInstance()->pay(4);
					GAMESTATE::getInstance()->setIsPaying(true);
				}
			}
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
			GAMESTATE::getInstance()->setUsePropTime(true);
#endif
		}
		break;        
	case Widget::TouchEventType::CANCELED:
		break;          
	default:
		break;
	}
}
