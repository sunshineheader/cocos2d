#ifndef _GAMEOVERSCENE_H_
#define _GAMEOVERSCENE_H_
#include "cocos2d.h"
using namespace cocos2d;
class GameOverScene : public Scene{
public:
	virtual bool init();
	CREATE_FUNC(GameOverScene);
};
#endif