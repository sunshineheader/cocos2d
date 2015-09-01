#include "GamePayHandler.h"
#include "GameLayer.h"
#include "GameData.h"
#include "GameState.h"
#include "BottomMenu.h"

static GamePayHandler* _instance = nullptr;
GamePayHandler* GamePayHandler::getInstance()
{
	if (!_instance)
	{
		_instance = new GamePayHandler();
	}
	return _instance;
}

void GamePayHandler::payCallback(int requestId, int resultId){
	GAMESTATE::getInstance()->setIsPaying(false);
	switch (requestId)
	{
	case 1:
		GAMESTATE::getInstance()->setGamePause(false);
		break;
	case 2:
	{
		if (resultId == 0){
			GAMESTATE::getInstance()->setIsRevive(true);
		}
		else{
			GAMESTATE::getInstance()->setGameOver(true);
		}
		GAMESTATE::getInstance()->setGamePause(false);
	}
	break;
	case 3:
	{
		if (resultId == 0){
			GAMEDATA* data = GAMEDATA::getInstance();
			if (BottomMenu::clickFindBtn){
				data->setPropFindNum(data->getPropFindNum() + 19);
				GAMESTATE::getInstance()->setUsePropFind(true);
			}
			else{
				data->setPropFindNum(data->getPropFindNum() + 20);
			}
			BottomMenu::getInstance()->updatePropNum();
		}
		BottomMenu::clickFindBtn = false;
		GAMESTATE::getInstance()->setGamePause(false);
	}
	break;
	case 4:
	{if (resultId == 0){
		GAMEDATA* data = GAMEDATA::getInstance();
		if (BottomMenu::clickTimeBtn){
			data->setPropTimeNum(data->getPropTimeNum() + 19);
			GAMESTATE::getInstance()->setUsePropTime(true);
		}
		else{
			data->setPropTimeNum(data->getPropTimeNum() + 20);
		}
		BottomMenu::clickTimeBtn = true;
		BottomMenu::getInstance()->updatePropNum();
	}
	GAMESTATE::getInstance()->setGamePause(false); }
	break;
	case 5:
	{if (resultId == 0){
		GAMEDATA* data = GAMEDATA::getInstance();
		data->setPropTimeNum(data->getPropTimeNum() + 10);
		data->setPropFindNum(data->getPropFindNum() + 10);
		BottomMenu::getInstance()->updatePropNum();
	}
	GAMESTATE::getInstance()->setGamePause(false);
	}
	break;
	case 6:
	{if (resultId == 0){
		int num = random(1, 20);
		GAMEDATA* data = GAMEDATA::getInstance();
		data->setPropTimeNum(data->getPropTimeNum() + num);
		data->setPropFindNum(data->getPropFindNum() + 20 - num);
		BottomMenu::getInstance()->updatePropNum();
	}
	GAMESTATE::getInstance()->setGamePause(false); }
	break;
	case 7:
	{if (resultId == 0){
		BottomMenu::getInstance()->plusGameTime(20);
		BottomMenu::getInstance()->updatePropNum();
	}
	GAMESTATE::getInstance()->setGamePause(false); }
	break;
	case 8:
	{
		GAMEDATA* data = GAMEDATA::getInstance();
		data->setPropTimeNum(data->getPropTimeNum() + 1);
		data->setPropFindNum(data->getPropFindNum() + 1);
		BottomMenu::getInstance()->updatePropNum();
		GAMESTATE::getInstance()->setGamePause(false);
	}
	break;
	case 9:
	{
		GAMESTATE::getInstance()->setGamePause(false);
		BottomMenu::getInstance()->plusGameTime(20);
	}
	break;
	default:
		GAMESTATE::getInstance()->setGamePause(false);
		break;
	}
}

void GamePayHandler::showMoreGameNative(bool show){
	GAMESTATE::getInstance()->setIsShowMoreGame(show);
}

