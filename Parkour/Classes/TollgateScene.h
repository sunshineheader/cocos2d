#ifndef __TOLLGATE_SCENE_H__
#define __TOLLGATE_SCENE_H__

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "Player.h"
#include "MonsterLayer.h"
#include "InfoLayer.h"
#include "GamePauseLayer.h"
#include "extensions\cocos-ext.h"

using namespace ui;
using namespace extension;

USING_NS_CC;

class TollgateScene : public cocos2d::Layer
{
public:
   ~TollgateScene();
    static Scene* scene();
    CREATE_FUNC(TollgateScene);
    virtual bool init();
    virtual void onExit() override;
	void jump(Ref *pSender, Widget::TouchEventType type);
	void slide(Ref *pSender, Widget::TouchEventType type);
	void pauseGame();
	void showFinishMission();
	void payPauseGame();
	void showPlayerDownGuide();
	void showPlayerUpGuide();
	static bool needSlide;
	static bool isSliding;
	static bool showRevivePay;
	static bool finishedMission;
	static float speed;
	static float level;
	static bool payPause;
private:
	BackgroundLayer* m_backgroundLayer;
	Player* m_player;
	MonsterLayer* m_monsterLayer;
	InfoLayer* m_infoLayer;
	GamePauseLayer* m_gamePauseLayer;
	//PropInfo* propInfo;
	Sprite* finishMissionBg;
	Sprite* finishMission;

	EventListenerPhysicsContact* contactListener;
	void logic(float dt);
	void toResultScene();
	int distance;
	int checkDistance;
	int distanceBySuper;
	int distanceByPotential;
	Size visibleSize;
	int totalDistance;
	bool pausedGame;
	bool hasShowPay;
	float finishedTime;
	bool hasToResultScene;
	bool isUseProp;
	bool isShowEvent18;
	bool isShowDownGuide;
	bool isShowUpGuide;
};

#endif 
