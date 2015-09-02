#include "OrientedRect.h"

#include <cmath>

USING_NS_CC;

OrientedRect::OrientedRect()
{
}

OrientedRect::OrientedRect(const Vec2 &bottomLeft, const Vec2 &bottomRight,
	const Vec2 &topRight, const Vec2 &topLeft)
{
	set(bottomLeft, bottomRight, topRight, topLeft);
}

OrientedRect::OrientedRect(const cocos2d::Rect &rect)
{
	set(rect);
}

OrientedRect::~OrientedRect()
{
}

void OrientedRect::set(const Vec2 &bottomLeft, const Vec2 &bottomRight,
	const Vec2 &topRight, const Vec2 &topLeft)
{
	_center = (bottomLeft + topRight) / 2;
	_axisX = bottomRight - bottomLeft;
	_axisY = topLeft - bottomLeft;
	_halfWidth = _axisX.length() / 2;
	_halfHeight = _axisY.length() / 2;
	_axisX.normalize();
	_axisY.normalize();
}

void OrientedRect::set(const cocos2d::Rect &rect)
{
	const Vec2 &origin = rect.origin;
	const Size &size = rect.size;
	set(Vec2(origin.x, origin.y),
		Vec2(origin.x + size.width, origin.y),
		Vec2(origin.x + size.width, origin.y + size.height),
		Vec2(origin.x, origin.y + size.height));
}

bool OrientedRect::overlaps(const OrientedRect &other) const
{
	Vec2 centerDistance(_center - other.getCenter());
	Vec2 axes[4] = {
		_axisX, _axisY, other.getAxisX(), other.getAxisY()
	};

	for (int i = 0; i < 4; ++i)
	{
		float sum = getProjectionRadius(axes[i]) + other.getProjectionRadius(axes[i]);
		float dot = absDot(centerDistance, axes[i]);
		if (sum <= dot)
			return false;
	}

	return true;
}

const Vec2& OrientedRect::getCenter() const
{
	return _center;
}

const Vec2& OrientedRect::getAxisX() const
{
	return _axisX;
}

const Vec2& OrientedRect::getAxisY() const
{
	return _axisY;
}

float OrientedRect::getWidth() const
{
	return _halfWidth * 2;
}

float OrientedRect::getHeight() const
{
	return _halfHeight * 2;
}

float OrientedRect::getProjectionRadius(const cocos2d::Vec2 &axis) const
{
	float projectionAxisX = absDot(axis, _axisX);
	float projectionAxisY = absDot(axis, _axisY);

	return _halfWidth * projectionAxisX + _halfHeight * projectionAxisX;
}

float OrientedRect::absDot(const cocos2d::Vec2 &axisA, const cocos2d::Vec2 &axisB) const
{
	return fabs(axisA.dot(axisB));
}