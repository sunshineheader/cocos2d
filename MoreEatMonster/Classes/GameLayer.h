#ifndef GameLayer_H
#define GameLayer_H

#include "cocos2d.h"
#include "GameScene.h"
#include "GamePauseLayer.h"
#include "Ball.h"
#include "Monster.h"
#include "Border.h"
#include "GameData.h"
#include "GameOverScene.h"

class GameLayer :public cocos2d::Layer  {

public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void addBackgroundSprite();
	void addPauseGameButton();
	void pauseGameCallback();
	void showCurrcertSorceSprite();
	void showCurrcertSorceNumber();
	void genBall();
	void genMonster();
	void genBorder();
	void genCheckBorder();
	void update(float dt);
	bool onTouchBegan(cocos2d::Touch * touch,cocos2d::Event * event);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	Border * border;
	//Monnster * monsterNode ;
	Ball * ball;
	float ratation;
	cocos2d::Sprite*monsterSpriteUp;
	cocos2d::Sprite*monsterSptiteDown;
	cocos2d::Sprite*checkSprite;
public:
	void updateSorce();
	void updateSpeed();
private:
	int currcertSorce;
	cocos2d::LabelAtlas * CurrcertSorce;
	int currcertSpeed;
	
};
#endif