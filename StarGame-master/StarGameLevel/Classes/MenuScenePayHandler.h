#ifndef _MENU_SCENE_PAY_HANDLER_H_
#define _MENU_SCENE_PAY_HANDLER_H_
#include "cocos2d.h"

class MenuScenePayHandler
{       
public:
	MenuScenePayHandler() {};
	~MenuScenePayHandler() {};  
	void payCallback(int requestId,int resultId);
	static MenuScenePayHandler* getInstance();
};
#endif

