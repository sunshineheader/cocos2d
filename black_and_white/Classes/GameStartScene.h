#ifndef GameStartScene_H
#define GameSrartScene_H
#include "cocos2d.h"


class GameStart :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void game_layer_scene_callback(cocos2d::Ref* psneder);
	CREATE_FUNC(GameStart);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};


#endif