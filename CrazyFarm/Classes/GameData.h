#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include "cocos2d.h"

using namespace cocos2d;

class GAMEDATA{
public:
	static GAMEDATA* getInstance();

	void setSoundState(bool state);
	bool getSoundState();
	void setMusicState(bool state);
	bool getMusicState();

	int getLevel();
	void setLevel(int level);

	void setScore(int score);
	int  getScore();

	int  getReviveNum();//复活次数
	void  setReviveNum(int num);

	int  getLoginTimes();
	void setLoginTimes();

	int  getLastClikTime();
	void setLastClikTime(int clickTime);

	long getCurrentTime();

private:
	GAMEDATA();
	void init();
	static GAMEDATA* _instance;
	int score;//当前游戏分数
	int level;//关卡
	int lastClikTime;
};

#endif
