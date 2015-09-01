#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer : public cocos2d::Layer
{
public:
	BackgroundLayer();
	~BackgroundLayer();
    CREATE_FUNC(BackgroundLayer);
    virtual bool init();
	void logic(float dt);
	float speed;
	void setBackGroudSpeed(float speed);
private:
	Sprite* m_bg1;
	Sprite* m_bg2;
	Sprite* createBorder(Point pos);
};

#endif 
