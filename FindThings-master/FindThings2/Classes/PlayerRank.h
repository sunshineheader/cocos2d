#ifndef _PLAYERRANK_H_
#define _PLAYERRANK_H_
#include "cocos2d.h"


class PLAYERRANK{
public:
	static PLAYERRANK* getInstance();
	int getRankPer(int score);
	int getRankList(int score);
	const static int LEVEL_0 = 30;
	const static int LEVEL_1 = 60;
	const static int LEVEL_2 = 90;
	const static int LEVEL_3 = 120;
	const static int LEVEL_4 = 150;
	const static int LEVEL_5 = 200;
	const static int LEVEL_6 = 250;
	const static int LEVEL_7 = 300;
private:
	PLAYERRANK();
private:
	static PLAYERRANK* _instance;
};


#endif
