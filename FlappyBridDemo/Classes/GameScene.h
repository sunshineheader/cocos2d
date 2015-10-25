#pragma once
#include "cocos2d.h"
#include "GameLayer.h"
using namespace cocos2d;

class GameScene :public Scene {

public:
	virtual bool init();
	CREATE_FUNC(GameScene);

};