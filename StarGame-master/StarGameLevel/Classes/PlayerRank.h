#ifndef _PLAYERRANK_H_
#define _PLAYERRANK_H_
#include "cocos2d.h"


class PLAYERRANK{
public:
	static PLAYERRANK* getInstance();
	int getRankPer(int score);
	int getRankList(int score);
	const static int LEVEL_0 = 0;
	const static int LEVEL_1 = 500;
	const static int LEVEL_2 = 1000;
	const static int LEVEL_3 = 4000;
	const static int LEVEL_4 = 8000;
	const static int LEVEL_5 = 16000;
	const static int LEVEL_6 = 32000;
	const static int LEVEL_7 = 128000;
private:
	PLAYERRANK();
private:
	static PLAYERRANK* _instance;
};


#endif
