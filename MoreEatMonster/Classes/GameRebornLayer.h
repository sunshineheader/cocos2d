#ifndef GameRebornLayer_H_H
#define GameRebornLayer_H_H
#include "cocos2d.h"
class GameRebornLayer :public cocos2d::Layer{

public:
	virtual bool  init();
	CREATE_FUNC(GameRebornLayer);
	void addBackgroundSprite();
	void addTextSprite();
	void addSureButton();
	void sureButtonCallback();
	void addRebornGoldNumber();
	void showRebornGoldNumber();
	void addProgressBar();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

};
#endif