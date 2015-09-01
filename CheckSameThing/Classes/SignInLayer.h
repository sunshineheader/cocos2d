#ifndef __SIGNINLAYER_H__
#define __SIGNINLAYER_H__
#include "cocos2d.h"

USING_NS_CC;


class SignInLayer : public Node
{
public:
	void update(float dt);
	static SignInLayer* getInstance();
	static cocos2d::Scene* createScene();
	virtual bool init();

	void geteveryGift();
	bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void hideSelf();

	CREATE_FUNC(SignInLayer);

private:
	SignInLayer();
	int signDay;
	int refresh;
	int tip;
	int time;
	
	static SignInLayer* _instance;
};
#endif