#ifndef GamePauseLayer_H_H
#define GamePauseLayer_H_H
#include "cocos2d.h"
#include "GameStartScene.h"
using namespace cocos2d;

class GamePause :public Layer {

public:
	virtual bool init();
	CREATE_FUNC(GamePause);
	void contiueGameSprite();
	void contiueGameCallback();
	void restartGameSprite();
	void restartGameCallback();
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

};
#endif