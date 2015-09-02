#ifndef __SOG_SEGMENT_H__
#define __SOG_SEGMENT_H__

#include "cocos2d.h"

class Segment
{
public:
	cocos2d::Vec2 start;
	cocos2d::Vec2 end;

	Segment();
	Segment(float startX, float startY, float endX, float endY);
	Segment(const cocos2d::Vec2 &start, const cocos2d::Vec2 &end);
	Segment(const Segment &other);
	Segment& operator= (const Segment &other);
	~Segment();

	void setSegment(float startX, float startY, float endX, float endY);
	void setSegment(const cocos2d::Vec2 &start, const cocos2d::Vec2 &end);
	void setSegment(const Segment &other);

};

#endif // __SOG_SEGMENT_H__