#ifndef _GOLD_H_
#define _GOLD_H_
#include <string>
#include "cocos2d.h"
using namespace cocos2d;
class Gold : public Node{
public:
	static Gold* getInstance();
	virtual bool init();
	void refreshGold();
private:
	static Gold* _instance;
	LabelAtlas* playerGold;
private:
	Gold();

};
#endif
