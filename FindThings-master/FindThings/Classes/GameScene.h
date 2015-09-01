#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_
#include "cocos2d.h"
using namespace cocos2d;
class GameScene : public Scene{
public:
	virtual bool init();
	CREATE_FUNC(GameScene);

};
#endif