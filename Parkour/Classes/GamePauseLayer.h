#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GamePauseLayer :public Layer
{
public:
	bool init();
	CREATE_FUNC(GamePauseLayer);
	void contiGame();
	void backMenu();
};