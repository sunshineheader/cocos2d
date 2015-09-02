#ifndef __TKP_PLATFORM_H__
#define __TKP_PLATFORM_H__

#include "cocos2d.h"

#include "Math/Polygon.h"


class Platform : public cocos2d::Node
{
public:
	static Platform* create(cocos2d::Node *node);

	bool hasCollisionRegionX() const;
	bool hasCollisionRegionDownY() const;
	bool hasCollisionRegionUpY() const;
	bool hasJumpRegion() const;

	Math::Polygon& getCollisionRegionX();
	Math::Polygon& getCollisionRegionDownY();
	Math::Polygon& getCollisionRegionUpY();
	const cocos2d::Rect& getJumpRegion() const;

	void setJumpOpen(bool isJumpOpen);
	bool isJumpOpen() const;

protected:
	Platform();
	virtual ~Platform();
	CC_DISALLOW_COPY_AND_ASSIGN(Platform);

	virtual bool init(cocos2d::Node *node);

private:
	Math::Polygon _collisionRegionX;
	Math::Polygon _collisionRegionDownY;
	Math::Polygon _collisionRegionUpY;
	cocos2d::Rect _jumpRegion;

	bool _hasCollisionRegionX;
	bool _hasCollisionRegionDownY;
	bool _hasCollisionRegionUpY;
	bool _hasJumpRegion;

	bool _isJumpOpen;
};



#endif // __TKP_PLATFORM_H__