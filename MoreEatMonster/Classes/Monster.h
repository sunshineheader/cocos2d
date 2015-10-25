#pragma once

#include "cocos2d.h"

class Monnster :public cocos2d::Node {

public:
	enum  MonsterState
	{
		Open = 0,
		Close
	};
public:
	virtual bool init();
	CREATE_FUNC(Monnster);
	void addMonsterAmination();
	void stopMonsterAmination();
	void remuseMonsterAmination();
	void update(float dt);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *runSprite;
	cocos2d::RepeatForever*runAnimate;
};