#pragma once

#include "cocos2d.h"

class GameData{

public:
	~GameData();
	static GameData*getInstance();
	static void destoryInstance();
public:
	inline void setBallSpeed(int speed){ ballSpeed = speed; };
	inline int  getBallSpeed(){ return ballSpeed; };
	inline void setGoldsNumber(int golds){ goldsNumber = golds; };
	inline int  getGoldsNumber(){ return goldsNumber; };
	inline void setCurrcertSorce(int sorce){ currcertSorce = sorce; };
	inline int  getCurrcertSorce(){ return currcertSorce; };
private:
	GameData();
	static GameData * m_instance;
private:
	int ballSpeed;
	int goldsNumber;
	int currcertSorce;
};