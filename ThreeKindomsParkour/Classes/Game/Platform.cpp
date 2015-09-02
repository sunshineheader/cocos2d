#include "Platform.h"
#include "Math/MathUtils.h"

#include <string>

USING_NS_CC;
using namespace std;

Platform* Platform::create(cocos2d::Node *node)
{
	Platform *pf = new (std::nothrow) Platform;
	if (pf && pf->init(node))
	{
		pf->autorelease();
		return pf;
	}
	CC_SAFE_DELETE(pf);
	return nullptr;
}

Platform::Platform()
: _isJumpOpen(true)
, _hasJumpRegion(false)
, _hasCollisionRegionX(false)
, _hasCollisionRegionUpY(false)
, _hasCollisionRegionDownY(false)
{
}

Platform::~Platform()
{
}

static void initCollisionRegion(cocos2d::Node *node, const std::string &name, 
	Math::Polygon &region, bool &flag)
{
	auto panel = node->getChildByName(name);
	if (panel == nullptr)
		return;

	flag = true;

	auto rect = panel->getBoundingBox();
	MathUtils::rectToPolygon(rect, region);
}

bool Platform::init(cocos2d::Node *node)
{
	if (node == nullptr)
		return false;

	setPosition(node->getPosition());
	setContentSize(node->getContentSize());
	node->setPosition(Vec2::ZERO);

	node->removeFromParent();
	addChild(node);

	initCollisionRegion(node, "CollisionY_Down", _collisionRegionDownY, _hasCollisionRegionDownY);
	initCollisionRegion(node, "CollisionY_Up", _collisionRegionUpY, _hasCollisionRegionUpY);
	initCollisionRegion(node, "CollisionX", _collisionRegionX, _hasCollisionRegionX);
	
	auto jumpNode = node->getChildByName("JumpRegion");
	if (jumpNode != nullptr)
	{
		_jumpRegion = jumpNode->getBoundingBox();
		_hasJumpRegion = true;
	}

	return true;
}

Math::Polygon& Platform::getCollisionRegionX()
{
	return _collisionRegionX;
}

Math::Polygon& Platform::getCollisionRegionDownY()
{
	return _collisionRegionDownY;
}

Math::Polygon& Platform::getCollisionRegionUpY()
{
	return _collisionRegionUpY;
}

const cocos2d::Rect& Platform::getJumpRegion() const
{
	return _jumpRegion;
}

void Platform::setJumpOpen(bool isJumpOpen)
{
	_isJumpOpen = isJumpOpen;
}

bool Platform::isJumpOpen() const
{
	return _isJumpOpen;
}

bool Platform::hasCollisionRegionX() const
{
	return _hasCollisionRegionX;
}

bool Platform::hasCollisionRegionDownY() const
{
	return _hasCollisionRegionDownY;
}

bool Platform::hasCollisionRegionUpY() const
{
	return _hasCollisionRegionUpY;
}

bool Platform::hasJumpRegion() const
{
	return _hasJumpRegion;
}
