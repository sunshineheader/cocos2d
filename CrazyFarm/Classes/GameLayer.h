#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include "cocos2d.h"
#include "FishManage.h"
#include "BulletManage.h"
#include "Turret.h"

USING_NS_CC;

class GameLayer: public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
private:
	void createTurret(int type);//按照类型生成炮塔
	void addTouchEvent();
	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchMoved(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	//发射子弹
	void createFish(float dt);//产生鱼
	void shoot(float degree);//发射子弹
	float getTurretRotation(Point pos1,Point pos2);//获取炮塔需要旋转的角度
	void rotateTurret(float degree);//旋转炮塔
	void update(float dt);
	Turret* myTurret;
};
#endif