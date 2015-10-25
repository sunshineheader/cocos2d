#ifndef GameShopLayer_H_
#define GameShopLayer_H_
#include "cocos2d.h"
#include "cocos-ext.h"
class GameShopLayer :public cocos2d::Layer{

public:
	virtual bool  init();
	CREATE_FUNC(GameShopLayer);
	void addBackgroundSprite();
	void addCloseButton();
	void closeButtonCallback();
	void addGoldNumber();
	void showGoldNumber();
	void addRectArea();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

};
#endif