#ifndef _CALLANDROIDMETHOD_H_
#define _CALLANDROIDMETHOD_H_

#include "cocos2d.h"

using namespace cocos2d;

class CallAndroidMethod{
public:
	void Java_org_cocos2dx_cpp_PayService_callback();
	void showMoreGame();
	void pay(int payPoint);
	void startNativeNotify();
	bool isSignToday();
	bool notSignToday();
	int getCurrentSignDayas();
	void sign();
	void markPersonInfo(const char tag1,const char tag2);
	static CallAndroidMethod* getInstance();
private:
	CallAndroidMethod();
	static CallAndroidMethod* _instance;
};
#endif
