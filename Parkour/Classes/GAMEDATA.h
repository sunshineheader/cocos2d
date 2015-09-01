#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

#include "cocos2d.h"

USING_NS_CC;

class GAMEDATA{
public:
	static GAMEDATA* getInstance();
	void setGameScore(int score);
	int getGameScore();

	void setGoldNum(int gold_num);
	int getGoldNum();

	void setPlayerLevel(int player_level);
	int getPlayerLevel();

	void setMagneticLevel(int magnetic_level);
	int getMagneticLevel();

	std::string getShowMagneticTime();

	int getMagneticUpgradeGold();

	void setSuperLevel(int super_level);
	int getSuperLevel();

	std::string getShowSuperTime();

	int getSuperUpgradeGold();

	void setPotentialLevel(int potential_level);
	int getPotentialLevel();

	std::string getShowPotentialTime();

	int getPotentialUpgradeGold();

	int getDodgeMonsterNums();
	void setDodgeMonsterNums(int dodge_monster_num);

	int getDistance();
	void setDistance(int m_distance);

	int getEatGoldNum();
	void setEatGlodNum(int eat_gold_num);

	int getHistoryScore();
	void setHistoryScore(int history_score);

	bool isPaySuccess();
	void setPaySuccess(bool paySuccess);

	int getPlayRounds();
	void setPlayRounds(int play_rounds);

	int getPotentialIndex();
	void setPotentialIndex(int potential_index);

	int getActiveGoldNum();
	void setActiveGoldNum(int active_gold_num);

	bool isFirstLogin();
	void setFirstLogin(bool first_login);

	void setSoundState(bool state);
	bool getSoundState();
	void setMusicState(bool state);
	bool getMusicState();

	float getMagneticTime();
	float getSuperTime();
	float getPotentialTime();

	int getCurrentMissionNum();
	int getLastMissionNum();

	int getHasFinishedNum();
	void setHasFinishedNum(int has_finished_num);

	int getJumpTimes();
	void setJumpTimes(int jump_times);

	int getSlideTimes();
	void setSlideTimes(int slide_times);

	int getEatPotentialPropNums();
	void setEatPotentialPropNums(int eat_potential_prop_nums);

	int getEatSuperPropNums();
	void setEatSuperPropNums(int eat_super_prop_nums);

	int getEatMagneticPropNums();
	void setEatMagneticPropNums(int eat_magnetic_prop_nums);

	int getActivePotentialTimes();
	void setActivePotentialTimes(int active_potential_times);

	int getPropPotentialTimes();
	void setPropPotentialTimes(int prop_potential_times);

	int getCostGoldNums();
	void setCostGoldNums(int cost_gold_nums);

	int getEatGoldByMagneticNums();
	void setEatGoldByMagneticNums(int eat_gold_by_magnetic_nums);

	int getDistanceByPotential();
	void setDistanceByPotential(int distance_by_potential);

	int getDistanceBySuper();
	void setDistanceBySuper(int distance_by_super);

	int getReviveNum();
	void setReviveNum(int reveive_num);

	bool isHasPaySignIn();
	void setHasPaySignIn(bool has_pay_signin);

	int getMagneticPropNum();
	void setMagneticPropNum(int magneticPropNum);

	int getSuperPropNum();
	void setSuperPropNum(int superPropNum);

	int getPotentialPropNum();
	void setPotentialPropNum(int potentialPropNum);

	bool getHasShowSignInPay();
	void setHasShowSignInPay(bool has_show_signin_pay);

	bool isFirstEatPotentialProp();
	void setFirstEatPotentialProp(bool firstEatPotentialProp);

	bool isHasShowPlayerUpgradePay();
	void setHasShowPlayerUpgradePay(bool hasShowPlayerUpgradePay);

	bool isSuperSelect();
	void setSuperSelect(bool select);

	bool isMagneticSelect();
	void setMagneticSelect(bool select);

	bool isPotentialSelect();
	void setPotentialSelect(bool select);

	int getUsePropType();
	void setUsePropType(int type);

	void reset();
private:
	GAMEDATA();
	void init();
	static GAMEDATA* _instance;
	int gameScore;
	bool firstLognin;
	int magneticLevel;
	int superLevel;
	int potentialLevel;
	int dodgeMonsterNums;
	int distance;
	int eatGoldNum;
	int historyScore;
	int potentialIndex;
	int activeGoldNum;
	int playerLevel;
	int playRounds;
	int jumpTimes;
	int slideTimes;
	int eatPotentialPropNums;
	int eatSuperPropNums;
	int eatMagneticPrpNums;
	int activePotentialTimes;
	int propPotentialTimes;
	int costGoldNums;
	int eatGoldByMagneticNums;
	int distanceBySuper;
	int distanceByPotential;
	int hasFinishedNum;
	bool hasShowSignInPay;
	bool super_select;
	bool magnetic_select;
	bool potential_select;
	int use_prop_type;
};
#endif
