#ifndef __FISHMANAGE_H__
#define __FISHMANAGE_H__

#include "cocos2d.h"
#include "Fish.h"
using namespace cocos2d;

#define BORDER_LEFT 0
#define BORDER_TOP 1
#define BORDER_RIGHT 2
#define BORDER_BOTTOM 3

class FishManage {
public:
	static FishManage* getInstance();
	Fish* createFishSingle();
	Vector<Fish*> createFishGroup();
	void removeFish(Fish* fish);
	void decideFishPos(Fish* fish);//决定鱼的出生位置
	Vector<Fish*> getAllFishInPool();
private :
	FishManage();
	static FishManage* _instance;
	Vector<Fish*> fishPool;
 };
#endif