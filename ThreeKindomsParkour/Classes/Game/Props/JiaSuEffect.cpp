#include "JiaSuEffect.h"
#include "Game/GameMap.h"
#include "Game/GameObjects/ScoreItem.h"
#include "Game/ZhuGong.h"

USING_NS_CC;

JiaSuEffect::JiaSuEffect()
: _zhugong(nullptr)
, _gameMap(nullptr)
, _stateTime(0.0f)
, _totalTime(5.0f)
{
}

JiaSuEffect::~JiaSuEffect()
{
}

bool JiaSuEffect::init()
{
	scheduleUpdate();

	return true;
}

void JiaSuEffect::update(float delta)
{
	if (_gameMap == nullptr)
		return;

	_stateTime += delta;
	if (_stateTime >= _totalTime)
	{
		_gameMap->setMoveSpeed(_oldMoveSpeed);
		removeFromParent();
		return;
	}
}

void JiaSuEffect::setZhuGong(ZhuGong *zhugong)
{
	_zhugong = zhugong;
}

void JiaSuEffect::setGameMap(GameMap *gameMap)
{
	_gameMap = gameMap;
	_oldMoveSpeed = gameMap->getMoveSpeed();
	_gameMap->setMoveSpeed(_oldMoveSpeed * 1.5f);
}

void JiaSuEffect::setTotalTime(float time)
{
	_totalTime = time;
}