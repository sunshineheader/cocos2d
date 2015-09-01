#ifndef _SIGNIN_H_
#define _SIGNIN_H_
#include <string>
#include "cocos2d.h"
#include "FloatWord.h"
using namespace cocos2d;
class SignIn : public Node{
public:
	static SignIn* getInstance();
	virtual bool init();
	CREATE_FUNC(SignIn);
	void hideSelf();
	void getSoudState(CCObject* pSender);
	void getMusicState(CCObject* pSender);
	void showAbout();
	void pay();
	void hideAbout();
	void startGameT();
	void setAboutVisible(bool visible);

private:
	static SignIn* _instance;
	Node* aboutLayer;
	int signDay;
	int prizeGoldNum;
	Node* gold;
private:
	SignIn();
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
