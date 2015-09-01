#include "GAMEDATA.h"
#include "cocos2d.h"
using namespace cocos2d;

GAMEDATA* GAMEDATA::_instance = 0;

GAMEDATA::GAMEDATA(){
	this->init();
}

void GAMEDATA::init(){
	magneticLevel = UserDefault::getInstance()->getIntegerForKey("magneticLevel", 1);
	superLevel = UserDefault::getInstance()->getIntegerForKey("superLevel", 1);
	potentialLevel = UserDefault::getInstance()->getIntegerForKey("potentialLevel", 1);
	historyScore = UserDefault::getInstance()->getIntegerForKey("historyScore", 0);
	playerLevel = UserDefault::getInstance()->getIntegerForKey("playerLevel", 0);
	costGoldNums = UserDefault::getInstance()->getIntegerForKey("costGoldNums", 0);
	playRounds = UserDefault::getInstance()->getIntegerForKey("playRounds", 0);
	firstLognin = UserDefault::getInstance()->getBoolForKey("firstLognin", true);
	hasShowSignInPay = false;
}

void GAMEDATA::reset(){
	gameScore = 0;
	distance = 0;
	eatGoldNum = 0;
	dodgeMonsterNums = 0;
	activeGoldNum = 0;
	potentialIndex = 1;
	jumpTimes = 0;
	slideTimes = 0;
	eatPotentialPropNums = 0;
	eatSuperPropNums = 0;
	eatMagneticPrpNums = 0;
	activePotentialTimes = 0;
	propPotentialTimes = 0;
	eatGoldByMagneticNums = 0;
	distanceBySuper = 0;
	distanceByPotential = 0;
	hasFinishedNum = 0;
}

GAMEDATA* GAMEDATA::getInstance(){
	if (_instance == 0){
		_instance = new GAMEDATA();
	}
	return _instance;
}

void GAMEDATA::setGameScore(int score){
	gameScore = score;
}

int GAMEDATA::getGameScore(){
	return gameScore;
}

void GAMEDATA::setGoldNum(int gold_num){
	UserDefault::getInstance()->setIntegerForKey("goldNum", gold_num);
}

int GAMEDATA::getGoldNum(){
	return UserDefault::getInstance()->getIntegerForKey("goldNum", 1000);
}

void GAMEDATA::setPlayerLevel(int player_level){
	playerLevel = player_level;
	UserDefault::getInstance()->setIntegerForKey("playerLevel", player_level);
}

int GAMEDATA::getPlayerLevel(){
	return playerLevel;
}

void GAMEDATA::setMagneticLevel(int magnetic_level){
	magneticLevel = magnetic_level;
	UserDefault::getInstance()->setIntegerForKey("magneticLevel", magnetic_level);
}

int GAMEDATA::getMagneticLevel(){
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
	CCLog("magneticLevel = %d", magneticLevel);
#endif
	return magneticLevel;
}

std::string GAMEDATA::getShowMagneticTime(){
	float mt = getMagneticTime();
	if (mt - (int)mt == 0){
		return String::createWithFormat("%d", (int)mt)->_string;
	}
	else{
		return String::createWithFormat("%d", (int)mt)->_string + ":5";
	}
}

void GAMEDATA::setSuperLevel(int super_level){
	superLevel = super_level;
	UserDefault::getInstance()->setIntegerForKey("superLevel", super_level);
}

int GAMEDATA::getSuperLevel(){
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
	CCLog("superLevel = %d", superLevel);
#endif
	return superLevel;
}

std::string GAMEDATA::getShowSuperTime(){
	float st = getSuperTime();
	if (st - (int)st == 0){
		return String::createWithFormat("%d", (int)st)->_string;
	}
	else{
		return String::createWithFormat("%d", (int)st)->_string + ":5";
	}
}


void GAMEDATA::setPotentialLevel(int potential_level){
	potentialLevel = potential_level;
	UserDefault::getInstance()->setIntegerForKey("potentialLevel", potential_level);
}

int GAMEDATA::getPotentialLevel(){
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_ANDROID)
	CCLog("potentialLevel = %d", potentialLevel);
#endif
	return potentialLevel;
}

std::string GAMEDATA::getShowPotentialTime(){
	float gt = getPotentialTime();
	if (gt - (int)gt == 0){
		return String::createWithFormat("%d", (int)gt)->_string;
	}
	else{
		return String::createWithFormat("%d", (int)gt)->_string + ":5";
	}
}


float GAMEDATA::getMagneticTime(){
	return 5 + (magneticLevel - 1)*0.5;
}

float GAMEDATA::getSuperTime(){
	return 4 + (superLevel - 1)*0.5;
}

float GAMEDATA::getPotentialTime(){
	return 3 + (potentialLevel - 1)*0.5;
}

int GAMEDATA::getDodgeMonsterNums(){
	return dodgeMonsterNums;
}

void GAMEDATA::setDodgeMonsterNums(int dodge_monster_num){
	dodgeMonsterNums = dodge_monster_num;
}

int GAMEDATA::getDistance(){
	return distance;
}

void GAMEDATA::setDistance(int m_distance){
	distance = m_distance;
}

int GAMEDATA::getEatGoldNum(){
	return eatGoldNum;
}

void GAMEDATA::setEatGlodNum(int eat_gold_num){
	eatGoldNum = eat_gold_num;
}

int GAMEDATA::getHistoryScore(){
	return historyScore;
}

void GAMEDATA::setHistoryScore(int history_score){
	historyScore = history_score;
	UserDefault::getInstance()->setIntegerForKey("historyScore", history_score);
}

int GAMEDATA::getPotentialIndex(){
	return potentialIndex;
}

void GAMEDATA::setPotentialIndex(int potential_index){
	potentialIndex = potential_index;
}

int GAMEDATA::getCurrentMissionNum(){
	static const int missions[29][2] =
	{
		{ 0, 1 },
		{ 1, 20 },
		{ 2, 20 },
		{ 3, 1000 },
		{ 4, 2 },
		{ 5, 1 },
		{ 6, 20 },
		{ 7, 10000 },
		{ 8, 1 },
		{ 9, 2 },
		{ 10, 3 },
		{ 11, 30 },
		{ 12, 30 },
		{ 13, 2000 },
		{ 14, 2000 },
		{ 15, 200 },
		{ 16, 2 },
		{ 17, 200 },
		{ 18, 50000 },
		{ 19, 30 },
		{ 20, 3000 },
		{ 21, 3 },
		{ 22, 6 },
		{ 23, 4 },
		{ 24, 500 },
		{ 25, 5000 },
		{ 26, 1000 },
		{ 27, 5000 },
		{ 28, 100000 }
	};
	return missions[playerLevel][1];
}

int GAMEDATA::getLastMissionNum(){
	if (playerLevel == 0){
		return 1;
	}
	static const int missions[29][2] =
	{
		{ 0, 1 },
		{ 1, 20 },
		{ 2, 20 },
		{ 3, 1000 },
		{ 4, 2 },
		{ 5, 1 },
		{ 6, 20 },
		{ 7, 10000 },
		{ 8, 1 },
		{ 9, 2 },
		{ 10, 3 },
		{ 11, 30 },
		{ 12, 30 },
		{ 13, 2000 },
		{ 14, 2000 },
		{ 15, 200 },
		{ 16, 2 },
		{ 17, 200 },
		{ 18, 50000 },
		{ 19, 30 },
		{ 20, 3000 },
		{ 21, 3 },
		{ 22, 6 },
		{ 23, 4 },
		{ 24, 500 },
		{ 25, 5000 },
		{ 26, 1000 },
		{ 27, 5000 },
		{ 28, 100000 }
	};
	return missions[playerLevel - 1][1];
}

void GAMEDATA::setSoundState(bool state) {
	UserDefault::getInstance()->setBoolForKey("soundState", state);
}

bool GAMEDATA::getSoundState() {
	return UserDefault::getInstance()->getBoolForKey("soundState", true);
}

void GAMEDATA::setMusicState(bool state) {
	UserDefault::getInstance()->setBoolForKey("musicState", state);
}

bool GAMEDATA::getMusicState() {
	return UserDefault::getInstance()->getBoolForKey("musicState", true);
}

bool GAMEDATA::isPaySuccess(){
	return UserDefault::getInstance()->getBoolForKey("paySuccess", false);
}

void GAMEDATA::setPaySuccess(bool paySuccess){
	UserDefault::getInstance()->setBoolForKey("paySuccess", paySuccess);
}

bool GAMEDATA::isFirstLogin(){
	return firstLognin;
}

void GAMEDATA::setFirstLogin(bool first_login){
	firstLognin = first_login;
	UserDefault::getInstance()->setBoolForKey("firstLognin", first_login);
}

int GAMEDATA::getPlayRounds(){
	return playRounds;
}

void GAMEDATA::setPlayRounds(int play_rounds){
	playRounds = play_rounds;
	UserDefault::getInstance()->setIntegerForKey("playRounds", play_rounds);
}

int GAMEDATA::getCostGoldNums(){
	return costGoldNums;
}

void GAMEDATA::setCostGoldNums(int cost_gold_nums){
	costGoldNums = cost_gold_nums;
	UserDefault::getInstance()->setIntegerForKey("costGoldNums", cost_gold_nums);
}

int GAMEDATA::getActiveGoldNum(){
	return activeGoldNum;
}
void GAMEDATA::setActiveGoldNum(int active_gold_num){
	activeGoldNum = active_gold_num;
}

int GAMEDATA::getHasFinishedNum(){
	return hasFinishedNum;
}

void GAMEDATA::setHasFinishedNum(int has_finished_num){
	hasFinishedNum = has_finished_num;
}

int GAMEDATA::getJumpTimes(){
	return jumpTimes;
}

void GAMEDATA::setJumpTimes(int jump_times){
	jumpTimes = jump_times;
}

int GAMEDATA::getSlideTimes(){
	return slideTimes;
}

void GAMEDATA::setSlideTimes(int slide_times){
	slideTimes = slide_times;
}

int GAMEDATA::getEatPotentialPropNums(){
	return eatPotentialPropNums;
}

void GAMEDATA::setEatPotentialPropNums(int eat_potential_prop_nums){
	eatPotentialPropNums = eat_potential_prop_nums;
}

int GAMEDATA::getEatSuperPropNums(){
	return eatSuperPropNums;
}

void GAMEDATA::setEatSuperPropNums(int eat_super_prop_nums){
	eatSuperPropNums = eat_super_prop_nums;
}

int GAMEDATA::getEatMagneticPropNums(){
	return eatMagneticPrpNums;
}

void GAMEDATA::setEatMagneticPropNums(int eat_magnetic_prop_nums){
	eatMagneticPrpNums = eat_magnetic_prop_nums;
}

int GAMEDATA::getActivePotentialTimes(){
	return activePotentialTimes;
}

void GAMEDATA::setActivePotentialTimes(int active_potential_times){
	activePotentialTimes = active_potential_times;
}

int GAMEDATA::getPropPotentialTimes(){
	return propPotentialTimes;
}

void GAMEDATA::setPropPotentialTimes(int prop_potential_times){
	propPotentialTimes = prop_potential_times;
}

int GAMEDATA::getEatGoldByMagneticNums(){
	return eatGoldByMagneticNums;
}

void GAMEDATA::setEatGoldByMagneticNums(int eat_gold_by_magnetic_nums){
	eatGoldByMagneticNums = eat_gold_by_magnetic_nums;
}

int GAMEDATA::getDistanceByPotential(){
	return distanceByPotential;
}

void GAMEDATA::setDistanceByPotential(int distance_by_potential){
	distanceByPotential = distance_by_potential;
}

int GAMEDATA::getDistanceBySuper(){
	return distanceBySuper;
}

void GAMEDATA::setDistanceBySuper(int distance_by_super){
	distanceBySuper = distance_by_super;
}

int GAMEDATA::getReviveNum(){
	return UserDefault::getInstance()->getIntegerForKey("reviveNum", 0);
}

void GAMEDATA::setReviveNum(int reveive_num){
	UserDefault::getInstance()->setIntegerForKey("reviveNum", reveive_num);
}

bool GAMEDATA::isHasPaySignIn(){
	return UserDefault::getInstance()->getBoolForKey("hasPaySignIn", false);
}

void GAMEDATA::setHasPaySignIn(bool has_pay_signin){
	UserDefault::getInstance()->setBoolForKey("hasPaySignIn", has_pay_signin);
}

int GAMEDATA::getMagneticPropNum(){
	return UserDefault::getInstance()->getIntegerForKey("magneticPropNum", 0);
}

void GAMEDATA::setMagneticPropNum(int magneticPropNum){
	UserDefault::getInstance()->setIntegerForKey("magneticPropNum", magneticPropNum);
}

int GAMEDATA::getSuperPropNum(){
	return UserDefault::getInstance()->getIntegerForKey("superPropNum", 1);
}

void GAMEDATA::setSuperPropNum(int superPropNum){
	UserDefault::getInstance()->setIntegerForKey("superPropNum", superPropNum);
}

int GAMEDATA::getPotentialPropNum(){
	return UserDefault::getInstance()->getIntegerForKey("potentialPropNum", 0);
}

void GAMEDATA::setPotentialPropNum(int potentialPropNum){
	UserDefault::getInstance()->setIntegerForKey("potentialPropNum", potentialPropNum);
}

bool GAMEDATA::isFirstEatPotentialProp(){
	return UserDefault::getInstance()->getBoolForKey("firstEatPotentialPropNum", true);
}

void GAMEDATA::setFirstEatPotentialProp(bool firstEatPotentialProp){
	UserDefault::getInstance()->setBoolForKey("firstEatPotentialPropNum", firstEatPotentialProp);
}

bool GAMEDATA::isHasShowPlayerUpgradePay(){
	return UserDefault::getInstance()->getBoolForKey("hasShowPlayerUpgradePay", false);
}

void GAMEDATA::setHasShowPlayerUpgradePay(bool hasShowPlayerUpgradePay){
	UserDefault::getInstance()->setBoolForKey("hasShowPlayerUpgradePay", hasShowPlayerUpgradePay);
}

bool GAMEDATA::getHasShowSignInPay(){
	return hasShowSignInPay;
}

void GAMEDATA::setHasShowSignInPay(bool has_show_signin_pay){
	hasShowSignInPay = has_show_signin_pay;
}

int GAMEDATA::getMagneticUpgradeGold(){
	static const int magneticGold[10][2] =
	{
		{ 0, 500 },
		{ 1, 800 },
		{ 2, 1000 },
		{ 3, 1500 },
		{ 4, 2000 },
		{ 5, 3000 },
		{ 6, 4000 },
		{ 7, 5000 },
		{ 8, 6000 },
		{ 9, 8000 }
	};
	if (magneticLevel > 10 || magneticLevel < 0){
		return 0;
	}
	return magneticGold[magneticLevel - 1][1];
}

int GAMEDATA::getSuperUpgradeGold(){
	static const int superGold[10][2] =
	{
		{ 0, 500 },
		{ 1, 800 },
		{ 2, 1000 },
		{ 3, 1500 },
		{ 4, 2000 },
		{ 5, 3000 },
		{ 6, 4000 },
		{ 7, 5000 },
		{ 8, 6000 },
		{ 9, 8000 }
	};
	if (superLevel>10 || superLevel < 0){
		return 0;
	}
	return superGold[superLevel - 1][1];
}

int GAMEDATA::getPotentialUpgradeGold(){
	static const int potentialGold[10][2] =
	{
		{ 0, 500 },
		{ 1, 800 },
		{ 2, 1000 },
		{ 3, 1500 },
		{ 4, 2000 },
		{ 5, 3000 },
		{ 6, 4000 },
		{ 7, 5000 },
		{ 8, 6000 },
		{ 9, 8000 }
	};
	if (potentialLevel>10 || potentialLevel < 0){
		return 0;
	}
	return potentialGold[potentialLevel - 1][1];
}

bool GAMEDATA::isSuperSelect(){
	return  UserDefault::getInstance()->getBoolForKey("isSuperSelect", true);
}
void GAMEDATA::setSuperSelect(bool select){
	UserDefault::getInstance()->setBoolForKey("isSuperSelect", select);
}

bool GAMEDATA::isMagneticSelect(){
	return  UserDefault::getInstance()->getBoolForKey("isMagneticSelect", false);
}
void GAMEDATA::setMagneticSelect(bool select){
	return  UserDefault::getInstance()->setBoolForKey("isMagneticSelect", select);
}

bool GAMEDATA::isPotentialSelect(){
	return  UserDefault::getInstance()->getBoolForKey("isPotentialSelect", false);
}
void GAMEDATA::setPotentialSelect(bool select){
	return  UserDefault::getInstance()->setBoolForKey("isPotentialSelect", select);
}


int GAMEDATA::getUsePropType(){
		return use_prop_type;
}

void GAMEDATA::setUsePropType(int type){
	use_prop_type = type;
}
