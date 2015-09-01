#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class GameLayer : public Layer{

public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void loadGameView();
	void update(float dt);
};
#endif
