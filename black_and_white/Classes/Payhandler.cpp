#include "Payhandler.h"
#include "PayForGame.h"
#include "GameData.h"
#include "GameLayerScene.h"
static PayHandler* _instance = nullptr;

PayHandler* PayHandler::getInstance() {
	if (!_instance) {
		_instance = new PayHandler();
	}
	return _instance;
	delete _instance;
	_instance = nullptr;
}

void PayHandler::payCallback(int requestId, int resultId){

	switch (requestId)
	{
	case 1:
		if (resultId == 0){
			GameData::getInstance()->set_xiao_guo(true);
		}
		break;
	case 2:
		if (resultId == 0){
			GameData::getInstance()->set_currcert_life(5);
			GameData::getInstance()->reStart = true;
		}
		else if (resultId == 1){
			GameData::getInstance()->gotoResult = true;
		}
		break;
	case 3:
		if (resultId == 0){
			GameData::getInstance()->set_error_number(1);
		}
		break;
	case 4:
		if (resultId == 0){
			GameData::getInstance()->set_xiao_guo(true);
		}
		break;
	case 5:
		if (resultId == 0){
			GameData::getInstance()->set_currcert_life(4);
			GameData::getInstance()->reStart = true;
		}
		else if (resultId == 1){
			GameData::getInstance()->gotoResult = true;
		}
		break;
	case 6:
		if (resultId == 0){
			GameData::getInstance()->set_currcert_life(3);
			GameData::getInstance()->reStart = true;
		}
		else if (resultId == 1){
			GameData::getInstance()->gotoResult = true;
		}
		break;
	case 7:
		if (resultId == 0){
			GameData::getInstance()->set_currcert_life(2);
			GameData::getInstance()->reStart = true;
		}
		else if (resultId == 1){
			GameData::getInstance()->gotoResult = true;
		}
		break;
	case 8:
		if (resultId == 0){
			GameData::getInstance()->set_currcert_life(1);
			GameData::getInstance()->reStart = true;
		}
		else if (resultId == 1){
			GameData::getInstance()->gotoResult = true;
		}
		break;
	default:
		break;
	}
}

void PayHandler::moreGameCallback(bool openMoreGame) {
	//MenuLayer::needShowMoreGame = openMoreGame;
}

