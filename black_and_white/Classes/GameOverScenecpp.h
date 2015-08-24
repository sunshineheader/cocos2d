#ifndef GameOverScene_H
#define GameOverScene_H
#include "cocos2d.h"

class GameOver :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameOver);
private:
	
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};


#endif