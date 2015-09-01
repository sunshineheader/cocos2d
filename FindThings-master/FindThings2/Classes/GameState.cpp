#include "GAMESTATE.h"
#include "cocos2d.h"
using namespace cocos2d;

GAMESTATE* GAMESTATE::_instance = 0;

GAMESTATE::GAMESTATE(){
	this->init();
}

void GAMESTATE::init(){
	reset();
}

void GAMESTATE::reset(){
	gamePause = false;
	gameOver = false;
	isUseFind = false;
	isUseTime = false;
	isPaying = false;
	isRevive = false;
	isShowPayFind = false;
	isShowPayTime = false;
	isFirstTask = true;
	isGuide = false;
	isCreate=false;
}

GAMESTATE* GAMESTATE::getInstance(){
	if(_instance == 0){
		_instance = new GAMESTATE();
	}
	return _instance;
}

void GAMESTATE::setGamePause(bool pause){
	gamePause = pause;
}

bool GAMESTATE::getGamePause(){
	return gamePause;
}

void GAMESTATE::setGameOver(bool over){
	gameOver = over;
}

bool GAMESTATE::getGameOver(){
	return gameOver;
}

bool GAMESTATE::isUsePropFind(){
	return isUseFind;
}

void GAMESTATE::setUsePropFind(bool b){
	this->isUseFind = b;
}

bool GAMESTATE::isUsePropTime(){
	return isUseTime;
}

void GAMESTATE::setUsePropTime(bool b){
	this->isUseTime = b;
}

bool GAMESTATE::getIsPaying(){
	return isPaying;
}
void GAMESTATE::setIsPaying(bool b){
	isPaying =b;
}
bool GAMESTATE::getIsRevive(){
	return isRevive;
}
void GAMESTATE::setIsRevive(bool b){
	isRevive = b;
}

bool GAMESTATE::getIsShowPayTime(){
	return isShowPayTime;
}

void GAMESTATE::setIsShowPayTime(bool b){
	isShowPayTime = b;
}

bool GAMESTATE::getIsShowPayFind(){
	return  isShowPayFind;
}

void GAMESTATE::setIsShowPayFind(bool b){
	isShowPayFind = b;
}

bool GAMESTATE::getIsFirstTask(){
	return isFirstTask;
}


void GAMESTATE::setIsFirstTask(bool b){
    isFirstTask = b;
}

bool GAMESTATE::getIsGuide(){
	return isGuide;
}



void GAMESTATE::setIsGuide(bool b){
	isGuide = b;
}

bool GAMESTATE::getIsCreateGuideTask(){
	return isCreate;
}


void GAMESTATE::setIsCreateGuideTask(bool b){
	isCreate = b;
}

bool GAMESTATE::getIsShowMoreGame(){
	return isShowMoreGame;
}

void GAMESTATE::setIsShowMoreGame(bool b){
	this->isShowMoreGame = b;
}