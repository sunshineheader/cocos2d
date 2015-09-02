#include "Intersector.h"
#include "Circle.h"
#include "Segment.h"
#include "MathUtils.h"

#include <cmath>
#include <algorithm>
#include <limits>

USING_NS_CC;
using namespace std;

bool Intersector::isPointInTriangle(const Vec2 &p, 
	const Vec2 &a, const Vec2 &b, const Vec2 &c)
{
	return isPointInTriangle(p.x, p.y, a.x, a.y, b.x, b.y, c.x, c.y);
}

bool Intersector::isPointInTriangle(float px, float py,
	float ax, float ay, float bx, float by, float cx, float cy)
{
	float px1 = px - ax;
	float py1 = py - ay;
	bool side12 = (bx - ax) * py1 - (by - ay) * px1 > 0;
	if ((cx - ax) * py1 - (cy - ay) * px1 > 0 == side12) return false;
	if ((cx - bx) * (py - by) - (cy - by) * (px - bx) > 0 != side12) return false;

	return true;
}

bool Intersector::isPointInCircle(const Vec2 &p, const Vec2 &center, float radius)
{
	return isPointInCircle(p.x, p.y, center.x, center.y, radius);
}

bool Intersector::isPointInCircle(float px, float py, float centerX, float centerY, float radius)
{
	float x = centerX - px;
	float y = centerY - py;

	return x * x + y * y <= radius * radius;
}

bool Intersector::intersectSegmentPolygon(const Vec2 &p1, const Vec2 &p2, const ValueVector &vertices)
{
	float x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
	float width12 = x1 - x2, height12 = y1 - y2;
	float det1 = x1 * y2 - y1 * x2;
	ValueMap p3 = vertices[vertices.size() - 1].asValueMap();
	float x3 = p3["x"].asInt();
	float y3 = p3["y"].asInt();
	for (size_t i = 0; i < vertices.size(); ++i) {
		ValueMap p4 = vertices[i].asValueMap();
		float x4 = p4["x"].asInt();
		float y4 = p4["y"].asInt();
		float det2 = x3 * y4 - y3 * x4;
		float width34 = x3 - x4, height34 = y3 - y4;
		float det3 = width12 * height34 - height12 * width34;
		float x = (det1 * width34 - width12 * det2) / det3;
		if (((x >= x3 && x <= x4) || (x >= x4 && x <= x3)) && ((x >= x1 && x <= x2) || (x >= x2 && x <= x1))) {
			float y = (det1 * height34 - height12 * det2) / det3;
			if (((y >= y3 && y <= y4) || (y >= y4 && y <= y3)) && ((y >= y1 && y <= y2) || (y >= y2 && y <= y1))) return true;
		}
		x3 = x4;
		y3 = y4;
	}

	return false;
}

bool Intersector::intersectSegmentPolygon(const Vec2 &p1, const Vec2 &p2, Math::Polygon &polygon)
{
	auto vertices = polygon.getTransformedVertices();
	float x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
	float width12 = x1 - x2, height12 = y1 - y2;
	float det1 = x1 * y2 - y1 * x2;
	int n = vertices.size();
	float x3 = vertices[n - 2], y3 = vertices[n - 1];
	for (int i = 0; i < n; i += 2) {
		float x4 = vertices[i], y4 = vertices[i + 1];
		float det2 = x3 * y4 - y3 * x4;
		float width34 = x3 - x4, height34 = y3 - y4;
		float det3 = width12 * height34 - height12 * width34;
		float x = (det1 * width34 - width12 * det2) / det3;
		if (((x >= x3 && x <= x4) || (x >= x4 && x <= x3)) && ((x >= x1 && x <= x2) || (x >= x2 && x <= x1))) {
			float y = (det1 * height34 - height12 * det2) / det3;
			if (((y >= y3 && y <= y4) || (y >= y4 && y <= y3)) && ((y >= y1 && y <= y2) || (y >= y2 && y <= y1))) return true;
		}
		x3 = x4;
		y3 = y4;
	}
	return false;
}

bool Intersector::intersectRectCircle(const Rect &rect, const Circle &circle)
{
	Vec2 c(rect.getMidX(), rect.getMidY());
	Vec2 h(rect.size.width / 2, rect.size.height / 2);
	Vec2 p(circle.origin);
	Vec2 v(fabs(p.x - c.x), fabs(p.y - c.y));
	Vec2 u(max((v.x - h.x), 0.0f), max((v.y - h.y), 0.0f));

	return u.lengthSquared() <= circle.radius * circle.radius;
}

bool Intersector::intersectSegmentCircle(const Segment &segment, const Circle &circle)
{
	const Vec2 &start = segment.start;
	const Vec2 &end = segment.end;
	const Vec2 &center = circle.origin;
	const float squareRadius = circle.radius * circle.radius;

	Vec2 tmp(end.x - start.x, end.y - start.y);
	Vec2 tmp1(center.x - start.x, center.y - start.y);
	Vec2 tmp2;
	Vec2 tmp3;

	float l = tmp.length();
	tmp.normalize();
	float u = tmp1.dot(tmp);
	if (u <= 0)
	{
		tmp2.setPoint(start.x, start.y);
	}
	else if (u >= l)
	{
		tmp2.set(end.x, end.y);
	}
	else
	{
		tmp.scale(u);
		tmp3.setPoint(tmp.x, tmp.y);
		tmp2.setPoint(tmp3.x + start.x, tmp3.y + start.y);
	}

	float x = center.x - tmp2.x;
	float y = center.y - tmp2.y;

	return x * x + y * y <= squareRadius;
}

bool Intersector::intersectSegments(const Segment &segment1, const Segment &segment2)
{
	return intersectSegments(segment1.start, segment1.end, segment2.start, segment2.end);
}

bool Intersector::intersectSegments(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Vec2 &p4)
{

	return ( max(p1.x, p2.x) >= min(p3.x, p4.x)
		&& max(p3.x, p4.x) >= min(p1.x, p2.x)
		&& max(p1.y, p2.y) >= min(p3.y, p4.y)
		&& max(p3.y, p4.y) >= min(p1.y, p2.y)
		&& MathUtils::pointLineSide(p1, p3, p4) * MathUtils::pointLineSide(p2, p3, p4) <= 0
		&& MathUtils::pointLineSide(p3, p1, p2) * MathUtils::pointLineSide(p4, p1, p2) <= 0 );
}


bool Intersector::overlapConvexPolygons(Math::Polygon &p1, Math::Polygon &p2, MinimumTranslationVector *mtv)
{
	return overlapConvexPolygons(p1.getTransformedVertices(), p2.getTransformedVertices(), mtv);
}

bool Intersector::overlapConvexPolygons(const std::vector<float> &verts1, const std::vector<float> &verts2, MinimumTranslationVector *mtv)
{
	return overlapConvexPolygons(verts1, 0, verts1.size(), verts2, 0, verts2.size(), mtv);
}

bool Intersector::overlapConvexPolygons(const std::vector<float> &verts1, int offset1, int count1,
	const std::vector<float> &verts2, int offset2, int count2, MinimumTranslationVector *mtv)
{
	float overlap = FLT_MAX;
	float smallestAxisX = 0;
	float smallestAxisY = 0;

	int end1 = offset1 + count1;
	int end2 = offset2 + count2;

	// Get polygon1 axes
	for (int i = offset1; i < end1; i += 2) {
		float x1 = verts1[i];
		float y1 = verts1[i + 1];
		float x2 = verts1[(i + 2) % count1];
		float y2 = verts1[(i + 3) % count1];

		float axisX = y1 - y2;
		float axisY = -(x1 - x2);

		const float length = (float)sqrt(axisX * axisX + axisY * axisY);
		axisX /= length;
		axisY /= length;

		// -- Begin check for separation on this axis --//

		// Project polygon1 onto this axis
		float min1 = axisX * verts1[0] + axisY * verts1[1];
		float max1 = min1;
		for (int j = offset1; j < end1; j += 2) {
			float p = axisX * verts1[j] + axisY * verts1[j + 1];
			if (p < min1) {
				min1 = p;
			}
			else if (p > max1) {
				max1 = p;
			}
		}

		// Project polygon2 onto this axis
		float min2 = axisX * verts2[0] + axisY * verts2[1];
		float max2 = min2;
		for (int j = offset2; j < end2; j += 2) {
			float p = axisX * verts2[j] + axisY * verts2[j + 1];
			if (p < min2) {
				min2 = p;
			}
			else if (p > max2) {
				max2 = p;
			}
		}

		if (!(min1 <= min2 && max1 >= min2 || min2 <= min1 && max2 >= min1)) {
			return false;
		}
		else {
			float o = min(max1, max2) - max(min1, min2);
			if (min1 < min2 && max1 > max2 || min2 < min1 && max2 > max1) {
				float mins = abs(min1 - min2);
				float maxs = abs(max1 - max2);
				if (mins < maxs) {
					axisX = -axisX;
					axisY = -axisY;
					o += mins;
				}
				else {
					o += maxs;
				}
			}
			if (o < overlap) {
				overlap = o;
				smallestAxisX = axisX;
				smallestAxisY = axisY;
			}
		}
		// -- End check for separation on this axis --//
	}

	// Get polygon2 axes
	for (int i = offset2; i < end2; i += 2) {
		float x1 = verts2[i];
		float y1 = verts2[i + 1];
		float x2 = verts2[(i + 2) % count2];
		float y2 = verts2[(i + 3) % count2];

		float axisX = y1 - y2;
		float axisY = -(x1 - x2);

		const float length = (float)sqrt(axisX * axisX + axisY * axisY);
		axisX /= length;
		axisY /= length;

		// -- Begin check for separation on this axis --//

		// Project polygon1 onto this axis
		float min1 = axisX * verts1[0] + axisY * verts1[1];
		float max1 = min1;
		for (int j = offset1; j < end1; j += 2) {
			float p = axisX * verts1[j] + axisY * verts1[j + 1];
			if (p < min1) {
				min1 = p;
			}
			else if (p > max1) {
				max1 = p;
			}
		}

		// Project polygon2 onto this axis
		float min2 = axisX * verts2[0] + axisY * verts2[1];
		float max2 = min2;
		for (int j = offset2; j < end2; j += 2) {
			float p = axisX * verts2[j] + axisY * verts2[j + 1];
			if (p < min2) {
				min2 = p;
			}
			else if (p > max2) {
				max2 = p;
			}
		}

		if (!(min1 <= min2 && max1 >= min2 || min2 <= min1 && max2 >= min1)) {
			return false;
		}
		else {
			float o = min(max1, max2) - max(min1, min2);

			if (min1 < min2 && max1 > max2 || min2 < min1 && max2 > max1) {
				float mins = abs(min1 - min2);
				float maxs = abs(max1 - max2);
				if (mins < maxs) {
					axisX = -axisX;
					axisY = -axisY;
					o += mins;
				}
				else {
					o += maxs;
				}
			}

			if (o < overlap) {
				overlap = o;
				smallestAxisX = axisX;
				smallestAxisY = axisY;
			}
		}
		// -- End check for separation on this axis --//
	}

	if (mtv != nullptr)
	{
		mtv->normal.set(smallestAxisX, smallestAxisY);
		mtv->depth = overlap;
	}

	return true;
}