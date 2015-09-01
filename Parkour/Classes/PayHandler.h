#ifndef _PAY_HANDLER_H_
#define _PAY_HANDLER_H_
#include "cocos2d.h"

class PayHandler
{       
public:
	PayHandler() {};
	~PayHandler() {};  
	void payCallback(int requestId,int resultId);
	void moreGameCallback(bool openMoreGame);
	bool isNeedFly();
	void setNeedFly(bool need_fly);
	static PayHandler* getInstance();
	static bool needSuper;
	static bool needMagnetic;
	static bool needFly;
	static bool revivaled;
};
#endif

