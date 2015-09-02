#include "QuickFlying.h"
#include "Game/GameMap.h"
#include "Game/GameObjects/ScoreItem.h"
#include "Game/ZhuGong.h"

#include <algorithm>

using namespace std;

USING_NS_CC;

QuickFlying* QuickFlying::create(GameMap *gameMap, ZhuGong *zhugong, 
	cocos2d::Node *carrier, float totalTime)
{
	QuickFlying *fly = new (std::nothrow) QuickFlying(gameMap, zhugong, carrier, totalTime);
	if (fly && fly->init())
	{
		fly->autorelease();
		return fly;
	}
	CC_SAFE_DELETE(fly);
	return nullptr;
}

QuickFlying::QuickFlying(GameMap *gameMap, ZhuGong *zhugong, cocos2d::Node *carrier, float totalTime)
: _zhugong(zhugong)
, _gameMap(gameMap)
, _carrier(carrier)
, _stateTime(0.0f)
, _totalTime(totalTime)
, _newGameMapMoveSpeed(0.0f)
{
	_oldGameMapMoveSpeed = gameMap->getMoveSpeed();
}

QuickFlying::~QuickFlying()
{
}

bool QuickFlying::init()
{
	if (_gameMap == nullptr || _zhugong == nullptr || _carrier == nullptr)
		return false;

	_carrier->setPosition(_zhugong->getPosition());

	_gameMap->addChildToEntityLayer(_carrier);
	_gameMap->setMoveSpeed(700);
	setNewGameMapMoveSpeed(700);
	_gameMap->addAutoCollectEffect(_totalTime);
	_carrier->runAction(MoveTo::create(1.0f, Vec2(_carrier->getPositionX(), 380.0f)));
	_zhugong->runAction(MoveTo::create(1.0f, Vec2(_zhugong->getPositionX(), 420)));

	_zhugong->setFlying(true);

	scheduleUpdate();

	return true;
}

void QuickFlying::update(float delta)
{
	float deltaDistance = _newGameMapMoveSpeed * delta;
	_carrier->setPositionX(_carrier->getPositionX() + deltaDistance);

	_stateTime += delta;
	if (_stateTime >= _totalTime)
	{
		_gameMap->setMoveSpeed(_oldGameMapMoveSpeed);
		_zhugong->setFlying(false);
		_carrier->removeFromParent();
		removeFromParent();
		return;
	}
}

void QuickFlying::setTotalTime(float time)
{
	_totalTime = time;
}

void QuickFlying::setNewGameMapMoveSpeed(float speed)
{
	_newGameMapMoveSpeed = speed;
}