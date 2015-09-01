#ifndef __GAME_RESULT_SCENE__
#define __GAME_RESULT_SCENE__

#include "cocos2d.h"
USING_NS_CC;

class GamePauseScene : public cocos2d::Scene{
public:
	virtual bool init();
	CREATE_FUNC(GamePauseScene);
};

#endif