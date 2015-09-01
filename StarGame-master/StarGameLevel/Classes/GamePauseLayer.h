#ifndef _GAMEPAUSELAYER_H_
#define _GAMEPAUSELAYER_H_
#include "cocos2d.h"
#include "TopMenu.h"
using namespace cocos2d;
class TopMenu;
class GamePauseLayer : public Layer{
public:
	static GamePauseLayer* create(TopMenu* topNode);
	virtual bool init(TopMenu* topNode);
	void payProps();
	void ResumeGame();
	void goBack();
	void getSoudState(CCObject* pSender);
	void getMusicState(CCObject* pSender);
};

#endif // !_GAMEPAUSELAYER_H_
