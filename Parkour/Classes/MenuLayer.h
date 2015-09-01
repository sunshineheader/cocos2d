#ifndef _MENULAYER_H_
#define _MENULAYER_H_

#include "cocos2d.h"
#include "GAMEDATA.h"
#include "QuitLayer.h"
#include "SignIn.h"
#include "BackgroundLayer.h"
#include "SignInPrize.h"

using namespace cocos2d;

class MenuLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(MenuLayer);
	void startGame();
	bool upgradeSuper(Touch* touch,Event* event);
	bool upgradeMagnetic(Touch* touch,Event* event);
	bool upgradePotential(Touch* touch,Event* event);
	void getSoudState(CCObject* pSender);
	void getMusicState(CCObject* pSender);
	void showQuit();
	void showMoreGame();
	void update(float dt);
	void chcekPropUse();
	static bool needShowMoreGame;
	static bool canStartGame;
	static bool showSignInPrize;
	static bool passPropCheck;
	void showLightAnim(Sprite* sprite);
	void goToGameScene();
private:
	SignIn* signIn;
	Menu* moreGameMenu;
	BackgroundLayer* m_backgroundLayer;
	SignInPrize* signInPrize;
	Sprite* superIcon;
	Sprite* magneticIcon;
	Sprite* potentialIcon;
	Sprite* prop_select_icon;
	bool isShowSuper;
	bool isShowMagnetic;
	bool isShowPotential;
};
#endif
