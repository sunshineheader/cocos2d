#pragma once
#include "cocos2d.h"
USING_NS_CC;
class BankRaiseLayer :public Layer
{
public:
	bool init();
	CREATE_FUNC(BankRaiseLayer);
	void update(float dt);
	void refreshInfo();
private:
	float animeTime;
	bool hasGetChild;
	Sprite* upBg;
	Sprite* downBg;
	LabelAtlas* upNum;
	LabelAtlas* downNum;
};