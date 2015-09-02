#ifndef __INTERSECTOR_H__
#define __INTERSECTOR_H__

#include "cocos2d.h"
#include "Polygon.h"
#include <vector>

class Circle;
class Segment;

struct MinimumTranslationVector 
{
	cocos2d::Vec2 normal;
	float depth = 0;
};

class Intersector
{
public:
	static bool isPointInTriangle(const cocos2d::Vec2 &p, 
		const cocos2d::Vec2 &a, const cocos2d::Vec2 &b, const cocos2d::Vec2 &c);

	static bool isPointInTriangle(float px, float py,
		float ax, float ay, float bx, float by, float cx, float cy);

	static bool isPointInCircle(const cocos2d::Vec2 &p,
		const cocos2d::Vec2 &center, float radius);

	static bool isPointInCircle(float px, float py,
		float centerX, float centerY, float radius);

	static bool intersectSegmentPolygon(const cocos2d::Vec2 &p1, const cocos2d::Vec2 &p2,
		const cocos2d::ValueVector &vertices);

	static bool intersectSegmentPolygon(const cocos2d::Vec2 &p1, const cocos2d::Vec2 &p2,
		Math::Polygon &polygon);

	static bool intersectRectCircle(const cocos2d::Rect &rect, const Circle &circle);

	static bool intersectSegmentCircle(const Segment &segment, const Circle &circle);

	static bool intersectSegments(const Segment &segment1, const Segment &segment2);

	static bool intersectSegments(const cocos2d::Vec2 &p1, const cocos2d::Vec2 &p2, 
		const cocos2d::Vec2 &p3, const cocos2d::Vec2 &p4);


	static bool overlapConvexPolygons(Math::Polygon &p1, Math::Polygon &p2, MinimumTranslationVector *mtv = nullptr);

	static bool overlapConvexPolygons(const std::vector<float> &verts1, const std::vector<float> &verts2, MinimumTranslationVector *mtv = nullptr);

	static bool overlapConvexPolygons(const std::vector<float> &verts1, int offset1, int count1,
		const std::vector<float> &verts2, int offset2, int count2, MinimumTranslationVector *mtv = nullptr);




	CC_DISALLOW_IMPLICIT_CONSTRUCTORS(Intersector);
};

#endif // __INTERSECTOR_H__