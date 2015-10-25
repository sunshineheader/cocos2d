#pragma once
#include "cocos2d.h"
using namespace cocos2d;


class GamePauseLayer :public Layer {

public:
	virtual bool init();
	CREATE_FUNC(GamePauseLayer);
	void update(float dt);
	void addBackgroundSprite();
	void addContuineGameButton();
	void ContuineGameCallBack();
	void addBackGameButton();
	void BackGameCallBack();
	void removeAndRemuse();
private:
	Size visibleSize;
	Vec2 origin;
};