#include "Segment.h"


Segment::Segment()
{
	setSegment(0, 0, 0, 0);
}

Segment::~Segment()
{
}

Segment::Segment(float startX, float startY, float endX, float endY)
{
	setSegment(startX, startY, endX, endY);
}

Segment::Segment(const cocos2d::Vec2 &start, const cocos2d::Vec2 &end)
{
	setSegment(start, end);
}

Segment::Segment(const Segment &other)
{
	setSegment(other);
}

Segment& Segment::operator= (const Segment &other)
{
	setSegment(other);
	return *this;
}

void Segment::setSegment(float startX, float startY, float endX, float endY)
{
	start.setPoint(startX, startY);
	end.setPoint(endX, endY);
}

void Segment::setSegment(const cocos2d::Vec2 &start, const cocos2d::Vec2 &end)
{
	setSegment(start.x, start.y, end.x, end.y);
}

void Segment::setSegment(const Segment &other)
{
	setSegment(other.start, other.end);
}
