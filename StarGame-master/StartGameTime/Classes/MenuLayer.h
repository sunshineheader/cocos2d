#ifndef _MENULAYER_H_
#define _MENULAYER_H_

#include "cocos2d.h"
#include "SignIn.h"
#include "BlinkTitle.h"

using namespace cocos2d;

class MenuLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(MenuLayer);
	bool startGame(Touch* touch,Event* event);
	void autoStartGame(float dt);
	void showAbout();
	void getSoudState(CCObject* pSender);
	void getMusicState(CCObject* pSender);
	void quit();
	void cancel();
	void showQuit();
	void setSignIn(bool signIn);
	void pay();
	void hideAbout();
	void startGameT();
	void setAboutVisible(bool visible);
private:
	Menu* menuBgMusic;
	Menu* menuSoundEffect;
	Sprite* quitBg;
	Sprite* quitDesc;
	Menu* confirmMenu;
	Menu* cancelMenu;
	SignIn* signIn;
	BlinkTitle* title;
	bool hasShowQuitPay;
	Node* gold;
	Sprite* aboutBg;
	Label* smallTitle11;
	Label* smallTitle12;
	Label* smallTitle21;
	Label* smallTitle22;
	Label* titleDesc1;
	Label* titleDesc2;
	Label* titleDesc3;
	Label* titleDesc4;
	Label* titleDesc5;
	Label* titleDesc6;
	Label* titleDesc7;
	Label* titleDesc8;
	Label* titleDesc9;
	Menu* backMenu;
	Menu* startMenu;
};
#endif
