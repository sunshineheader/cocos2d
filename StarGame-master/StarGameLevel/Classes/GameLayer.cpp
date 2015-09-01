#include "GameLayer.h"
#include "GameData.h"
#include "Chinese.h"
#include "StarMatrix.h"
#include "HelloWorldScene.h"
#include "Audio.h"
#include "GameOverScene.h"
#include "CallAndroidMethod.h"


bool GameLayer::needRevive =false;
bool GameLayer::gameOver =false;
bool GameLayer::goToNextLevel=false;
bool GameLayer::isShowRePlay = false;

bool GameLayer::init(){
	if(!Layer::init()){
		return false;
	}
	needInitPause = true;
	hasShowMission =false;
	missionComplete = NULL;
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
		if(!GAMEDATA::getInstance()->getIsBuySuperGift() &&
				GAMEDATA::getInstance()->getCurExpNum()==0 &&
				(GAMEDATA::getInstance()->getUserLevel()==1 || GAMEDATA::getInstance()->getUserLevel()==2 ||
						GAMEDATA::getInstance()->getUserLevel()==3 || GAMEDATA::getInstance()->getUserLevel()==4)){
			needInitPause = false;
			CallAndroidMethod::getInstance()->pay(9);
		}
	#endif
}


void GameLayer::loadGame(float dt){

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

	GAMEDATA::getInstance()->setCurLevel(0);
	menu = TopMenu::getInstance();
	menu->refreshTargetScore();
	this->addChild(menu, 2);

	schedule(schedule_selector(GameLayer::showStarMatrix), 1.0f, 0, 0);
	Audio::getInstance()->playReadyGo();
}

void GameLayer::floatLevelWord(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_levelMsg = FloatWord::create(
		ChineseWord("guanqia") + cocos2d::String::createWithFormat(": %d",GAMEDATA::getInstance()->getNextLevel())->_string,
		50, Point(visibleSize.width,visibleSize.height/3*2)
		);
	this->addChild(_levelMsg,1);
	_levelMsg->floatInOut(0.5f,1.0f,[=](){
		schedule(schedule_selector(GameLayer::showStarMatrix), 1.0f, 0, 0);
		matrix->setAcceptTouch(true);
		menu->showProps();
		Audio::getInstance()->playNextGameRound();
	});
	Audio::getInstance()->playReadyGo();
}


void GameLayer::showStarMatrix(float dt){
	matrix = StarMatrix::create(this);
	this->addChild(matrix);
	menu->showProps();
}

void GameLayer::doRevive(){
    TopMenu::getInstance()->cleanScore();
	GAMEDATA::getInstance()->setCurScore(GAMEDATA::getInstance()->getLastLevelScore());
	TopMenu::getInstance()->refresh(0);
	TopMenu::getInstance()->refreshTargetScore();	
	schedule(schedule_selector(GameLayer::showStarMatrix), 1.0f, 0, 0);
	matrix->setAcceptTouch(true);
	Audio::getInstance()->playNextGameRound();
}

void GameLayer::update(float delta){
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
	if(goToNextLevel){
		GAMEDATA::getInstance()->setCurScore(GAMEDATA::getInstance()->getNextScore());
		GAMEDATA::getInstance()->setCurLevel(GAMEDATA::getInstance()->getCurLevel() + 1);		
	    gotoNextLevel();
		goToNextLevel=false;
	}
	if(isShowRePlay){
		TopMenu::getInstance()->showRePaly();
		isShowRePlay = false;
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
	menu->refreshTargetScore();
	GAMEDATA* data = GAMEDATA::getInstance();
	if(data->getCurScore()+score>=GAMEDATA::getInstance()->getNextScore()&&!hasShowMission&& score!=0){
		hasShowMission =true;
		showMissionComplete();
	}
}

void GameLayer::showLinkNum(int size){
	if(size==0){
		return;
	}
	int result=0;
	for(int i=0;i<size;i++){
		result += 5+i*5;
	}
	string s = String::createWithFormat("%d",size)->_string + ChineseWord("lianji") +
		String::createWithFormat("%d",result)->_string + ChineseWord("abouttitle12");
	linkNum->setString(s);
	linkNum->setVisible(true);
}


void GameLayer::showEveryScore(int size,int score,int index,Point point,bool leftType){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* everyScore=FloatWord::create(String::createWithFormat("%d",score)->_string,32,Point(point.x,point.y));
	this->addChild(everyScore);
	Point cp1 =Point(50,50);
	Point cp2= Point(100,100);
	if(leftType){
		cp1 =Point(430,500);
		cp2= Point(330,600);
	}else{
		cp1 =Point(50,500);
		cp2= Point(150,600);
	}
	if(size >= 9){
		everyScore->floatInScore((StarMatrix::ONE_CLEAR_TIME)*2,cp1,cp2,[=](){
			Audio::getInstance()->playScore();
			this->refreshMenu(score);
		});
	}else if(size >= 7){
		everyScore->floatInScore((StarMatrix::ONE_CLEAR_TIME)*2,cp1,cp2,[=](){
			Audio::getInstance()->playScore();
			this->refreshMenu(score);
		});
	}else{
		everyScore->floatInScore((StarMatrix::ONE_CLEAR_TIME)*2,cp1,cp2,[=](){
			Audio::getInstance()->playScore();
			this->refreshMenu(score);
		});
	}
}

void GameLayer::hideLinkNum(){
	linkNum->setVisible(false);
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
	removeMissonComplet();
	refreshMenu(0);
	GAMEDATA::getInstance()->setLastLevelScore(GAMEDATA::getInstance()->getCurScore());
	floatLevelWord();
}

void GameLayer::gotoGameOver(){
	GAMEDATA::getInstance()->saveHighestScore();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->pay(10);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	gameOver=true;
	needRevive=false;
#endif
}

void GameLayer::showMissionComplete(){
	auto visibleSize =  Director::getInstance()->getVisibleSize();
	missionComplete=Sprite::create("missionComplete.png");
	missionComplete->setPosition(visibleSize.width/2,visibleSize.height/2);
	missionComplete->setScale(0.2f);
	this->addChild(missionComplete);
	auto scale = ScaleTo::create(1.0f,0.5f);
	auto move = MoveTo::create(1.0f,Point(visibleSize.width/2-200,visibleSize.height/2+260));
	auto seq = Sequence::create(scale,move,NULL);
	missionComplete->runAction(seq);
}

void GameLayer::removeMissonComplet(){
	if(NULL !=missionComplete){
		missionComplete->removeFromParentAndCleanup(true);
		missionComplete = NULL;
	}
	hasShowMission=false;
}

void GameLayer::hidePropInfos(){
	menu->cancelUseProp();
}

void GameLayer::hideProps(){
	menu->hideProps();
}

