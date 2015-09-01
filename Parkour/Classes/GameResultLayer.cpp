#include "GameResultLayer.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "TollgateScene.h"
#include "Audio.h"
#include "GAMEDATA.h"
#include "PlayerRank.h"
#include "GameResultInfo.h"
#include "ResultGold.h"
#include "CallAndroidMethod.h"
#include "MenuLayer.h"

using namespace cocos2d;

bool GameResultLayer::clickedStartGame = false;
bool GameResultLayer::clickedBack = false;
bool GameResultLayer::canClick = false;

bool GameResultLayer::init(){
	if (!Layer::init()){
		return false;
	}
	Audio::getInstance()->playBGM("Music/lobby_bg.ogg");
	animTime = 0;
	canClick = false;
	gameScoreNum = 0;
	hasStartMissionAnim = false;
	hasStartRankAnim = false;
	hasShowPay = false;
    isShowSuper = false;
	isShowMagnetic = false;
	isShowPotential = false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("result.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("result_lose.plist");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("background.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background, -1);

	auto bg = TMXTiledMap::create("map_0.tmx");
	this->addChild(bg);

	if (GameResultInfo::getInstance()->getGameResult() == 0){
		auto resultShineBg = Sprite::createWithSpriteFrameName("result_shine_bg_lose.png");
		resultShineBg->setPosition(235, 289);
		this->addChild(resultShineBg);

		auto resultBg = Sprite::createWithSpriteFrameName("result_bg.png");
		resultBg->setPosition(183, 276);
		this->addChild(resultBg);

		auto title = Sprite::createWithSpriteFrameName("result_title_lose.png");
		title->setPosition(183, 414);
		this->addChild(title);
	}
	else{
		ResultGold::getInstance()->refreshPlayerLevel();
		GAMEDATA::getInstance()->setHasShowPlayerUpgradePay(false);
		auto resultShineBg = Sprite::createWithSpriteFrameName("result_shine_bg.png");
		resultShineBg->setPosition(235, 289);
		this->addChild(resultShineBg);

		auto resultBg = Sprite::createWithSpriteFrameName("result_bg.png");
		resultBg->setPosition(183, 276);
		this->addChild(resultBg);

		auto title = Sprite::createWithSpriteFrameName("result_title.png");
		title->setPosition(183, 414);
		this->addChild(title);
	}

	auto historyScoreBg = Sprite::createWithSpriteFrameName("result_history_score_bg.png");
	historyScoreBg->setPosition(183, 345);
	this->addChild(historyScoreBg);

	auto historyScoreTxt = Sprite::createWithSpriteFrameName("result_history_txt.png");
	historyScoreTxt->setPosition(138, 345);
	this->addChild(historyScoreTxt);

	auto historyScore = LabelAtlas::create(String::createWithFormat("%d", GAMEDATA::getInstance()->getHistoryScore())->_string,
		"result_histor_score_num.png", 10, 13, 48);
	historyScore->setAnchorPoint(Point(0, 0.5));
	historyScore->setPosition(179, 345);
	this->addChild(historyScore);

	totalGameScore = GAMEDATA::getInstance()->getGameScore();
	gameScore = LabelAtlas::create("0",
		"result_score_num.png", 26, 35, 48);
	gameScore->setAnchorPoint(Point(0.5, 0.5));
	gameScore->setPosition(183, 299);
	this->addChild(gameScore);

	auto dodgeMonsterNum = String::createWithFormat("%d", GAMEDATA::getInstance()->getDodgeMonsterNums());
	int dodgeLength = dodgeMonsterNum->length();
	auto dodgeTxt = Sprite::createWithSpriteFrameName("result_dodge_txt.png");
	dodgeTxt->setPosition(151.5 - (dodgeLength - 1) * 5, 375);
	this->addChild(dodgeTxt);
	auto dodgeNum = LabelAtlas::create(dodgeMonsterNum->_string, "result_num.png", 10, 13, 48);
	dodgeNum->setAnchorPoint(Point(0.5, 0.5));
	dodgeNum->setPosition(174, 375);
	this->addChild(dodgeNum);
	auto monsterTxt = Sprite::createWithSpriteFrameName("result_monster_txt.png");
	monsterTxt->setPosition(207.5 + (dodgeLength - 1) * 5, 375);
	this->addChild(monsterTxt);

	auto distanceNumStr = String::createWithFormat("%d", GAMEDATA::getInstance()->getDistance());
	int distanceLength = distanceNumStr->length();
	auto distanceTxt = Sprite::createWithSpriteFrameName("result_distance_txt.png");
	distanceTxt->setPosition(163.5 - (distanceLength - 1) * 5, 251);
	this->addChild(distanceTxt);
	auto distanceNum = LabelAtlas::create(distanceNumStr->_string, "result_num.png", 10, 13, 48);
	distanceNum->setAnchorPoint(Point(0.5, 0.5));
	distanceNum->setPosition(196, 251);
	this->addChild(distanceNum);
	auto miTxt = Sprite::createWithSpriteFrameName("result_mi_txt.png");
	miTxt->setPosition(215.5 + (distanceLength - 1) * 5, 251);
	this->addChild(miTxt);

	int prizeGoldNum = GAMEDATA::getInstance()->getEatGoldNum() / 10;
	GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum() + prizeGoldNum);
	ResultGold::getInstance()->refreshGold();
	auto goldNumStr = String::createWithFormat("%d", prizeGoldNum);
	int goldLength = goldNumStr->length();
	auto goldTxt = Sprite::createWithSpriteFrameName("result_gold.png");
	goldTxt->setPosition(164 - (goldLength - 1) * 5, 225);
	this->addChild(goldTxt);
	auto goldNum = LabelAtlas::create(goldNumStr->_string, "result_num.png", 10, 13, 48);
	goldNum->setAnchorPoint(Point(0.5, 0.5));
	goldNum->setPosition(196.5, 225);
	this->addChild(goldNum);
	auto perTxt = Sprite::createWithSpriteFrameName("result_per_txt.png");
	perTxt->setPosition(215.5 + (goldLength - 1) * 5, 225);
	this->addChild(perTxt);

	auto bankNumStr = String::createWithFormat("%d", PLAYERRANK::getInstance()->getRankList(GAMEDATA::getInstance()->getGameScore()));
	auto rankNumLength = bankNumStr->length();
	auto rankStr = Sprite::createWithSpriteFrameName("result_bank_txt.png");
	rankStr->setPosition(170.5 - (rankNumLength - 1)*12.5, 181);
	this->addChild(rankStr);
	rankNum = LabelAtlas::create(bankNumStr->_string, "result_bank_num.png", 23, 29, 48);
	rankNum->setAnchorPoint(Point(0.5, 0.5));
	rankNum->setPosition(216.5, 181);
	rankNum->setVisible(false);
	rankNum->setScale(4);
	this->addChild(rankNum);

	auto level = Sprite::createWithSpriteFrameName("lobby_level.png");
	level->setPosition(404, 412);
	this->addChild(level);

	auto gold = Sprite::createWithSpriteFrameName("lobby_gold.png");
	gold->setPosition(638, 412);
	this->addChild(gold);

	auto needRefreshInfo = ResultGold::getInstance();
	ResultGold::getInstance()->refreshPropNum();
	this->addChild(needRefreshInfo, 2);

	auto superBg = Sprite::createWithSpriteFrameName("lobby_prop_bg.png");
	superBg->setPosition(576, 340);
	this->addChild(superBg);

	auto superProgressBg = Sprite::createWithSpriteFrameName("lobby_progress_bg.png");
	superProgressBg->setPosition(516, 340);
	this->addChild(superProgressBg);

	auto superTxt = Sprite::createWithSpriteFrameName("lobby_super_time_txt.png");
	superTxt->setPosition(495, 355);
	this->addChild(superTxt);

	superIcon = Sprite::createWithSpriteFrameName("lobby_prop_super.png");
	superIcon->setPosition(416.5, 340);
	this->addChild(superIcon);

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = CC_CALLBACK_2(GameResultLayer::upgradeSuper, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, superBg);

	auto magneticBg = Sprite::createWithSpriteFrameName("lobby_prop_bg.png");
	magneticBg->setPosition(576, 255);
	this->addChild(magneticBg);

	auto magneticProgressBg = Sprite::createWithSpriteFrameName("lobby_progress_bg.png");
	magneticProgressBg->setPosition(516, 255);
	this->addChild(magneticProgressBg);

	auto magneticTxt = Sprite::createWithSpriteFrameName("lobby_magnetic_time_txt.png");
	magneticTxt->setPosition(495, 270);
	this->addChild(magneticTxt);

	magneticIcon = Sprite::createWithSpriteFrameName("lobby_prop_magnetic.png");
	magneticIcon->setPosition(416.5, 255);
	this->addChild(magneticIcon);

	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = CC_CALLBACK_2(GameResultLayer::upgradeMagnetic, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, magneticBg);

	auto potentialBg = Sprite::createWithSpriteFrameName("lobby_prop_bg.png");
	potentialBg->setPosition(576, 170);
	this->addChild(potentialBg);

	auto potentialProgressBg = Sprite::createWithSpriteFrameName("lobby_progress_bg.png");
	potentialProgressBg->setPosition(516, 170);
	this->addChild(potentialProgressBg);

	auto potentialTxt = Sprite::createWithSpriteFrameName("lobby_potential_time_txt.png");
	potentialTxt->setPosition(495, 185);
	this->addChild(potentialTxt);

	potentialIcon = Sprite::createWithSpriteFrameName("lobby_prop_potential.png");
	potentialIcon->setPosition(416.5, 170);
	this->addChild(potentialIcon);

	auto listener3 = EventListenerTouchOneByOne::create();
	listener3->onTouchBegan = CC_CALLBACK_2(GameResultLayer::upgradePotential, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener3, potentialBg);

	auto startGameBtn = MenuItemImage::create(
		"lobby_start_game_bg_normal.png",
		"lobby_start_game_bg_click.png",
		CC_CALLBACK_0(GameResultLayer::contiGame, this));
	auto startGameMenu = Menu::create(startGameBtn, NULL);
	startGameMenu->setAnchorPoint(Point(1, 0.5f));
	startGameMenu->setPosition(632, 70);
	this->addChild(startGameMenu);

	auto startGameTxt = MenuItemImage::create(
		"result_conti_txt_normal.png",
		"result_conti_txt_click.png",
		CC_CALLBACK_0(GameResultLayer::contiGame, this));
	auto startGameTxtMenu = Menu::create(startGameTxt, NULL);
	startGameTxtMenu->setAnchorPoint(Point(1, 0.5f));
	startGameTxtMenu->setPosition(632, 70);
	this->addChild(startGameTxtMenu);

	auto backBtn = MenuItemImage::create(
		"result_btn_bg_normal.png",
		"result_btn_bg_click.png",
		CC_CALLBACK_0(GameResultLayer::back, this));
	auto backMenu = Menu::create(backBtn, NULL);
	backMenu->setAnchorPoint(Point(0, 0.5f));
	backMenu->setPosition(168, 70);
	this->addChild(backMenu);

	auto backTxt = MenuItemImage::create(
		"result_back_txt_normal.png",
		"result_back_txt_click.png",
		CC_CALLBACK_0(GameResultLayer::back, this));
	auto backTxtMenu = Menu::create(backTxt, NULL);
	backTxtMenu->setAnchorPoint(Point(0, 0.5f));
	backTxtMenu->setPosition(168, 70);
	this->addChild(backTxtMenu);

	Sprite* super_not_select = Sprite::create("prop_not_select.png");
	super_not_select->setPosition(ccp(432, 320));
	this->addChild(super_not_select);

	Sprite* magnetic_not_select = Sprite::create("prop_not_select.png");
	magnetic_not_select->setPosition(ccp(432, 236));
	this->addChild(magnetic_not_select);

	Sprite* potential_not_select = Sprite::create("prop_not_select.png");
	potential_not_select->setPosition(ccp(432, 150));
	this->addChild(potential_not_select);

	prop_select_icon = Sprite::create("prop_select.png");
	prop_select_icon->setVisible(false);
	this->addChild(prop_select_icon, 2);

	if (GAMEDATA::getInstance()->isSuperSelect()){
		prop_select_icon->setPosition(ccp(432, 320));
		prop_select_icon->setVisible(true);
	}
	else if (GAMEDATA::getInstance()->isMagneticSelect()){
		prop_select_icon->setPosition(ccp(432, 236));
		prop_select_icon->setVisible(true);
	}
	else if (GAMEDATA::getInstance()->isPotentialSelect()){
		prop_select_icon->setPosition(ccp(432, 150));
		prop_select_icon->setVisible(true);
	}

	mission = Sprite::createWithSpriteFrameName("result_finish_mission.png");
	mission->setPosition(308, 327);
	mission->setScale(4);
	mission->setVisible(false);
	this->addChild(mission);

	bankRaiseLayer = BankRaiseLayer::create();
	bankRaiseLayer->setVisible(false);
	bankRaiseLayer->setTag(1111);
	this->addChild(bankRaiseLayer, 10);

	this->scheduleUpdate();

	if (GameResultInfo::getInstance()->getGameResult() == 0){
		Audio::getInstance()->playSound("Music/result_fail.mp3");
	}
	else{
		Audio::getInstance()->playSound("Music/result_success.mp3");
	}

	return true;
}

void GameResultLayer::contiGame(){
	if (clickedStartGame || !canClick){
		return;
	}
	int historyScore = GAMEDATA::getInstance()->getHistoryScore();
	int gameScore = GAMEDATA::getInstance()->getGameScore();
	if (historyScore < gameScore){
		GAMEDATA::getInstance()->setHistoryScore(gameScore);
	}
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	chcekPropUse();
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	goToGameScene();
#endif
}

void GameResultLayer::goToGameScene(){
	Audio::getInstance()->playSound("Music/game_start.mp3");
	bankRaiseLayer->setVisible(false);
	Director::getInstance()->replaceScene(TransitionFade::create(1, TollgateScene::scene()));
}

void GameResultLayer::chcekPropUse(){
	if (GAMEDATA::getInstance()->isSuperSelect()){
		int superPropNum = GAMEDATA::getInstance()->getSuperPropNum();
		if (superPropNum > 0){
			GAMEDATA::getInstance()->setUsePropType(PROP_SUPER);
			goToGameScene();
		}
		else{
			CallAndroidMethod::getInstance()->pay(15);
		}
	}
	else if (GAMEDATA::getInstance()->isMagneticSelect()){
		int magneticPropNum = GAMEDATA::getInstance()->getMagneticPropNum();
		if (magneticPropNum > 0){
			GAMEDATA::getInstance()->setUsePropType(PROP_MAGNETIC);
			goToGameScene();
		}
		else{
			CallAndroidMethod::getInstance()->pay(16);
		}
	}
	else if (GAMEDATA::getInstance()->isPotentialSelect()){
		int potentialPropNum = GAMEDATA::getInstance()->getPotentialPropNum();
		if (potentialPropNum > 0){
			GAMEDATA::getInstance()->setUsePropType(PROP_POTENTIAL);
			goToGameScene();
		}
		else{
			CallAndroidMethod::getInstance()->pay(17);
		}
	}
	else{
		goToGameScene();
	}
}

void GameResultLayer::back(){
	if (clickedBack || !canClick){
		return;
	}
	int historyScore = GAMEDATA::getInstance()->getHistoryScore();
	int gameScore = GAMEDATA::getInstance()->getGameScore();
	if (historyScore < gameScore){
		GAMEDATA::getInstance()->setHistoryScore(gameScore);
	}
	Audio::getInstance()->playSound("Music/paddle_hit.wav");
	ResultGold::cleanInstance();
	Director::getInstance()->replaceScene(TransitionFade::create(1, MenuScene::create()));
}

bool GameResultLayer::upgradeSuper(Touch* touch, Event* event){
	if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())){
		if (!canClick){
			return true;
		}
		int level = GAMEDATA::getInstance()->getSuperLevel();
		if (!GAMEDATA::getInstance()->isSuperSelect()){
			GAMEDATA::getInstance()->setMagneticSelect(false);
			GAMEDATA::getInstance()->setSuperSelect(true);
			GAMEDATA::getInstance()->setPotentialSelect(false);
			prop_select_icon->setVisible(true);
			prop_select_icon->setPosition(ccp(432, 320));
		}
		else{
			GAMEDATA::getInstance()->setSuperSelect(false);
			prop_select_icon->setVisible(false);
		}
		return true;
	}
	return false;
}

bool GameResultLayer::upgradeMagnetic(Touch* touch, Event* event){
	if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())){
		if (!canClick){
			return true;
		}
		int level = GAMEDATA::getInstance()->getMagneticLevel();
		if (!GAMEDATA::getInstance()->isMagneticSelect()){
			prop_select_icon->setVisible(true);
			prop_select_icon->setPosition(ccp(432, 236));
			GAMEDATA::getInstance()->setMagneticSelect(true);
			GAMEDATA::getInstance()->setSuperSelect(false);
			GAMEDATA::getInstance()->setPotentialSelect(false);
		}
		else{
			prop_select_icon->setVisible(false);
			GAMEDATA::getInstance()->setMagneticSelect(false);
		}
		return true;
	}
	return false;
}

bool GameResultLayer::upgradePotential(Touch* touch, Event* event){
	if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())){
		if (!canClick){
			return true;
		}
		int level = GAMEDATA::getInstance()->getPotentialLevel();
		if (!GAMEDATA::getInstance()->isPotentialSelect()){
			prop_select_icon->setVisible(true);
			prop_select_icon->setPosition(ccp(432, 150));
			GAMEDATA::getInstance()->setMagneticSelect(false);
			GAMEDATA::getInstance()->setSuperSelect(false);
			GAMEDATA::getInstance()->setPotentialSelect(true);
		}
		else{
			prop_select_icon->setVisible(false);
			GAMEDATA::getInstance()->setPotentialSelect(false);
		}
		return true;
	}
	return false;
}


void GameResultLayer::update(float dt){
	if (MenuLayer::passPropCheck){
		goToGameScene();
		MenuLayer::passPropCheck = false;
	}
	if (this->isVisible()){
		animTime += dt / 0.05;
		gameScoreNum = totalGameScore*animTime / 60;
		if (gameScoreNum >= totalGameScore){
			gameScoreNum = totalGameScore;
		}
		gameScore->setString(String::createWithFormat("%d", (int)gameScoreNum)->_string);
		if (animTime >= 60){
			if (!hasStartRankAnim){
				hasStartRankAnim = true;
				rankNum->setVisible(true);
				auto action1 = ScaleTo::create(0.3f, 3.5f);
				auto action2 = ScaleTo::create(0.09f, 1);
				auto seq = Sequence::create(action1, action2, NULL);
				rankNum->runAction(seq);
			}
		}
		if (animTime >= 80){
			if (GameResultInfo::getInstance()->getGameResult() == 1){
				if (!hasStartMissionAnim){
					hasStartMissionAnim = true;
					mission->setVisible(true);
					auto action1 = ScaleTo::create(0.3f, 3.5f);
					auto action2 = ScaleTo::create(0.09f, 1);
					auto seq = Sequence::create(action1, action2, NULL);
					mission->runAction(seq);
				}
			}
			else{
				if (animTime < 115){
					animTime = 115;
				}
			}
		}
		if (animTime >= 115){
			if (GAMEDATA::getInstance()->getPlayerLevel() >= 4 && GAMEDATA::getInstance()->getPlayerLevel() % 2 == 0
				&& !GAMEDATA::getInstance()->isHasShowPlayerUpgradePay()){
				GAMEDATA::getInstance()->setHasShowPlayerUpgradePay(true);
				if (!hasShowPay){
					hasShowPay = true;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
					CallAndroidMethod::getInstance()->pay(3);
#endif
				}
			}
			else if (GAMEDATA::getInstance()->getPlayRounds() == 1){
				if (!hasShowPay){
					hasShowPay = true;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
					CallAndroidMethod::getInstance()->pay(3);
#endif
				}
			}
			else if (GAMEDATA::getInstance()->getPlayRounds() == 2){
				if (!hasShowPay){
					hasShowPay = true;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
					CallAndroidMethod::getInstance()->pay(2);
#endif
				}
			}
			else if (PLAYERRANK::getInstance()->getRankList(GAMEDATA::getInstance()->getGameScore()) < PLAYERRANK::getInstance()->getRankList(GAMEDATA::getInstance()->getHistoryScore())){
				bankRaiseLayer->setVisible(true);
				if (animTime > 180){
					bankRaiseLayer->setVisible(false);
					canClick = true;
				}
			}
			else{
				canClick = true;
			}
		}
	}
	//�������Ƿ�����δ������ʾ����
	if (NULL != superIcon&&!isShowSuper&&GAMEDATA::getInstance()->getSuperLevel() <= 10){
		showLightAnim(superIcon);
		isShowSuper = true;
	}
	if (NULL != magneticIcon&&!isShowMagnetic&&GAMEDATA::getInstance()->getMagneticLevel()<+10){
		showLightAnim(magneticIcon);
		isShowMagnetic = true;
	}
	if (NULL != potentialIcon&&!isShowPotential&&GAMEDATA::getInstance()->getPotentialLevel() <= 10){
		showLightAnim(potentialIcon);
		isShowPotential = true;
	}
}

void GameResultLayer::showLightAnim(Sprite* sprite){
	auto animation = Animation::create();
	for (int i = 1; i < 17; i++)
	{
		std::string szName = "prop_light_" + cocos2d::String::createWithFormat("%d", i)->_string + ".png";
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
	}
	animation->setDelayPerUnit(1 / 24.0f);
	animation->setRestoreOriginalFrame(false);
	auto action = Animate::create(animation);
	auto seq = Sequence::create(action, NULL);
	Sprite* posSprite = Sprite::create();
	posSprite->setPosition(sprite->getPosition());
	this->addChild(posSprite);
	posSprite->runAction(RepeatForever::create(seq));
}

