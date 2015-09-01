#pragma once
#include "cocos2d.h"
USING_NS_CC;
class SignInPrize :public Layer
{
public:
	bool init();
	CREATE_FUNC(SignInPrize);
	void hideSelf();
	Sprite* icon;
};
