#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include "cocos2d.h"

using namespace cocos2d;

class GAMEDATA{
public:
	static GAMEDATA* getInstance();
	inline void setPaySuccess(bool paySuccess){ pay_success = paySuccess; }
	inline bool isPaySuccess(){ return pay_success; }
	inline void setaddtimeNum(int addnum){ add_num = addnum; }
	inline int getaddtimeNum(){ return add_num; }
	inline void settipNum(int tipnum){ tip_num = tipnum; }
	inline int gettipNum(){ return tip_num; }
	inline void setrefreshNum(int renum){ re_num = renum; }
	inline int getrefreshNum(){ return re_num; }
	void savePaySuccess();
	void  saveaddtimeNum();
	void  savetipNum();
	void  saverefreshNum();
	void setSoundState(bool state);
	bool getSoundState();
	void setMusicState(bool state);
	bool getMusicState();
	int getLevel();
	void setLevel(int level);
	void setDay(int value);
	int getDay();
	void savaDay();
	void setScore(int score);
	int  getScore();
	void settime(float value);
	float gettime();
	int  getReviveNum();//复活次数
	void  setReviveNum(int num);
	void  saveReviveNum();
	void saveMusicState();
	int  getLoginTimes();
	void setLoginTimes(int value);
	void saveLoginTimes();
	void setstate(int value);
	int getstate();
	int  getLastClikTime();
	void setLastClikTime(int clickTime);


	
	float getAchievescore();
	void setAchievescore(float value);

	int getPercent();
	void setPercent(int value);

	int getcurrentTime();
	void setcurrentTime(int level);
	int getTimes();
	void setTimes(int value);
	long getCurrentTime();
	void init();

	bool needResetMap;
	bool needTipPos; 
	bool updateScore;
private:
	GAMEDATA();
	
	static GAMEDATA* _instance;
	bool first_login;
	int score;//当前游戏分数
	int level=0;//关卡
	int lastClikTime;
	float gametime;
	int gamestate;
	int add_num;
	int re_num;
	int tip_num;
	float Ascore;
	int  times;
	int percent;
	bool pay_success;
};

#endif
