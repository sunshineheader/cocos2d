#include "GameData.h"
#include "cocos2d.h"
using namespace cocos2d;
GAMEDATA* GAMEDATA::_instance = 0;
GAMEDATA::GAMEDATA(){
	this->init();
}
GAMEDATA* GAMEDATA::getInstance(){
	if(_instance == 0){
		_instance = new GAMEDATA();
	}
	return _instance;
}

void GAMEDATA::init(){
	lastLevelScore=0;
    setCurLevel(0);
	setCurScore(0);
	setHistoryScore(UserDefault::getInstance()->getIntegerForKey("highestScore",0));
	setUserLevel(UserDefault::getInstance()->getIntegerForKey("userLevel",0));
	setGoldNum(UserDefault::getInstance()->getIntegerForKey("goldNum",1000));
	setPowerStoneNum(UserDefault::getInstance()->getIntegerForKey("powerStoneNum",0));
	setPrizeTimes(UserDefault::getInstance()->getIntegerForKey("prizeTimes",3));
	setAddTimeNum(UserDefault::getInstance()->getIntegerForKey("addTimeNum",0));
	setBombNum(UserDefault::getInstance()->getIntegerForKey("bombNum",0));
	setChuiNum(UserDefault::getInstance()->getIntegerForKey("chuiNum",0));
	setBiNum(UserDefault::getInstance()->getIntegerForKey("biNum",0));
	setReviveNum(UserDefault::getInstance()->getIntegerForKey("reviveNum",0));
	setHasShowRegisterPay(UserDefault::getInstance()->getBoolForKey("showRegisterPay",false));
	setSoundEffect(UserDefault::getInstance()->getBoolForKey("soundEffect",true));
	setMusicState(UserDefault::getInstance()->getBoolForKey("musicState",true));
	setCurExpNum(UserDefault::getInstance()->getIntegerForKey("curExpNum",0));
	setPrizeGoldNum(UserDefault::getInstance()->getIntegerForKey("prizeGoldNum",15));
	setTotalScore(UserDefault::getInstance()->getIntegerForKey("totalScore",0));
	setPaySuccess(UserDefault::getInstance()->getBoolForKey("paySuccess",false));
}

void GAMEDATA::setCurLevel(int level){
	if(level < 0){
		return;
	}
	cur_level = level;
	next_level = level + 1;
	next_score = getScoreByLevel(next_level);
}

int GAMEDATA::getScoreByLevel(int level){
	int score = 0;
	if (level == 1)
	{
		score = 10000;
	}
	else if (level == 2)
	{
		score = 3000;
	}
	else if ( (level >=3) && (level <= 10) )
	{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
		score = 3000 + 3000 * (level - 2);
	}
	else
	{
		score = 27000 + 4000 * (level - 10);
	}
	return score;
}

int GAMEDATA::getJiangli(int size){
	static const int jiangli[10][2] =
	{
		{0, 2000},
		{1, 1880},
		{2, 1620},
		{3, 1520},
		{4, 1480},
		{5, 1400},
		{6, 1280},
		{7, 1020},
		{8, 720},
		{9, 380},
	};
	if(size>9 || size<0){
		return 0;
	}
	return jiangli[size][1];
}

int GAMEDATA::getFullExpNum(int userLevel){
	return userLevel+(userLevel/10)*1+1;
}

float GAMEDATA::getScoreAddPer(int userLevel){
	return userLevel*0.01;
}

int GAMEDATA::getUpgradePrizeNum(int userLevel){
	return (userLevel/10+1)*1000;
}


void GAMEDATA::saveHighestScore(){
	UserDefault::getInstance()->setIntegerForKey("highestScore",getHistoryScore());
}

void GAMEDATA::saveGoldNum(){
	UserDefault::getInstance()->setIntegerForKey("goldNum",getGoldNum());
}

void GAMEDATA::savePowerStoneNum(){
	UserDefault::getInstance()->setIntegerForKey("powerStoneNum",getPowerStoneNum());
}

void GAMEDATA::saveUserLevel(){
	UserDefault::getInstance()->setIntegerForKey("userLevel",getUserLevel());
}

void GAMEDATA::savePrizeTimes(){
	UserDefault::getInstance()->setIntegerForKey("prizeTimes",getPrizeTimes());
}

void GAMEDATA::saveAddTimeNum(){
	UserDefault::getInstance()->setIntegerForKey("addTimeNum",getAddTimeNum());
}

void GAMEDATA::saveBombNum(){
	UserDefault::getInstance()->setIntegerForKey("bombNum",getBombNum());
}

void GAMEDATA::saveChuiNum(){
	UserDefault::getInstance()->setIntegerForKey("chuiNum",getChuiNum());
}

void GAMEDATA::saveBiNum(){
	UserDefault::getInstance()->setIntegerForKey("biNum",getBiNum());
}

void GAMEDATA::saveReviveNum(){
	UserDefault::getInstance()->setIntegerForKey("reviveNum",getReviveNum());
}

void GAMEDATA::saveShowRegisterPay(){
	UserDefault::getInstance()->setBoolForKey("showRegisterPay", true);
}
void GAMEDATA::saveSoundEffect(){
	UserDefault::getInstance()->setBoolForKey("soundEffect", getSoundEffect());
}

void GAMEDATA::saveMusicState(){
	UserDefault::getInstance()->setBoolForKey("musicState", getMusicState());
}

void GAMEDATA::saveCurExpNum(){
	UserDefault::getInstance()->setIntegerForKey("curExpNum", getCurExpNum());
}

void GAMEDATA::savePrizeGoldNum(){
	UserDefault::getInstance()->setIntegerForKey("prizeGoldNum", getPrizeGoldNum());
}

void GAMEDATA::saveTotalScore(){
	UserDefault::getInstance()->setIntegerForKey("totalScore", getTotalScore());
}

void GAMEDATA::savePaySuccess(){
	UserDefault::getInstance()->setBoolForKey("paySuccess", isPaySuccess());
}


void GAMEDATA::setLastLevelScore(int score){
	lastLevelScore =score;
}

int GAMEDATA::getLastLevelScore(){
	return lastLevelScore;
}


int GAMEDATA::getIsBuySuperGift(){
	return UserDefault::getInstance()->getBoolForKey("superGift", false);
}
void GAMEDATA::setIsBuySuperGift(){
	UserDefault::getInstance()->setBoolForKey("superGift", true);
}
