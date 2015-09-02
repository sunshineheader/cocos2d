#include "GAMEDATA.h"
#include "cocos2d.h"
using namespace cocos2d;

GAMEDATA* GAMEDATA::_instance = 0;

GAMEDATA::GAMEDATA(){
	this->init();
}

void GAMEDATA::init(){
	this->level = 0;
	this->score = 0;
	this->lastClikTime = 0;
}

GAMEDATA* GAMEDATA::getInstance(){
	if(_instance == 0){
		_instance = new GAMEDATA();
	}
	return _instance;
}

void GAMEDATA::setSoundState(bool state) {
	UserDefault::getInstance()->setBoolForKey("soundState",state);
}

bool GAMEDATA::getSoundState() {
	return UserDefault::getInstance()->getBoolForKey("soundState",true);
}

void GAMEDATA::setMusicState(bool state) {
	UserDefault::getInstance()->setBoolForKey("musicState",state);
}

bool GAMEDATA::getMusicState() {
	return UserDefault::getInstance()->getBoolForKey("musicState",true);
}

int GAMEDATA::getScore(){
	return score;
}

void GAMEDATA::setScore(int score){
	this->score = score;
	auto record =UserDefault::getInstance()->getIntegerForKey("record",0);
	if(score>record){
		UserDefault::getInstance()->setIntegerForKey("record",score);
	}
}


int GAMEDATA::getLevel(){
	return level;
}
void GAMEDATA::setLevel(int level){
	this->level = level;
}



int  GAMEDATA::getReviveNum(){
	return UserDefault::getInstance()->getIntegerForKey("reviveNum",0);
}

void  GAMEDATA::setReviveNum(int num){
	UserDefault::getInstance()->setIntegerForKey("reviveNum",num);
}


int GAMEDATA::getLoginTimes(){
	return UserDefault::getInstance()->getIntegerForKey("loginTimes",0);
}


void GAMEDATA::setLoginTimes(){
	auto times = getLoginTimes()+1;
	UserDefault::getInstance()->setIntegerForKey("loginTimes",times);
}

int  GAMEDATA::getLastClikTime(){
	return lastClikTime;
}


void GAMEDATA::setLastClikTime(int clickTime){
	this->lastClikTime = clickTime;
}


long GAMEDATA::getCurrentTime()   
{    
	struct timeval tv;    
	gettimeofday(&tv,NULL);    
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;      
}  

