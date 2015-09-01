#ifndef _GAMERESULTLAYER_H_
#define _GAMERESULTLAYER_H_

#include "cocos2d.h"
#include "ResultGold.h"
#include "BankRaiseLayer.h"
#include "Def.h"

using namespace cocos2d;

class GameResultLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameResultLayer);

	void contiGame();
	void back();
	bool upgradeSuper(Touch* touch,Event* event);
	bool upgradeMagnetic(Touch* touch,Event* event);
	bool upgradePotential(Touch* touch,Event* event);
	void update(float dt);
	void showLightAnim(Sprite* sprite);
	void chcekPropUse();
	void goToGameScene();
	static bool clickedStartGame;
	static bool clickedBack;
	static bool canClick;
private:
	float animTime;
	BankRaiseLayer* bankRaiseLayer;
	Sprite* mission;
	LabelAtlas* gameScore;
	LabelAtlas* rankNum;
	int totalGameScore;
	float gameScoreNum;
	bool hasStartRankAnim;
	bool hasStartMissionAnim;
	bool hasShowPay;
	Sprite* superIcon;
	Sprite* magneticIcon;
	Sprite* potentialIcon;
	bool isShowSuper;
	bool isShowMagnetic;
	bool isShowPotential;
	Sprite* prop_select_icon;
};
#endif
