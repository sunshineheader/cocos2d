#ifndef __GAME_GUI_LAYER_H__
#define __GAME_GUI_LAYER_H__
#include "cocos2d.h"
USING_NS_CC;

class GameGuiLayer: public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameGuiLayer);
	//static const int Map_1[];
private :
	void pauseGame();
	void initTime();
	void update(float dt);
	void gotoResult();
	float passTime;
	 
};
#endif