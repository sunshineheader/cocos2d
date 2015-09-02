#ifndef __GAME_RESULT_LAYER_H__
#define __GAME_RESULT_LAYER_H__
#include "cocos2d.h"
USING_NS_CC;

class GameResultLayer: public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameResultLayer);
private:
	void continueGame();
	void quitGame();
	void showMoreGame();
};
#endif