#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Brid :public Node {

public:
	static Brid *create();
	virtual bool init();
public:
	void initBridAmination();
	void stopBridAmination();
	void update(float dt); 
public:
	void setPhysicsConfiger();
	void setBridContentSize();
private:
	RepeatForever * runAnimate;
	Sprite *runSprite;
	Size visibleSize;
	Vec2 origin;

};