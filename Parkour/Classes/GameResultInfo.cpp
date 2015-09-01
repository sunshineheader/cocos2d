#include "GameResultInfo.h"
#include "cocos2d.h"

using namespace cocos2d;

GameResultInfo* GameResultInfo::_instance = 0;

GameResultInfo::GameResultInfo(){
	this->init();
}

void GameResultInfo::init(){
	gameResult = 0;
}

GameResultInfo* GameResultInfo::getInstance(){
	if(_instance == 0){
		_instance = new GameResultInfo();
	}
	return _instance;
}

void GameResultInfo::setGameResult(int game_result){
	gameResult = game_result;
}

int GameResultInfo::getGameResult(){
	return gameResult;
}
