#ifndef _GAMEPAUSELAYER_H_
#define _GAMEPAUSELAYER_H_
#include "cocos2d.h"
using namespace cocos2d;
class TopMenu;
class GamePauseLayer : public Layer{
public:
	static GamePauseLayer* create();
	virtual bool init();
	void payProps();
	void ResumeGame();
	void goBack();
	void getSoudState(CCObject* pSender);
	void getMusicState(CCObject* pSender);
};

#endif 
