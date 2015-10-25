#pragma once
#include "cocos2d.h"
#include "Brid.h"
#include "Ball.h"
#include "Pipline.h"
#include "GameOverLayer.h"
#include "GameData.h"
#include "GamePauseLayer.h"
#include "GameAudio.h"
using namespace cocos2d;

const int bridTag = 1;
const int ballTag = 2;
const int piplineTag = 3;
const int broderTag = 4;
class GameLayer :public Layer {

public:
	virtual bool init();
	void addWithPhysics();
	void addBackgroundSprite();
	void showGoldSprite();
	void showGoldNumber();
	void addUIButton();
	void pauseGameCallBack();
	void pauseGane();
	void addBridWithAmination();
	void addBall();
	void addPiplineUp();
	void addPiplineDown();
	void addcheckBorder();
	void doGameOver();
	void doVisit();
	void updateSorce(float time);
	virtual bool onContactBegin(PhysicsContact& contact);
	virtual bool onTouchBegan(Touch * touch,Event * event);
	CREATE_FUNC(GameLayer);
	void update(float dt);
private:
	Brid * brid;
	LabelAtlas * gold;
	Sprite * checkBorder;
private:
	Size visibleSize;
	Vec2 origin;
	//float myTimer;
	int sorce;
};