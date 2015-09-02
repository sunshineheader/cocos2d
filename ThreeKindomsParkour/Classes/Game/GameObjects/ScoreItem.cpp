#include "ScoreItem.h"

USING_NS_CC;

ScoreItem::ScoreItem()
: _isCollecting(false)
, _sprite(nullptr)
{
}

ScoreItem::~ScoreItem()
{
}

bool ScoreItem::init()
{
	setTypeName("ScoreItem_SmallCoin");

	return true;
}

void ScoreItem::setCollecting(bool isCollecting)
{
	_isCollecting = isCollecting;
}

bool ScoreItem::isCollecting() const
{
	return _isCollecting;
}

void ScoreItem::setSprite(cocos2d::Node *sprite)
{
	if (sprite == nullptr)
		return;

	_sprite = sprite;

	setPosition(sprite->getPosition());
	sprite->setPosition(Vec2::ZERO);
	sprite->removeFromParent();
	addChild(sprite);
}

cocos2d::Node* ScoreItem::getSprite() const
{
	return _sprite;
}