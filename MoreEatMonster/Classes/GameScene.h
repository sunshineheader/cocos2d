#ifndef GameScene_H_H
#define GameScene_H_H
#include "cocos2d.h"
#include "GameLayer.h"
#include "GameShopLayer.h"
#include "GameRebornLayer.h"
class GameScene :public cocos2d::Scene {

public:
	virtual bool init();
	CREATE_FUNC(GameScene);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

};
#endif