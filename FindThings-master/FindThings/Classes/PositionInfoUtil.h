#ifndef _POSITION_INFO_UTIL_H_
#define _POSITION_INFO_UTIL_H_
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;
class PositionInfoUtil{
public:
	static PositionInfoUtil* getInstance();
	Point* getPositionById(int id);
	std::map<int,Point*> getPositionList();
private:
	void init();
	PositionInfoUtil();
	~PositionInfoUtil();
private:
	static PositionInfoUtil* m_instance;
	std::map<int,Point*> posMap;
};
#endif