#ifndef GameScrollView_H_H
#define GameScrollView_H_H
#include "cocos2d.h"
USING_NS_CC;
class GameScrollView : public Layer
{

public:
	static Scene * createScene();
	virtual bool init();
	CREATE_FUNC(GameScrollView);
};
#endif