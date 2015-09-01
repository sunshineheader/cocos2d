#pragma once
#include "cocos2d.h"
#include "GAMEDATA.h"
USING_NS_CC;
class SignIn :public Layer
{
public:
	bool init();
	CREATE_FUNC(SignIn);
	void signIn();
	static int currentSignDay;
};
