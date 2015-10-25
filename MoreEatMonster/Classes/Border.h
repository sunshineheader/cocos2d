#pragma once

#include "cocos2d.h"

class Border :public cocos2d::Sprite{

public:
	enum BorderState
	{
		Horizontal = 0,
		Vertical
	};
public:
	virtual bool init();
	CREATE_FUNC(Border);
	void addBorder();
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

};
	
