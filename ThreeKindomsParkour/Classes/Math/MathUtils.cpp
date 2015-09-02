#include "MathUtils.h"
#include <cmath>
#include <vector>

USING_NS_CC;
using namespace std;

const float MathUtils::kNanoToSec = 1 / 1000000000.0f;

const float kFloatRoundingError = 0.000001f;
const float MathUtils::kPI = 3.1415927f;
const float MathUtils::kPI2 = MathUtils::kPI * 2;

const float MathUtils::kE = 2.7182818f;

const float MathUtils::kRadiansToDegrees = 180.0f / MathUtils::kPI;
const float MathUtils::kDegreesToRadians = MathUtils::kPI / 180.0f;

const int MathUtils::kSinBits = 14;
const int MathUtils::kSinMask = ~(-1 << MathUtils::kSinBits);
const int MathUtils::kSinCount = MathUtils::kSinMask + 1;

const float MathUtils::kRadFull = MathUtils::kPI * 2;
const float MathUtils::kDegFull = 360;
const float MathUtils::kRadToIndex = MathUtils::kSinCount / MathUtils::kRadFull;
const float MathUtils::kDegToIndex = MathUtils::kSinCount / MathUtils::kDegFull;


float MathUtils::sin(float radians)
{
	return getSinTable()[(int)(radians * kRadToIndex) & kSinMask];
}

float MathUtils::cos(float radians)
{
	return getSinTable()[(int)((radians + kPI / 2) * kRadToIndex) & kSinMask];
}

float MathUtils::sinDeg(float degrees)
{
	return getSinTable()[(int)(degrees * kDegToIndex) & kSinMask];
}

float MathUtils::cosDeg(float degrees)
{
	return getSinTable()[(int)((degrees + 90) * kDegToIndex) & kSinMask];
}

const float* MathUtils::getSinTable()
{
	static float sinTable[kSinCount];
	static bool isInit = false;

	if (!isInit)
	{
		isInit = true;
		for (int i = 0; i < kSinCount; ++i)
			sinTable[i] = sin((i + 0.5f) / kSinCount * kRadFull);
		for (int i = 0; i < 360; i += 90)
			sinTable[(int)(i * kDegToIndex) & kSinMask] = sin(i * kDegreesToRadians);
	}

	return sinTable;
}


float MathUtils::crossProduct(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Vec2 &p4)
{
	return (p2.x - p1.x) * (p4.y - p3.y) - (p4.x - p3.x) * (p2.y - p1.y);
}

int MathUtils::pointLineSide(const Vec2 &point, const Vec2 &linePoint1, const Vec2 &linePoint2)
{
	float result = crossProduct(linePoint1, point, linePoint1, linePoint2);
	return fabs(result) < MATH_EPSILON ? 0 :
		result > 0 ? 1 : -1;
}

bool MathUtils::isSameSideWithSegment(const Vec2 &p1, const Vec2 &p2, const Segment &segment)
{
	int side1 = MathUtils::pointLineSide(p1, segment.start, segment.end);
	int side2 = MathUtils::pointLineSide(p2, segment.start, segment.end);
	return side1 == side2;
}

float MathUtils::includedAngle(const cocos2d::Vec2 &v1, const cocos2d::Vec2 &v2)
{
	float angle = Vec2::angle(v1, v2);
	return angle > kPI / 2 ? kPI - angle : angle;
}

float MathUtils::includedAngle(const cocos2d::Vec2 &v, const Segment &s)
{
	return includedAngle(v, s.end - s.start);
}

void MathUtils::rectToPolygon(const cocos2d::Rect &rect, Math::Polygon &polygon)
{
	vector<float> vertices;
	vertices.reserve(8);

	vertices.push_back(rect.origin.x);
	vertices.push_back(rect.origin.y);

	vertices.push_back(rect.origin.x + rect.size.width);
	vertices.push_back(rect.origin.y);

	vertices.push_back(rect.origin.x + rect.size.width);
	vertices.push_back(rect.origin.y + rect.size.height);

	vertices.push_back(rect.origin.x);
	vertices.push_back(rect.origin.y + rect.size.height);

	polygon.setVertices(vertices);
}