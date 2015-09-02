#include "AutoCollectScoreItems.h"
#include "Game/GameMap.h"
#include "Game/GameObjects/ScoreItem.h"
#include "Game/ZhuGong.h"

USING_NS_CC;

AutoCollectScoreItems::AutoCollectScoreItems()
: _zhugong(nullptr)
, _gameMap(nullptr)
, _stateTime(0.0f)
, _totalTime(0.0f)
{
}

AutoCollectScoreItems::~AutoCollectScoreItems()
{
}

bool AutoCollectScoreItems::init()
{
	scheduleUpdate();

	return true;
}

void AutoCollectScoreItems::update(float delta)
{
	if (_zhugong == nullptr || _gameMap == nullptr)
		return;

	_stateTime += delta;
	if (_stateTime >= _totalTime)
	{
		disableScoreItemsCollecting();
		removeFromParent();
		return;
	}

	auto terrains = _gameMap->getTerrains();
	for (auto terrain : terrains)
	{
		auto stars = terrain->getChildByName("Stars");
		if (stars == nullptr)
			continue;

		auto terrainPosition = terrain->getPosition();
		auto nodes = stars->getChildren();
		for (auto it = nodes.begin(); it != nodes.end(); ++it) {
			auto star = dynamic_cast<ScoreItem*>((*it));
			if (star == nullptr || star->isNeedRemove())
				continue;

			auto starPosition = star->getPosition() + terrainPosition;
			auto zhugongPosition = _zhugong->getPosition();
			if (star->isCollecting())
			{
				zhugongPosition.y += 60;
				auto direction = (zhugongPosition - starPosition);
				direction.normalize();
				auto velocity = direction * _gameMap->getMoveSpeed() * 2;
				auto displacement = velocity * delta;
				auto position = starPosition + displacement;
				star->setPosition(position - terrainPosition);

				if ((position - zhugongPosition).length() < 4.0f)
				{
					star->setNeedRemove(true);
					star->runAction(ScaleTo::create(0.25f, 0.0f));
					_gameMap->addScore(50);
				}
			}
			else
			{
				auto distance = (starPosition - zhugongPosition).length();
				if (distance < 300)
				{
					star->setCollecting(true);
				}
			}
		}
	}
}

void AutoCollectScoreItems::disableScoreItemsCollecting()
{
	auto terrains = _gameMap->getTerrains();
	for (auto terrain : terrains)
	{
		auto stars = terrain->getChildByName("Stars");
		if (stars == nullptr)
			continue;

		auto terrainPosition = terrain->getPosition();
		auto nodes = stars->getChildren();
		for (auto it = nodes.begin(); it != nodes.end(); ++it) {
			auto star = dynamic_cast<ScoreItem*>((*it));
			if (star == nullptr || star->isNeedRemove())
				continue;

			if (star->isCollecting())
			{
				star->setCollecting(false);
			}
		}
	}
}

void AutoCollectScoreItems::setZhuGong(ZhuGong *zhugong)
{
	_zhugong = zhugong;
}

void AutoCollectScoreItems::setGameMap(GameMap *gameMap)
{
	_gameMap = gameMap;
}

void AutoCollectScoreItems::setTotalTime(float time)
{
	_totalTime = time;
}