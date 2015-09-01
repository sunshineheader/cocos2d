#include "GAMEDATA.h"
#include "cocos2d.h"
using namespace cocos2d;

GAMEDATA* GAMEDATA::_instance = 0;

GAMEDATA::GAMEDATA(){
	this->init();
}
GAMEDATA* GAMEDATA::getInstance(){
	if (_instance == 0){
		_instance = new GAMEDATA();
	}
	return _instance;

}

void GAMEDATA::init(){
	this->level = 0;
	this->gametime = 10;
	this->gamestate = 0;
	this->score = 1000000;
	this->lastClikTime = 0;
	this->Ascore = 0;
	this->times = 0;
	this->percent = 100;
	setPaySuccess(UserDefault::getInstance()->getBoolForKey("paySuccess", false));
	setaddtimeNum(UserDefault::getInstance()->getIntegerForKey("addnum", 5));
	settipNum(UserDefault::getInstance()->getIntegerForKey("tipnum", 5));
	setrefreshNum(UserDefault::getInstance()->getIntegerForKey("renum", 5));
}

void GAMEDATA::savePaySuccess(){
	UserDefault::getInstance()->setBoolForKey("paySuccess", isPaySuccess());
}

void GAMEDATA::saveaddtimeNum(){
	UserDefault::getInstance()->setIntegerForKey("addnum", getaddtimeNum());
}

void GAMEDATA::savetipNum(){
	UserDefault::getInstance()->setIntegerForKey("tipnum", gettipNum());
}

void GAMEDATA::saverefreshNum(){
	UserDefault::getInstance()->setIntegerForKey("renum", getrefreshNum());
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

void GAMEDATA::saveMusicState(){
	UserDefault::getInstance()->setBoolForKey("musicState", getMusicState());

}

void GAMEDATA::setDay(int value){

	UserDefault::getInstance()->setIntegerForKey("day",value);
}

int GAMEDATA::getDay(){

	return UserDefault::getInstance()->getIntegerForKey("day",0);

}

void GAMEDATA::savaDay(){
	UserDefault::getInstance()->setIntegerForKey("day", getDay());

}

int GAMEDATA::getScore(){
	return score;
}
void GAMEDATA::settime(float value){
	gametime = value;

}

float GAMEDATA::gettime(){

	return gametime;

}


void GAMEDATA::setAchievescore(float value){

	Ascore = value;
}

float GAMEDATA::getAchievescore(){
	return Ascore;
}



void GAMEDATA::setPercent(int value){
	percent = value;

}

int GAMEDATA::getPercent(){

	return percent;

}
int GAMEDATA::getTimes(){
	return times;

}

void GAMEDATA::setTimes(int value){
	times = value;
}

void GAMEDATA::setstate(int value){
	gamestate = value;

}

int GAMEDATA::getstate(){

	return gamestate;

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
 
void GAMEDATA::saveReviveNum(){
	UserDefault::getInstance()->setIntegerForKey("reviveNum", getReviveNum());
}


int GAMEDATA::getLoginTimes(){
	return UserDefault::getInstance()->getIntegerForKey("loginTimes",0);
}


void GAMEDATA::setLoginTimes(int value){
	UserDefault::getInstance()->setIntegerForKey("loginTimes",value);
}


void GAMEDATA::saveLoginTimes(){
	UserDefault::getInstance()->setIntegerForKey("loginTimes", getLoginTimes());
}
int  GAMEDATA::getLastClikTime(){
	return lastClikTime;
}


void GAMEDATA::setLastClikTime(int clickTime){
	this->lastClikTime = clickTime;
}


long GAMEDATA::getCurrentTime()   
{     
	struct tm *tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
	int day = tm->tm_mday;

	return day;
}  

