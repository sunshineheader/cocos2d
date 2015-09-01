#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

class GAMEDATA{
public:
	static GAMEDATA* getInstance();
	void setCurLevel(int level);
	inline int getCurLevel(){return cur_level;}
	inline int getNextLevel(){return next_level;}
	inline void setHistoryScore(int score){history_score = score;}
	inline int getHistoryScore(){return history_score;}
	inline void setCurScore(int score){cur_score = score;}
	inline int getCurScore(){return cur_score;}
	inline int getNextScore(){return next_score;}
	inline int getScoreByLevel(int level);
	inline void setGoldNum(int goldNum){gold_num = goldNum;}
	inline int getGoldNum(){return gold_num;}
	inline void setPowerStoneNum(int powerStoneNum){power_stone_num = powerStoneNum;}
	inline int getPowerStoneNum(){return power_stone_num;}
	inline void setUserLevel(int userLevel){user_level = userLevel;}
	inline int getUserLevel(){return user_level;}
	inline void setPrizeTimes(int prizeTimes){prize_times = prizeTimes;}
	inline int getPrizeTimes(){return prize_times;}

	inline void setAddTimeNum(int addTimeNum){add_time_num = addTimeNum;}
	inline int getAddTimeNum(){return add_time_num;}

	inline void setBombNum(int bombNum){bomb_num = bombNum;}
	inline int getBombNum(){return bomb_num;}

	inline void setChuiNum(int chuiNum){chui_num = chuiNum;}
	inline int getChuiNum(){return chui_num;}

	inline void setBiNum(int biNum){bi_num = biNum;}
	inline int getBiNum(){return bi_num;}

	inline void setReviveNum(int reviveNum){revive_num = reviveNum;}
	inline int getReviveNum(){return revive_num;}

	inline void setHasShowRegisterPay(bool showRegisterPay){show_register_pay = showRegisterPay;}
	inline bool hasShowRegisterPay(){return show_register_pay;}

	inline void setSoundEffect(bool soundeffect){sound_effect = soundeffect;}
	inline bool getSoundEffect(){return sound_effect;}

	inline void setMusicState(bool musicstate){music_state = musicstate;}
	inline bool getMusicState(){return music_state;}

	inline void setCurExpNum(int curExpNum){cur_exp_num = curExpNum;}
	inline int getCurExpNum(){return cur_exp_num;}	 

	inline void setPrizeGoldNum(int prizeGoldNum){prize_gold_num = prizeGoldNum;}
	inline int getPrizeGoldNum(){return prize_gold_num;}

	inline void setFirstLogin(bool firstLogin){first_login = firstLogin;}
	inline bool isFirstLogin(){return first_login;}

	inline void setTotalScore(int totalScore){total_score = totalScore;}
	inline int getTotalScore(){return total_score;}

	inline void setPaySuccess(bool paySuccess){pay_success = paySuccess;}
	inline bool isPaySuccess(){return pay_success;}

	int getJiangli(int size);

	int getFullExpNum(int userLevel);

	float getScoreAddPer(int userLevel);

	int getUpgradePrizeNum(int urserLevel);

	void saveHighestScore();
	void saveGoldNum();
	void savePowerStoneNum();
	void saveUserLevel();
	void savePrizeTimes();
	void saveAddTimeNum();
	void saveBombNum();
	void saveChuiNum();
	void saveBiNum();
	void saveReviveNum();
	void saveShowRegisterPay();
	void saveSoundEffect();
	void saveMusicState();
	void saveCurExpNum();
	void savePrizeGoldNum();
	void saveTotalScore();
	void savePaySuccess();

	int getIsBuySuperGift();
	void setIsBuySuperGift();

	void setLastLevelScore(int score);
	int getLastLevelScore();

private:
	GAMEDATA();
	void init();
private:
	static GAMEDATA* _instance;
	bool first_login;
	int cur_level;
	int next_level;
	int history_score;
	int cur_score;
	int next_score;
	int gold_num;
	int power_stone_num;
	int user_level;
	int prize_times;
	int add_time_num;
	int bomb_num;
	int chui_num;
	int bi_num;
	bool sound_effect;
	bool music_state;
	int revive_num;
	bool show_register_pay;
	int cur_exp_num;
	float score_add_per;
	int prize_gold_num;
	int total_score;
	bool pay_success;
	int lastLevelScore;
	friend class MenuLayer;
	friend class GameOverLayer;
	friend class SignIn;
};
#endif
