#ifndef GameOverScene_H_H
#define GameOverScene_H_H
#include "cocos2d.h"
#include "GameOverLayer.h"
class GameOverScene :public cocos2d::Scene {

public:
	virtual bool init();
	CREATE_FUNC(GameOverScene);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

};
#endif