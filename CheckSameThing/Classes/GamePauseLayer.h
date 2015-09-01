#ifndef __GAME_PAUSE_LAYER_H__
#define __GAME_PAUSE_LAYER_H__
#include "cocos2d.h"
USING_NS_CC;

class GamePauseLayer: public cocos2d::Layer{
public:
	static GamePauseLayer* create();
	virtual bool init();

private :
	void resumeGame();
	void delayTen();
	void getGift();
	void goBack();
	void getdaoju();
	void scene(CCRenderTexture* sqr);
	bool  onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
};
#endif