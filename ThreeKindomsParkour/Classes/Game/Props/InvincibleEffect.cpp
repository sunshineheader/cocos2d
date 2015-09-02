#include "InvincibleEffect.h"
#include "Game/GameMap.h"
#include "Game/GameObjects/ScoreItem.h"
#include "Game/ZhuGong.h"

USING_NS_CC;

InvincibleEffect::InvincibleEffect()
: _zhugong(nullptr)
, _gameMap(nullptr)
, _stateTime(0.0f)
, _totalTime(8.0f)
{
}

InvincibleEffect::~InvincibleEffect()
{
}

bool InvincibleEffect::init()
{
	scheduleUpdate();

	return true;
}

void InvincibleEffect::update(float delta)
{
	if (_gameMap == nullptr)
		return;

	_stateTime += delta;
	if (_stateTime >= _totalTime)
	{
		_baguadun->removeFromParent();
		_gameMap->getZhuGong()->setInvincible(false);
		removeFromParent();
		return;
	}
}

void InvincibleEffect::setZhuGong(ZhuGong *zhugong)
{
	_zhugong = zhugong;
}

void InvincibleEffect::setGameMap(GameMap *gameMap)
{
	_gameMap = gameMap;
	_gameMap->getZhuGong()->setInvincible(true);
	_baguadun = cocos2d::Sprite::create("Icons/Shield.png");
	_baguadun->setPositionY(50);
	_gameMap->getZhuGong()->addChild(_baguadun);
}

void InvincibleEffect::setTotalTime(float time)
{
	_totalTime = time;
}