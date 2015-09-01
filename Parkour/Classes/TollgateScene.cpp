#include "TollgateScene.h"
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "ObjectTag.h"
#include "PlayerState.h"
#include "Monster.h"
#include "GameState.h"
#include "GameResultScene.h"
#include "GameStateInfo.h"
#include "GAMEDATA.h"
#include "GameResultInfo.h"
#include "PayHandler.h"
#include "CallAndroidMethod.h"
#include "Audio.h"
#include "Def.h"


bool TollgateScene::needSlide = false;
bool TollgateScene::isSliding = false;
bool TollgateScene::showRevivePay = true;
bool TollgateScene::finishedMission = false;
float TollgateScene::speed = 6;
float TollgateScene::level = 1;
bool TollgateScene::payPause = false;

TollgateScene::~TollgateScene()
{
}
Scene* TollgateScene::scene()
{
	Audio::getInstance()->playBGM("Music/game_bg.mp3");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameUI.plist");
	auto scene = Scene::create();

	auto background = BackgroundLayer::create();
	scene->addChild(background, 0);

	auto layer = TollgateScene::create();
	layer->m_backgroundLayer = background;
	scene->addChild(layer, 10);

	return scene;
}
bool TollgateScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	isShowDownGuide = false;
	isShowUpGuide = false;
	finishedMission = false;
	needSlide = false;
	isSliding = false;
	pausedGame = false;
	showRevivePay = true;
	hasShowPay = false;
	distance = 0;
	totalDistance = 0;
	distanceByPotential = 0;
	distanceBySuper = 0;
	finishedTime = 0;
	hasToResultScene = false;
	payPause = false;
	isUseProp = false;
	isShowEvent18 = false;
	GAMEDATA::getInstance()->reset();
	GameStateInfo::getInstance()->setGameState(Game_Playing);
	visibleSize = Director::getInstance()->getVisibleSize();
	m_player = Player::create();
	m_player->setPosition(Point(200, 230.4));
	this->addChild(m_player, 5);

	m_infoLayer = InfoLayer::create();
	this->addChild(m_infoLayer, 20);

	m_gamePauseLayer = GamePauseLayer::create();
	m_gamePauseLayer->setVisible(false);
	this->addChild(m_gamePauseLayer, 40);

	auto monsterLayer = MonsterLayer::createLayer(m_player, m_infoLayer);
	this->m_monsterLayer = (MonsterLayer*)monsterLayer;
	this->addChild(monsterLayer, 1);

	//propInfo = PropInfo::getInstance(m_player);
	//this->addChild(propInfo, 30);

	m_player->move();

	auto jumpBtn = Button::create(
		"jump_btn_normal.png", "jump_btn_click.png");
	jumpBtn->setPosition(Vec2(visibleSize.width - 100, 91 * visibleSize.height / 480));
	this->addChild(jumpBtn, 10);
	jumpBtn->addTouchEventListener(CC_CALLBACK_2(TollgateScene::jump, this));

	auto slideBtn = Button::create(
		"slide_btn_normal.png", "slide_btn_click.png");
	slideBtn->setPosition(Vec2(visibleSize.width - 700, 91 * visibleSize.height / 480));
	this->addChild(slideBtn, 10);
	slideBtn->addTouchEventListener(CC_CALLBACK_2(TollgateScene::slide, this));

	MenuItemImage* pauseBtn = MenuItemImage::create(
		"game_pause.png", "game_pause.png", CC_CALLBACK_0(TollgateScene::pauseGame, this)
		);
	auto pauseMenu = Menu::create(pauseBtn, NULL);
	pauseMenu->setPosition(757, visibleSize.height - 33);
	this->addChild(pauseMenu, 10);

	finishMissionBg = Sprite::create("finish_mission_bg.png");
	finishMissionBg->setPosition(400, 220);
	this->addChild(finishMissionBg, 100);
	finishMissionBg->setVisible(false);

	finishMission = Sprite::create("finish_mission_txt.png");
	finishMission->setPosition(400, 220);
	this->addChild(finishMission, 100);
	finishMission->setVisible(false);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			pauseGame();
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	//add new player guide to this layer
	this->schedule(schedule_selector(TollgateScene::logic));
	return true;
}
void TollgateScene::onExit()
{
	Layer::onExit();
	TollgateScene::level = 1;
}

void TollgateScene::logic(float dt){
	int type = GAMEDATA::getInstance()->getUsePropType();
	if (!isUseProp){
		if (type == PROP_SUPER){
			Player::skillState = Player_Super;
			m_player->superMove();
			GAMEDATA::getInstance()->setSuperPropNum(
				GAMEDATA::getInstance()->getSuperPropNum() - 1);
			isUseProp = true;
		}
		else if (type == PROP_MAGNETIC){
			Player::skillState = Player_Magic;
			m_player->magneticMove();
			GAMEDATA::getInstance()->setMagneticPropNum(
				GAMEDATA::getInstance()->getMagneticPropNum() - 1);
			isUseProp = true;
		}
		else if (type == PROP_POTENTIAL){
			Player::skillState = Player_Fly;
			m_player->quickMove();
			GAMEDATA::getInstance()->setPotentialPropNum(
				GAMEDATA::getInstance()->getPotentialPropNum() - 1);
			isUseProp = true;
		}
	}
	if (payPause){
		payPause = false;
		payPauseGame();
	}
	//检查是否触发新手引导的条件
	if(GAMEDATA::getInstance()->getPlayRounds()==0){
		if (totalDistance >= 15 &&totalDistance<17 && !isShowDownGuide){
			isShowDownGuide = true;
			showPlayerDownGuide();
		}
		else if (totalDistance >= 24 && !isShowUpGuide){
			isShowUpGuide = true;
			showPlayerUpGuide();
		}
	}


	if (finishedMission){
		showFinishMission();
		finishedTime += dt / 0.05;
		if (finishedTime > 45 && !hasToResultScene){
			hasToResultScene = true;
			toResultScene();
		}
	}
	if (GameStateInfo::getInstance()->getGameState() != Game_Playing){
		if (GameStateInfo::getInstance()->getGameState() == Game_End){
			m_player->pause();
			m_monsterLayer->pause();
			if (GAMEDATA::getInstance()->getPlayRounds() == 0){
				finishedMission = true;
			}
			else{
				if (showRevivePay && GameResultInfo::getInstance()->getGameResult() == 0){
					showRevivePay = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
					GameStateInfo::getInstance()->setGameState(Game_Pause);
					if(GAMEDATA::getInstance()->getReviveNum() <= 0){
						CallAndroidMethod::getInstance()->pay(4);
					}else{
						int reviveNum = GAMEDATA::getInstance()->getReviveNum();
						switch (reviveNum)
						{
						case 4:
							CallAndroidMethod::getInstance()->pay(9);
							break;
						case 3:
							CallAndroidMethod::getInstance()->pay(12);
							break;
						case 2:
							CallAndroidMethod::getInstance()->pay(13);
							break;
						case 1:
							CallAndroidMethod::getInstance()->pay(14);
							break;
						default:
							break;
						}
					}

#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
					toResultScene();
#endif
				}
				else if (!showRevivePay && GameResultInfo::getInstance()->getGameResult() == 0){
					toResultScene();
				}
			}
		}
		else if (GameStateInfo::getInstance()->getGameState() == Game_Pause){
			return;
		}
		return;
	}
	if (PayHandler::needFly){
		PayHandler::needFly = false;
		auto action = MoveTo::create(0.5, Point(200, 360));
		auto callFunc = CallFunc::create([=](){
			m_player->quickMove();
		});
		auto seq = Sequence::create(action, callFunc, NULL);
		m_player->runAction(seq);
	}
	else if (PayHandler::needMagnetic){
		PayHandler::needMagnetic = false;
		m_player->magneticMove();
	}
	else if (PayHandler::needSuper){
		PayHandler::needSuper = false;
		m_player->superMove();
	}
	if (GAMEDATA::getInstance()->getPlayRounds() == 2){
		if (totalDistance > 10 && !hasShowPay){
			hasShowPay = true;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			GameStateInfo::getInstance()->setGameState(Game_Pause);
			CallAndroidMethod::getInstance()->pay(5);
#endif
		}
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//第一次进入的计费点弹出  
	if (GAMEDATA::getInstance()->isFirstLogin() && Player::skillState <= 4){
		GAMEDATA::getInstance()->setFirstLogin(false);
		GameStateInfo::getInstance()->setGameState(Game_Pause);
		CallAndroidMethod::getInstance()->pay(1);
	}
	if (!isShowEvent18&&totalDistance > 10 && GAMEDATA::getInstance()->getPlayRounds() >= 3 && GAMEDATA::getInstance()->getPlayRounds()%3==0){
		GameStateInfo::getInstance()->setGameState(Game_Pause);
		CallAndroidMethod::getInstance()->pay(18);
		isShowEvent18 = true;
	}
#endif
	int playerLevel = GAMEDATA::getInstance()->getPlayerLevel();
	if (playerLevel < 29){
		int hasFinishedNums = 0;
		switch (playerLevel){
		case 1:
		case 11:
			hasFinishedNums = GAMEDATA::getInstance()->getJumpTimes();
			break;
		case 2:
		case 12:
			hasFinishedNums = GAMEDATA::getInstance()->getSlideTimes();
			break;
		case 3:
		case 13:
		case 26:
			hasFinishedNums = GAMEDATA::getInstance()->getEatGoldNum();
			break;
		case 4:
			hasFinishedNums = GAMEDATA::getInstance()->getEatMagneticPropNums() +
				GAMEDATA::getInstance()->getEatPotentialPropNums() +
				GAMEDATA::getInstance()->getEatSuperPropNums();
			break;
		case 8:
			hasFinishedNums = GAMEDATA::getInstance()->getEatPotentialPropNums();
			break;
		case 9:
			hasFinishedNums = GAMEDATA::getInstance()->getEatMagneticPropNums();
			break;
		case 10:
			hasFinishedNums = GAMEDATA::getInstance()->getEatSuperPropNums();
			break;
		case 5:
			hasFinishedNums = GAMEDATA::getInstance()->getPropPotentialTimes() +
				GAMEDATA::getInstance()->getActivePotentialTimes();
			break;
		case 6:
		case 19:
			hasFinishedNums = GAMEDATA::getInstance()->getDodgeMonsterNums();
			break;
		case 7:
		case 18:
		case 28:
			hasFinishedNums = GAMEDATA::getInstance()->getGameScore();
			break;
		case 14:
		case 20:
		case 27:
			hasFinishedNums = GAMEDATA::getInstance()->getCostGoldNums();
			break;
		case 15:
		case 24:
			hasFinishedNums = GAMEDATA::getInstance()->getEatGoldByMagneticNums();
			break;
		case 16:
			hasFinishedNums = GAMEDATA::getInstance()->getActivePotentialTimes();
			break;
		case 17:
			hasFinishedNums = GAMEDATA::getInstance()->getDistanceBySuper();
			break;
		case 25:
			hasFinishedNums = GAMEDATA::getInstance()->getDistanceByPotential();
			break;
		}
		GAMEDATA::getInstance()->setHasFinishedNum(hasFinishedNums);
		if (hasFinishedNums >= GAMEDATA::getInstance()->getCurrentMissionNum()){
			if (playerLevel != 14 && playerLevel != 20 && playerLevel != 27){
				GameResultInfo::getInstance()->setGameResult(1);
				GAMEDATA::getInstance()->setPlayerLevel(GAMEDATA::getInstance()->getPlayerLevel() + 1);
				GameStateInfo::getInstance()->setGameState(Game_End);
				finishedMission = true;
			}
		}
		else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			CCLOG("android platform setGameResult = 0");	
#endif
			GameResultInfo::getInstance()->setGameResult(0);
		}
	}
	if (pausedGame){
		pausedGame = false;
		m_player->resume();
		m_monsterLayer->resume();
	}
	m_backgroundLayer->setBackGroudSpeed(TollgateScene::speed);
	m_backgroundLayer->logic(dt);
	m_monsterLayer->logic(dt);
	m_player->logic(dt);
	m_infoLayer->refreshMission();
	//if (propInfo->isVisible()){
	//	propInfo->updatePosition(m_player->getPositionX(), m_player->getPositionY());
	//}
	if (Player::skillState == Player_Active || Player::skillState == Player_Fly){
		distanceByPotential += 4;
		if (distanceByPotential >= 40){
			GAMEDATA::getInstance()->setDistanceByPotential(GAMEDATA::getInstance()->getDistanceByPotential() + 1);
			distanceByPotential -= 40;
		}
	}
	else if (Player::skillState == Player_Super){
		distanceBySuper += 4;
		if (distanceBySuper >= 40){
			GAMEDATA::getInstance()->setDistanceBySuper(GAMEDATA::getInstance()->getDistanceBySuper() + 1);
			distanceBySuper -= 40;
		}
	}
	checkDistance += 4;
	distance += 4;
	if (distance >= 40){
		m_infoLayer->distanceAddOne();
		totalDistance++;
		distance -= 40;
	}
	/*if (totalDistance >= 40){
		propInfo->setVisible(false);
		}
		else{
		if (propInfo->isShowVisible()){
		propInfo->setVisible(true);
		}
		}*/
	if ((m_player->getPositionX() < 0 || m_player->getPositionY() < 0) && Player::skillState != Player_Fly && Player::skillState != Player_Active){
		GameStateInfo::getInstance()->setGameState(Game_End);
	}
}

void TollgateScene::toResultScene(){
	//propInfo->setShowVisible(true);
	onExit();
	int playRounds = GAMEDATA::getInstance()->getPlayRounds();
	int playerLevel = GAMEDATA::getInstance()->getPlayerLevel();
	if (playerLevel == 0){
		GameResultInfo::getInstance()->setGameResult(1);
		GAMEDATA::getInstance()->setPlayerLevel(GAMEDATA::getInstance()->getPlayerLevel() + 1);
	}
	else if (playerLevel == 14 || playerLevel == 20 || playerLevel == 27){
		if (GAMEDATA::getInstance()->getHasFinishedNum() >= GAMEDATA::getInstance()->getCurrentMissionNum()){
			GameResultInfo::getInstance()->setGameResult(1);
			GAMEDATA::getInstance()->setPlayerLevel(GAMEDATA::getInstance()->getPlayerLevel() + 1);
		}
	}
	GAMEDATA::getInstance()->setPlayRounds(playRounds + 1);
	GAMEDATA::getInstance()->setDistance(totalDistance);
	GAMEDATA::getInstance()->setGameScore(totalDistance*GAMEDATA::getInstance()->getEatGoldNum() / 100);
	Director::getInstance()->replaceScene(
		TransitionFade::create(1, GameResultScene::create()));
}

void TollgateScene::jump(Ref *pSender, Widget::TouchEventType type){
	if (!m_monsterLayer->isCanJump()){
		CCLOG("can not jump...");
		return;
	}
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		Audio::getInstance()->playSound("Music/touch.wav");
		m_player->jump();
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void TollgateScene::slide(Ref *pSender, Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		Audio::getInstance()->playSound("Music/touch.wav");
		if (Player::state == Player_Run){
			m_player->slideMove();
		}
		else{
			needSlide = true;
		}
		isSliding = true;
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		if (!m_monsterLayer->isNeedContiSlide()){
			m_player->move();
		}
		needSlide = false;
		isSliding = false;
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		if (!m_monsterLayer->isNeedContiSlide()){
			needSlide = false;
			m_player->move();
		}
		needSlide = false;
		isSliding = false;
		break;
	default:
		break;
	}
}

void TollgateScene::payPauseGame(){
	if (GameStateInfo::getInstance()->getGameState() != Game_Playing){
		return;
	}
	pausedGame = true;
	GameStateInfo::getInstance()->setGameState(Game_Pause);
	m_player->pause();
	m_monsterLayer->pause();
}

void TollgateScene::pauseGame(){
	CCLOG(">>>>>>>>>>>>>>>>gameState=%d", GameStateInfo::getInstance()->getGameState());
	if (GameStateInfo::getInstance()->getGameState() != Game_Playing){
		return;
	}
	Audio::getInstance()->playSound("Music/paddle_hit.wav");
	pausedGame = true;
	GameStateInfo::getInstance()->setGameState(Game_Pause);
	m_player->pause();
	m_monsterLayer->pause();
	m_gamePauseLayer->setVisible(true);
}

void TollgateScene::showFinishMission(){
	finishMissionBg->setVisible(true);
	finishMission->setVisible(true);
}

//add new player guide
void TollgateScene::showPlayerDownGuide(){
	GameStateInfo::getInstance()->setGameState(Game_Pause);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = LayerColor::create(ccc4(0, 0, 0, 125));
	bg->setContentSize(CCSizeMake(visibleSize.width, visibleSize.height));
	auto pClip = ClippingNode::create();
	pClip->setInverted(true);
	pClip->addChild(bg);
	this->addChild(pClip, 100);
	Sprite* guide_down = Sprite::create("guide_slide.png");
	guide_down->setPosition(ccp(150,180));
	this->addChild(guide_down,100);
	auto pStencil = DrawNode::create();
	pStencil->drawSolidCircle(ccp(100, 90), 60, 0, 180, ccc4f(1, 0, 0, 1));
	pClip->setStencil(pStencil);
	EventListenerTouchOneByOne* touchEvent = EventListenerTouchOneByOne::create();
	touchEvent->onTouchBegan = [=](Touch* touch, Event* ev){
		Rect rect = Rect(70, 60, 60, 60);
		if (rect.containsPoint(touch->getLocation())){
			pClip->removeFromParent();
			_eventDispatcher->removeEventListener(touchEvent);
			guide_down->removeFromParent();
			GameStateInfo::getInstance()->setGameState(Game_Playing);
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithFixedPriority(touchEvent, -128);

}


void TollgateScene::showPlayerUpGuide(){
	GameStateInfo::getInstance()->setGameState(Game_Pause);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = LayerColor::create(ccc4(0, 0, 0, 125));
	bg->setContentSize(CCSizeMake(visibleSize.width, visibleSize.height));
	auto pClip = ClippingNode::create();
	pClip->setInverted(true);
	pClip->addChild(bg);
	this->addChild(pClip, 100);
	auto pStencil = DrawNode::create();
	pStencil->drawSolidCircle(ccp(700, 90), 60, 0, 180, ccc4f(1, 0, 0, 1));
	pClip->setStencil(pStencil);
	Sprite* guide_down = Sprite::create("guide_up.png");
	guide_down->setPosition(ccp(680,180));
	this->addChild(guide_down,100);
	EventListenerTouchOneByOne* touchEvent = EventListenerTouchOneByOne::create();
	touchEvent->onTouchBegan = [=](Touch* touch, Event* ev){
		Rect rect = Rect(670, 60, 60, 60);
		if (rect.containsPoint(touch->getLocation())){
			GameStateInfo::getInstance()->setGameState(Game_Playing);
			pClip->removeFromParent();
			guide_down->removeFromParent();
			_eventDispatcher->removeEventListener(touchEvent);
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithFixedPriority(touchEvent, -128);
}
