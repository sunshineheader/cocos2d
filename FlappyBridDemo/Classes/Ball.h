#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Ball :public Sprite {
	
public:
	enum BallState
	{
		Right = 0,
		Left
	};
public:
	virtual bool init();
	CREATE_FUNC(Ball);
	void setNextPosition();
	void setPhysicsConfiger();
	void update(float dt);
public:
	bool checkWidthBorder(float x);
	void setBallState();
	int  getBallState();
private:
	int state;
	Size visibleSize;
	Vec2 origin;

};