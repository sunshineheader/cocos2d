#ifndef _PLAYERRANK_H_
#define _PLAYERRANK_H_
#include "cocos2d.h"


class PLAYERRANK{
public:
	static PLAYERRANK* getInstance();
	int getRankPer(int score);
	int getRankList(int score);
	const static int LEVEL_0 = 0;
	const static int LEVEL_1 = 800;
	const static int LEVEL_2 = 1500;
	const static int LEVEL_3 = 3000;
	const static int LEVEL_4 = 6000;
	const static int LEVEL_5 = 10000;
	const static int LEVEL_6 = 16000;
	const static int LEVEL_7 = 24000;
private:
	PLAYERRANK();
private:
	static PLAYERRANK* _instance;
};


#endif
