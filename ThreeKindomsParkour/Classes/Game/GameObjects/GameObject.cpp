#include "GameObject.h"
#include "Game/GameMap.h"
using namespace cocos2d;

GameObject::GameObject()
: _isNeedRemove(false)
, _score(0)
, _gameMap(nullptr)
{
}

GameObject::~GameObject()
{
}

void GameObject::setTypeName(const std::string &typeName)
{
	_typeName = typeName;
}

std::string GameObject::getTypeName() const
{
	return _typeName;
}

void GameObject::setNeedRemove(bool isNeedRemove)
{
    _isNeedRemove = isNeedRemove;
}

bool GameObject::isNeedRemove() const
{
    return _isNeedRemove;
}

void GameObject::setScore(int score)
{
	_score = score;
}

int GameObject::getScore() const
{
	return _score;
}

void GameObject::setGameMap(GameMap *gameMap)
{
	_gameMap = gameMap;
}

GameMap* GameObject::getGameMap() const
{
	return _gameMap;
}

void GameObject::setAttackRegion(const std::vector<float> &vertices)
{
	_attackRegion.setVertices(vertices);
}

void GameObject::setDefenceRegion(const std::vector<float> &vertices)
{
	_defenceRegion.setVertices(vertices);
}

Math::Polygon& GameObject::getAttackRegion()
{
	_attackRegion.setScale(getScale());
	return _attackRegion;
}

Math::Polygon& GameObject::getDefenceRegion()
{
	_defenceRegion.setScale(getScale());
	return _defenceRegion;
}

void GameObject::die()
{
	runAction(Sequence::createWithTwoActions(ScaleTo::create(0.25f, 0.0f),
		Hide::create()));

	_gameMap->addDustAnimation(this);

	setNeedRemove(true);
}