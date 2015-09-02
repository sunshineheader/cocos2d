#ifndef __SOG_CIRCLE_H__
#define __SOG_CIRCLE_H__

#include "cocos2d.h"

class Circle
{
public:
	cocos2d::Vec2 origin;
	float radius;

public:
	Circle();
	Circle(float x, float y, float radius);
	~Circle();
	Circle(const Circle &other);
	Circle& operator= (const Circle &other);

	void setCircle(float x, float y, float radius);
	void setCircle(const Circle &other);
	bool containsPoint(float x, float y) const;
	bool containsPoint(const cocos2d::Vec2 &point) const;
	bool containsCircle(const Circle &other) const;
	bool overlapsCircle(const Circle &other) const;

};

#endif // __SOG_CIRCLE_H__