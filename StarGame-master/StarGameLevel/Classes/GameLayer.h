#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include "cocos2d.h"
#include "FloatWord.h"
#include "TopMenu.h"
#include "StarMatrix.h"
#include "TopMenu.h"

using namespace cocos2d;
class StarMatrix;

class GameLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void floatLevelWord();
	void floatTargetScoreWord();
	void removeFloatWord();
	void showStarMatrix(float dt);
	virtual void update(float delta);
	virtual bool onTouchBegan(Touch* touch,Event* event);
	void refreshMenu(int score);
	void showLinkNum(int size);
	void showEveryScore(int size,int score,int index,Point point,bool leftType);
	void hideLinkNum();
	void floatLeftStarMsg(int leftNum);
	void gotoNextLevel();
	void gotoGameOver();
	void doRevive();
	void doGameOver();
	void loadGame(float dt);
	void showPay(float dt);
	void showMissionComplete();
	void removeMissonComplet();
	void hidePropInfos();
	void hideProps();
private:
	FloatWord* _levelMsg;
	FloatWord* _targetScore;
	TopMenu* menu;
	StarMatrix* matrix;
	Label* linkNum;
	FloatWord* gameOverWord;
	Sprite* missionComplete;
	bool needInitPause;
	bool hasShowMission;
public :
	static bool gameOver;
	static bool needRevive;
	static bool goToNextLevel;
	static bool isShowRePlay;
};
#endif
