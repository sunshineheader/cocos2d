#ifndef __SOG_ORIENTED_RECT_H__
#define __SOG_ORIENTED_RECT_H__

#include "cocos2d.h"

class OrientedRect
{
public:
	OrientedRect();
	OrientedRect(const cocos2d::Vec2 &bottomLeft, const cocos2d::Vec2 &bottomRight,
		         const cocos2d::Vec2 &topRight, const cocos2d::Vec2 &topLeft);
	OrientedRect(const cocos2d::Rect &rect);
	~OrientedRect();

	void set(const cocos2d::Vec2 &bottomLeft, const cocos2d::Vec2 &bottomRight,
		     const cocos2d::Vec2 &topRight, const cocos2d::Vec2 &topLeft);

	void set(const cocos2d::Rect &rect);

	bool overlaps(const OrientedRect &other) const;

	const cocos2d::Vec2& getCenter() const;
	const cocos2d::Vec2& getAxisX() const;
	const cocos2d::Vec2& getAxisY() const;
	float getWidth() const;
	float getHeight() const;

private:
	float getProjectionRadius(const cocos2d::Vec2 &axis) const;
	float absDot(const cocos2d::Vec2 &axisA, const cocos2d::Vec2 &axisB) const;

private:
	cocos2d::Vec2 _center;
	cocos2d::Vec2 _axisX;
	cocos2d::Vec2 _axisY;
	float _halfWidth;
	float _halfHeight;
};

#endif // __SOG_ORIENTED_RECT_H__