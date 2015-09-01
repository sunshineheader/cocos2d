#include "GameStateInfo.h"
#include "cocos2d.h"
#include "GameState.h"

using namespace cocos2d;

GameStateInfo* GameStateInfo::_instance = 0;

GameStateInfo::GameStateInfo(){
	this->init();
}

void GameStateInfo::init(){
	state = Game_End;
}

GameStateInfo* GameStateInfo::getInstance(){
	if(_instance == 0){
		_instance = new GameStateInfo();
	}
	return _instance;
}

void GameStateInfo::setGameState(int gameState){
	state = gameState;
}

int GameStateInfo::getGameState(){
	return state;
}
