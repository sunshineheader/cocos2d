#ifndef _CALLANDROIDMETHOD_H_
#define _CALLANDROIDMETHOD_H_

#include "cocos2d.h"

using namespace cocos2d;

class CallAndroidMethod{
public:
	void Java_org_cocos2dx_cpp_PayService_callback();
	static CallAndroidMethod* getInstance();
	//TODO添加方法
	void eventToPay(int eventPoint);//触发支付的事件
private:
	CallAndroidMethod();
	static CallAndroidMethod* _instance;
};
#endif
