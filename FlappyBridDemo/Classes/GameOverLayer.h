#pragma once
#include "cocos2d.h"
#include "GameScene.h"
#include "GameStartLayer.h"
#include "Brid.h"
using namespace cocos2d;


class GameOver :public Layer {

public:
	static Scene * createScene();
	virtual bool init();
	void addBackgroundSprite();
	void addTitleSprite();
	void addBridAimation();
	void showCurrcertSorceSprite();
	void sendCurrcertSorce();
	void showHistorySorceSprite();
	void sendHistorySorce();
	void showCuccertGoldsNumberSprite();
	void sendCuccertGoldsNumber();
	CREATE_FUNC(GameOver);
	void upadte(float dt);
public:
	void showBackButton();
	void backButtonCallBack();
	void showRestartButton();
	void reStartButtonCallBack();
private:
	Size visibleSize;
	Vec2 origin;

};