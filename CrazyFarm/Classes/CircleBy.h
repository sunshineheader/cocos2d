#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include "cocos2d.h"
using namespace cocos2d;

class CircleBy : public ActionInterval{
public:
	static CircleBy* create(Point curPos,float duration, float degrees,float speed, bool clockwise);
	bool initWithDuration(Point curPos, float duration, float degrees, float speed, bool clockwise);
	virtual void update(float dt);
private:
	Point currentPostion;//当前target的坐标
	float degree;//单次转动弧度
	float speed;//移动速度
	int updateTimes;//刷新次数
	bool clockWise;
};
#endif