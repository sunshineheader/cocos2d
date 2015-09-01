#ifndef _MENU_SCENE_PAY_HANDLER_H_
#define _MENU_SCENE_PAY_HANDLER_H_
#include "cocos2d.h"

class MenuScenePayHandler
{       
public:
	MenuScenePayHandler() {};
	~MenuScenePayHandler() {};  
	void dealEventSuccess(int eventId, int propIds[], int propNums[], int count);
	void dealEventFail(int eventId);
	void dealRewardProp(int propId, int propNum);//处理支付获得道具
	void dealEventClose(int eventId);
	static MenuScenePayHandler* getInstance();

private:
	void doPayEvent1(int result);
	void doPayEvent2(int result);
	void doPayEvent3(int result);
};
#endif

