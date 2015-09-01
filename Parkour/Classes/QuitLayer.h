#pragma once
#include "cocos2d.h"
USING_NS_CC;
class QuitLayer :public Layer
{
public:
	bool init();
	CREATE_FUNC(QuitLayer);
	void cancel();
	void quit();
};