#include "GameLayer.h"
#include "GameData.h"
#include "Chinese.h"
#include "StarMatrix.h"
#include "HelloWorldScene.h"
#include "Audio.h"
#include "GameOverScene.h"
#include "CallAndroidMethod.h"

bool GameLayer::_PauseTime=false;
bool GameLayer::needPluse = false;
bool GameLayer::needRevive =false;
bool GameLayer::gameOver =false;
int  GameLayer::totalTime =60;


bool GameLayer::init(){
	if(!Layer::init()){
		return false;
	}
	needInitPause = true;
	TopMenu::getInstance()->cleanScore();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);
	schedule(schedule_selector(GameLayer::showPay), 1.0f, 0, 0);
	schedule(schedule_selector(GameLayer::loadGame), 2.5f, 0, 0);
	return true;
}

void GameLayer::showPay(float dt){
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if(!GAMEDATA::getInstance()->hasShowRegisterPay()){
			needInitPause = false;
			GameLayer::_PauseTime=true;
			CallAndroidMethod::getInstance()->pay(6);
		}
	#endif
}


void GameLayer::loadGame(float dt){
	schedule(schedule_selector(GameLayer::updateCustom), 1.0f, kRepeatForever, 0);

	matrix = nullptr;
	this->scheduleUpdate();
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	linkNum = Label::create("","Arial",32);
	linkNum->setPosition(visibleSize.width/2,visibleSize.height-160);
	linkNum->setVisible(false);
	this->addChild(linkNum,1);

	initTime();
	gameTime = Label::create("","Arial",24);
	gameTime->setPosition(visibleSize.width/2+190,visibleSize.height/2+350);
	showGameTime(totalTime);
	this->addChild(gameTime,0);

	menu = TopMenu::getInstance();
	this->addChild(menu, 2);

	schedule(schedule_selector(GameLayer::showStarMatrix), 1.0f, 0, 0);
	Audio::getInstance()->playReadyGo();
}


//��ʾ���Ǿ���
void GameLayer::showStarMatrix(float dt){
	matrix = StarMatrix::create(this);
	this->addChild(matrix);
	if(needInitPause){
		GameLayer::_PauseTime=false;//resume time
	}
}

//���·�����scheduleUpdate,ÿ֡����
void GameLayer::update(float delta){
	if(needPluse){
		linkNum->setString(ChineseWord("shijian"));
		linkNum->setVisible(true);
		plusTime(10);
		needPluse =false;
	}
	if(matrix){
		matrix->updateStar(delta);
	}

	if(gameOver){
		gameOver =false;
		doGameOver();
	}
	if(needRevive){
		doRevive();
		needRevive=false;
	}
	if(StarMatrix::BombClick){
		linkNum->setString(ChineseWord("zhadan"));
		linkNum->setVisible(true);
	}
}


bool GameLayer::onTouchBegan(Touch* touch,Event* event){
	Point p = touch->getLocationInView();
	p = Director::getInstance()->convertToGL(p);
	CCLOG("x=%f y=%f",p.x,p.y);
	if(matrix){
		matrix->onTouch(p);
	}
	return true;
}

void GameLayer::refreshMenu(int score){
	menu->refresh(score);
}

void GameLayer::showLinkNum(int size){
	if(size==0){
		return;
	}
	int result=0;
	for(int i=0;i<size;i++){
		result += 30+i*5;
	}
	string s = String::createWithFormat("%d",size)->_string + ChineseWord("lianji") +
		String::createWithFormat("%d",result)->_string + ChineseWord("abouttitle12");
	linkNum->setString(s);
	linkNum->setVisible(true);
}


void GameLayer::showEveryScore(int size,int score,int index,Point point,bool leftType){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* everyScore=FloatWord::create(String::createWithFormat("%d",score)->_string,32,Point(point.x,-20*index));
	this->addChild(everyScore);
	Point cp1 =Point(50,50);
	Point cp2= Point(100,100);
	if(leftType){
		cp1 =Point(430,50);
		cp2= Point(340,150);
	}else{
		cp1 =Point(50,50);
		cp2= Point(100,150);
	}

	if(size >= 9){
		everyScore->floatInScore((1.2),cp1,cp2,[=](){
			Audio::getInstance()->playScore();
			this->refreshMenu(score);
		});
	}else if(size >= 7){
		everyScore->floatInScore((0.8),cp1,cp2,[=](){
			Audio::getInstance()->playScore();
			this->refreshMenu(score);
		});
	}else{
		everyScore->floatInScore((StarMatrix::ONE_CLEAR_TIME),cp1,cp2,[=](){
			Audio::getInstance()->playScore();
			this->refreshMenu(score);
		});
	}
}

void GameLayer::hideLinkNum(){
	linkNum->setVisible(false);
}

void GameLayer::showGameTime(int time){
	string s = ChineseWord("shengyu") + String::createWithFormat("%d",time)->_string + ChineseWord("miao");
	if(gameTime){
		gameTime->setString(s);
	}
}


void GameLayer::floatLeftStarMsg(int leftNum){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* leftStarMsg1 = FloatWord::create(ChineseWord("shengyu") + String::createWithFormat("%d",leftNum)->_string +ChineseWord("ge"),
		50,Point(visibleSize.width,visibleSize.height/2));
	this->addChild(leftStarMsg1);
	int jiangLiScore = GAMEDATA::getInstance()->getJiangli(leftNum);
	leftStarMsg1->floatInOut(0.5f,1.0f,
				[=](){
					hideLinkNum();
					matrix->setNeedClear(true);
				});
	if(leftNum<10){
	FloatWord* leftStarMsg2 = FloatWord::create(ChineseWord("jiangli") + String::createWithFormat("%d",jiangLiScore)->_string + ChineseWord("fen"),
		50,Point(visibleSize.width,visibleSize.height/2 - 50));
	this->addChild(leftStarMsg2);
	leftStarMsg2->floatInOut(0.5f,1.0f,nullptr);
	}
	FloatWord* prize=FloatWord::create(String::createWithFormat("%d",jiangLiScore)->_string,32,Point(visibleSize.width/2,visibleSize.height/2 - 80));
	prize->setVisible(false);
	this->addChild(prize);
	prize->floatInPrize(1.5,[=](){
	prize->setVisible(true);
	},0.5,[=](){
	GAMEDATA* data = GAMEDATA::getInstance();
					data->setCurScore(data->getCurScore() + jiangLiScore);
					if(data->getCurScore() > data->getHistoryScore()){
						data->setHistoryScore(data->getCurScore());
					}
					refreshMenu(0);
	});
	/*Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* msg1 = FloatWord::create(ChineseWord("di")+cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextLevel()+1)->_string+ChineseWord("mu"),50,Point(0,visibleSize.height/2 - 50));
	this->addChild(msg1);
	msg1->floatInOut(0.5f,1.0f,
		[=](){
			hideLinkNum();
			matrix->setNeedClear(true);
	});
	if(leftNum<10){
		FloatWord* leftStarMsg2 = FloatWord::create(ChineseWord("jiangli") + String::createWithFormat("%d",jiangLiScore)->_string + ChineseWord("fen"),
			50,Point(visibleSize.width,visibleSize.height/2 - 50));
		this->addChild(leftStarMsg2);
		leftStarMsg2->floatInOut(0.5f,1.0f,nullptr);
		FloatWord* prize=FloatWord::create(String::createWithFormat("%d",jiangLiScore)->_string,32,Point(visibleSize.width/2,visibleSize.height/2 - 80));
		prize->setVisible(false);
		this->addChild(prize);
		prize->floatInPrize(1.5,[=](){
			prize->setVisible(true);
		},0.5,[=](){
			GAMEDATA* data = GAMEDATA::getInstance();
			data->setCurScore(data->getCurScore() + jiangLiScore);
			if(data->getCurScore() > data->getHistoryScore()){
				data->setHistoryScore(data->getCurScore());
			}
			refreshMenu(0);
		});
	}

	/*Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* msg1 = FloatWord::create(ChineseWord("di")+cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getNextLevel()+1)->_string+ChineseWord("mu"),50,Point(0,visibleSize.height/2 - 50));
	this->addChild(msg1);
	msg1->floatInOut(0.5f,1.0f,
	[=](){
	hideLinkNum();
	matrix->setNeedClear(true);
	GAMEDATA* data = GAMEDATA::getInstance();
	data->setCurScore(data->getCurScore());
	if(data->getCurScore() > data->getHistoryScore()){
	data->setHistoryScore(data->getCurScore());
	}
	refreshMenu(0);
	});*/
}


void GameLayer::doRevive(){
	setTime(20);
}

void GameLayer::doGameOver(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	gameOverWord = FloatWord::create(
		ChineseWord("gameover"),80,Point(visibleSize.width,visibleSize.height/2));
	this->addChild(gameOverWord);
	gameOverWord->floatIn(1.0f,[]{
		Director::getInstance()->replaceScene(TransitionSlideInR::create(1.0,GameOverScene::create()));
	});
}

void GameLayer::gotoNextLevel(){
	refreshMenu(0);
	//floatLevelWord();
	_PauseTime = false;
	schedule(schedule_selector(GameLayer::showStarMatrix), 1.0f, 0, 0);
	matrix->setAcceptTouch(true);
	Audio::getInstance()->playNextGameRound();
}

void GameLayer::gotoGameOver(){
	GAMEDATA::getInstance()->saveHighestScore();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(GAMEDATA::getInstance()->getReviveNum()>0){
		CallAndroidMethod::getInstance()->pay(6);
	}else{
		CallAndroidMethod::getInstance()->pay(5);
	}
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	gameOver=true;
	needRevive=false;
#endif
}

void GameLayer::initTime(){
	GameLayer::totalTime = 60;
}

int GameLayer::getTime(){
	return totalTime;
}

void GameLayer::setTime(int time){
	GameLayer::totalTime = time;
}

void GameLayer::plusTime(int time){
	Audio::getInstance()->playPropPlusTime();
	GameLayer::totalTime += time;
}

void GameLayer::updateCustom(float dt){
	if(!_PauseTime){
		totalTime--;
	}

	if(totalTime<=5 && totalTime>=0){
		Audio::getInstance()->playBeep();//����ʱ����
	}
	if(totalTime == 0){
		//ʱ�������������Ϸ�������
		gotoGameOver();
	}
	if(totalTime<0){
		totalTime=0;
	}
	showGameTime(totalTime);
}
