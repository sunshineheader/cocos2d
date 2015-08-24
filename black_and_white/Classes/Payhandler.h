#ifndef _MENU_SCENE_PAY_HANDLER_H_
#define _MENU_SCENE_PAY_HANDLER_H_
#include "cocos2d.h"

class PayHandler
{       
public:
	PayHandler() {};
	void payCallback(int requestId,int resultId);
	void moreGameCallback(bool openMoreGame);
	static PayHandler* getInstance();
};
#endif

