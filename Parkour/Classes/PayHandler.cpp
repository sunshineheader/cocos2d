#include "PayHandler.h"
#include "GameLayer.h"
#include "GameData.h"
#include "MenuLayer.h"
#include "MenuLayer.h"
#include "CallAndroidMethod.h"
#include "GameStateInfo.h"
#include "GameState.h"
#include "Player.h"
#include "PlayerState.h"
#include "ResultGold.h"
#include "TollgateScene.h"
#include "GameResultLayer.h"
#include "Audio.h"

static PayHandler* _instance = nullptr;
bool PayHandler::needMagnetic = false;
bool PayHandler::needSuper = false;
bool PayHandler::needFly = false;
bool PayHandler::revivaled = false;
PayHandler* PayHandler::getInstance() {
	if (!_instance) {
		_instance = new PayHandler();
	}
	return _instance;
}

void PayHandler::payCallback(int requestId, int resultId) {
	if (resultId == 0) {
		GAMEDATA::getInstance()->setPaySuccess(true);
		Audio::getInstance()->playSound("Music/pay_result_success.ogg");
	}
	else {
		Audio::getInstance()->playSound("Music/pay_result_fail.ogg");
	}
	if (GameStateInfo::getInstance()->getGameState() == Game_Pause) {
		GameStateInfo::getInstance()->setGameState(Game_Playing);
	}
	switch (requestId) {
	case 1:
		if (resultId == 0) {
			GAMEDATA::getInstance()->setPotentialPropNum(
				GAMEDATA::getInstance()->getPotentialPropNum() + 10);
			ResultGold::getInstance()->refreshPropNum();
		}
		GameStateInfo::getInstance()->setGameState(Game_Playing);
		break;
	case 10:
		if (resultId == 0) {
			GAMEDATA::getInstance()->setPotentialPropNum(
				GAMEDATA::getInstance()->getPotentialPropNum() + 10);
			ResultGold::getInstance()->refreshPropNum();
		}
		Player::skillState = Player_Fly;
		needFly = true;
		GameStateInfo::getInstance()->setGameState(Game_Playing);
		break;
	case 2:
	case 11:
		if (resultId == 0) {
			GAMEDATA::getInstance()->setGoldNum(
				GAMEDATA::getInstance()->getGoldNum() + 50000);
			ResultGold::getInstance()->refreshGold();
		}
		GameResultLayer::canClick = true;
		if (requestId == 11) {
			ResultGold::clickedUpgradeProp = false;
		}
		break;
	case 3:
		if (resultId == 0) {
			GAMEDATA::getInstance()->setGoldNum(
				GAMEDATA::getInstance()->getGoldNum() + 50000);
			ResultGold::getInstance()->refreshGold();
		}
		GameResultLayer::canClick = true;
		break;
	case 4:
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CCLog("PayHandler->payCallback resultId = %d", resultId);
#endif
		if (resultId == 0) {
			GAMEDATA::getInstance()->setReviveNum(4);
			GameStateInfo::getInstance()->setGameState(Game_Playing);
			Player::skillState = Player_Fly;
			needFly = true;
			revivaled = true;
			TollgateScene::showRevivePay = true;
	}
		else {
			GameStateInfo::getInstance()->setGameState(Game_End);
			TollgateScene::showRevivePay = false;
		}
		break;
	case 5:
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CCLog("Android platform paypoint 5 resultId back");
#endif
		GameStateInfo::getInstance()->setGameState(Game_Playing);
		TollgateScene::payPause = false;
		break;
	case 6:
		if (resultId == 0) {
			GAMEDATA::getInstance()->setSuperPropNum(
				GAMEDATA::getInstance()->getSuperPropNum() + 9);
			ResultGold::getInstance()->refreshPropNum();
			GAMEDATA::getInstance()->setUsePropType(PROP_SUPER);
			Player::skillState = Player_Super;
		}
		GameStateInfo::getInstance()->setGameState(Game_Playing);
		break;
	case 7:
		if (resultId == 0) {
			GAMEDATA::getInstance()->setMagneticPropNum(
				GAMEDATA::getInstance()->getMagneticPropNum() + 9);
			ResultGold::getInstance()->refreshPropNum();
			Player::skillState = Player_Magic;
		}
		GameStateInfo::getInstance()->setGameState(Game_Playing);
		break;
	case 8:
		if (resultId == 0) {
			GAMEDATA::getInstance()->setHasPaySignIn(true);
			GAMEDATA::getInstance()->setPotentialPropNum(
				GAMEDATA::getInstance()->getPotentialPropNum() + 1);
			ResultGold::getInstance()->refreshPropNum();
			CallAndroidMethod::getInstance()->sign();
			MenuLayer::showSignInPrize = true;
		}
		else {
			MenuLayer::canStartGame = true;
		}
		break;
		//免费复活计费点,区分剩余次数
	case 9:
	case 12:
	case 13:
	case 14:
		if (resultId == 0) {
			GameStateInfo::getInstance()->setGameState(Game_Playing);
			Player::skillState = Player_Fly;
			needFly = true;
			revivaled = true;
			int reviveNum = GAMEDATA::getInstance()->getReviveNum() - 1;
			GAMEDATA::getInstance()->setReviveNum(reviveNum);
			TollgateScene::showRevivePay = true;
		}
		else {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			CCLog("Android platform paypoint 9 resultId != 0");
#endif
			GameStateInfo::getInstance()->setGameState(Game_End);
			TollgateScene::showRevivePay = false;
		}
		break;

	case 15:
		if (resultId == 0) {
			GAMEDATA::getInstance()->setSuperPropNum(
				GAMEDATA::getInstance()->getSuperPropNum() + 10);
			ResultGold::getInstance()->refreshPropNum();
			GAMEDATA::getInstance()->setUsePropType(PROP_SUPER);
		}
		else{
			GAMEDATA::getInstance()->setUsePropType(PROP_NONE);
		}
		MenuLayer::passPropCheck = true;
		break;
	case 16:
		if (resultId == 0) {
			GAMEDATA::getInstance()->setMagneticPropNum(
				GAMEDATA::getInstance()->getMagneticPropNum() + 10);
			ResultGold::getInstance()->refreshPropNum();
			GAMEDATA::getInstance()->setUsePropType(PROP_MAGNETIC);
		}
		else{
			GAMEDATA::getInstance()->setUsePropType(PROP_NONE);
		}
		MenuLayer::passPropCheck = true;
		break;
	case 17:
		if (resultId == 0) {
			GAMEDATA::getInstance()->setPotentialPropNum(
				GAMEDATA::getInstance()->getPotentialPropNum() + 10);
			ResultGold::getInstance()->refreshPropNum();
			GAMEDATA::getInstance()->setUsePropType(PROP_POTENTIAL);
		}
		else{
			GAMEDATA::getInstance()->setUsePropType(PROP_NONE);
		}
		MenuLayer::passPropCheck = true;
		break;
	case 18:
		if (resultId == 0) {
			GAMEDATA::getInstance()->setGoldNum(
				GAMEDATA::getInstance()->getGoldNum() + 50000);
			ResultGold::getInstance()->refreshGold();
		}
		GameResultLayer::canClick = true;
	default:
		break;
}
}

void PayHandler::moreGameCallback(bool openMoreGame) {
	MenuLayer::needShowMoreGame = openMoreGame;
}

