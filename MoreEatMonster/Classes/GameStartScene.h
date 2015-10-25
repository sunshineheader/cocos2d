#ifndef GameStartScene_H_H
#define GameStartScene_H_H
#include "cocos2d.h"
#include "GameStartLayer.h"
class GameStartScene :public cocos2d::Scene {

public:
	virtual bool init();
	CREATE_FUNC(GameStartScene);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

};
#endif