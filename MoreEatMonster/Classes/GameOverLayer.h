#ifndef GameOverLayer_H_H
#define GameOverLayer_H_H
#include "cocos2d.h"
#include "GameData.h"
#include "GameStartScene.h"
#include "GameScene.h"
class GameOverLayer :public cocos2d::Layer {

public:
	virtual bool init();
	CREATE_FUNC(GameOverLayer);
	void addBackgroundSprite();
	void showNewHistory();
	void showNewHistoryNumber();
	void addHistorySorceShow();
	void showHistorySorceNumber();
	void showreturnGameButton();
	void retunGameButtonCallback();
	void showresatrtGameButton();
	void restartGameButtonCallback();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

};
#endif