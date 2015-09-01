#ifndef _LEVELMSGLAYER_H_
#define _LEVELMSGLAYER_H_
#include "cocos2d.h"
using namespace cocos2d;
class LevelMsgLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(LevelMsgLayer);
private:
	//virtual void update(float delta);
};
#endif