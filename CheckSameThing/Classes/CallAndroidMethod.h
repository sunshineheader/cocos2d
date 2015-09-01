#ifndef _CALLANDROIDMETHOD_H_
#define _CALLANDROIDMETHOD_H_

#include "cocos2d.h"

using namespace cocos2d;

class CallAndroidMethod{
public:
	void showMoreGame();
	void startNativeNotify();
	bool isSignToday();
	bool notSignToday();
	int getCurrentSignDayas();
	void sign();
	void markPersonInfo(const char tag1,const char tag2);
	void quit();
	static CallAndroidMethod* getInstance();
	void requestEvent(int eventId);//请求处理此事件
	void pay(int payPoint);
	void dealEventCallBack(int requestId, bool isOpen, bool payResult, int propIds[], int propNums[], int count);
private:
	CallAndroidMethod();
	static CallAndroidMethod* _instance;
};
#endif
