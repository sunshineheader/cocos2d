#ifndef __MATH_MATH_UTILS_H__
#define __MATH_MATH_UTILS_H__

#include "cocos2d.h"
#include "Segment.h"
#include "Polygon.h"

class MathUtils
{
public:
	static const float kNanoToSec;

	static const float kFloatRoundingError;
	static const float kPI;
	static const float kPI2;

	static const float kE;

	static const float kRadiansToDegrees;
	static const float kDegreesToRadians;

	static float sin(float radians);
	static float cos(float radians);
	static float sinDeg(float degrees);
	static float cosDeg(float degrees);

private:
	static const int kSinBits;
	static const int kSinMask;
	static const int kSinCount;

	static const float kRadFull;
	static const float kDegFull;
	static const float kRadToIndex;
	static const float kDegToIndex;

	static const float* getSinTable();

public:
	static float crossProduct(const cocos2d::Vec2 &p1, const cocos2d::Vec2 &p2,
		const cocos2d::Vec2 &p3, const cocos2d::Vec2 &p4);

	static int pointLineSide(const cocos2d::Vec2 &point,
		const cocos2d::Vec2 &linePoint1, const cocos2d::Vec2 &linePoint2);

	static bool isSameSideWithSegment(const cocos2d::Vec2 &p1, const cocos2d::Vec2 &p2,
		const Segment &segment);

	static float includedAngle(const cocos2d::Vec2 &v1, const cocos2d::Vec2 &v2);

	static float includedAngle(const cocos2d::Vec2 &v, const Segment &s);

	static void rectToPolygon(const cocos2d::Rect &rect, Math::Polygon &polygon);
};

#endif // __MATH_MATH_UTILS_H__