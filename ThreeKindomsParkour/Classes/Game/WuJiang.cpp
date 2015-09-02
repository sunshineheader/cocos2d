#include "WuJiang.h"
#include "GameMap.h"
#include "Platform.h"
#include "Utils/Properties.h"
#include "Utils/TmxMapHelper.h"
#include "Math/MathUtils.h"
#include "Math/Intersector.h"

#include "Math/Intersector.h"

#include "GameObjects/GameObject.h"

#include "cocostudio\CocoStudio.h"

#include <list>
#include <limits>

USING_NS_CC;
using namespace cocostudio;
using namespace std;


static bool s_isInit = false;
static float s_Damping;
static float s_Gravity;
static float s_JumpSpeed[3];

static float s_moveSpeed = 120;
static float s_quickMoveSpeed = 800;
static float s_slowMoveSpeed = 200;
static float s_attackSpeed = 300;

WuJiang::WuJiang()
: _wujiang(nullptr)
, _animation(nullptr)
, _weapon(nullptr)
, _leftfoot(nullptr)
, _rightfoot(nullptr)

, _state(State::Falling)


, _initPositionX(0.0f)

, _isAttacking(false)
, _attackDuration(5)
, _attackStateTime(0.0f)
, _attackTotalTime(0.5f)
, _attackingTime(0.0f)
, _fowardDistance(0.0f)

, _lastPositionX(FLT_MAX)
, _stopTime(0)
{
}

WuJiang::~WuJiang()
{
}

bool WuJiang::init()
{
	if (!s_isInit)
	{
		s_isInit = true;
		Properties p("Data/Config.json");
		s_Damping = p.getDoubleForKey("Damping", 0.25);
		s_Gravity = p.getDoubleForKey("Gravity", -2.5);
		s_JumpSpeed[0] = p.getDoubleForKey("FirstJumpSpeed", 60);
		s_JumpSpeed[1] = p.getDoubleForKey("SecondJumpSpeed", 40);
		s_JumpSpeed[2] = p.getDoubleForKey("ThirdJumpSpeed", 30);
		s_moveSpeed = p.getDoubleForKey("InitalMoveSpeed", 120);
	}

	ArmatureDataManager::getInstance()->addArmatureFileInfo("Test/WJ_ZhaoYun.ExportJson");
	_wujiang = Armature::create("WJ_ZhaoYun");
	_animation = _wujiang->getAnimation();
	_animation->play("Run");

	_weapon = _wujiang->getBone("Weapon");
	_leftfoot = _wujiang->getBone("LeftFoot");
	_rightfoot = _wujiang->getBone("RightFoot");

	addChild(_wujiang);
	scheduleUpdate();


	_wujiang->setScale(0.52f);

	_animation->setMovementEventCallFunc(
		[=](Armature * armature, MovementEventType type, const string &movementId)
	{
		if (type == MovementEventType::COMPLETE)
		{
			if (movementId == "Land")
			{
				run();
			}
		}

	});


	return true;
}

void WuJiang::update(float delta)
{
	if (getPositionX() + getParent()->getPositionX() < _initPositionX)
	{
		_velocity.x = s_quickMoveSpeed;
	}
	else
	{
		_velocity.x = _gameMap->getMoveSpeed();
	}

	checkCollisionWithJumpRegions();

	_velocity.y += s_Gravity;
	_velocity *= delta;

	if (_state == State::Jumping && _velocity.y < 1) {
		fall();
	}

	checkVerticalCollisionWithPlatforms();

	setPosition(getPosition() + _velocity);
	_velocity *= 1 / delta;

	checkAttackBlocks(delta);

	if (getPositionY() < 8 && _state != State::Jumping)
	{
		jump();
	}

	if (_isAttacking)
	{
		_fowardDistance += s_attackSpeed * delta;
		setPositionX(getPositionX() + s_attackSpeed * delta);
	}
	else if (_fowardDistance > 0)
	{
		_fowardDistance -= s_attackSpeed * delta;
		setPositionX(getPositionX() - s_attackSpeed * delta);
	}
	
	if (_lastPositionX != FLT_MAX)
	{
		auto deltaX = fabs(_lastPositionX - getPositionX());
		if (deltaX < 2)
		{
			jump();
		}
	}
	_lastPositionX = getPositionX();
}

void WuJiang::checkAttackBlocks(float delta)
{
	return;

	if (!_isAttacking)
	{
		_attackStateTime += delta;
		if (_attackStateTime >= _attackDuration
			&& _state != State::Jumping
			&& blocksInRange())
		{
			_attackStateTime = 0;
			_isAttacking = true;
			attack();
		}
	}

	if (_isAttacking)
	{
		_attackingTime += delta;
		if (_attackingTime >= _attackTotalTime)
		{
			_attackingTime = 0;
			_isAttacking = false;
			run();
		}

		checkAttack("Blocks");
		checkAttack("SpearSoldiers");
		checkAttack("Houses");
		checkAttack("ShieldSoldiers");
	}
}

void WuJiang::checkAttack(const std::string &name)
{
	auto terrains = _gameMap->getTerrains();
	auto positionX = getPositionX();
	for (auto terrain : terrains)
	{
		auto terrainPosition = terrain->getPosition();
		auto blocks = terrain->getChildByName(name);
		if (blocks != nullptr) {
			for (auto block : blocks->getChildren()) {
				auto object = dynamic_cast<GameObject*>(block);
				if (object == nullptr || object->isNeedRemove())
					continue;
				
				auto position = terrainPosition + object->getPosition();
				auto rect = object->_armature->getBoundingBox();
				position *= getParent()->getScale();
				rect.origin += position;

				auto distance = (position - getPosition()).length();
				if (distance > 150)
					continue;
				
				Math::Polygon hurtRegion;
				MathUtils::rectToPolygon(rect, hurtRegion);

				auto vertices = _weapon->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
				Math::Polygon weapon(vertices);
				weapon.setPosition(getPositionX(), getPositionY());

				if (Intersector::overlapConvexPolygons(weapon, hurtRegion)) {
					object->die();

					if (name == "Blocks")
					{
						_gameMap->addOneCollectedObject("Kill_Block");
					}
					else if (name == "SpearSoldiers")
					{
						_gameMap->addOneCollectedObject("Kill_SpearSoldier");
					}
					else if (name == "Houses")
					{
						_gameMap->addOneCollectedObject("Kill_LiangChe");
					}
					else if (name == "ShieldSoldiers")
					{
						_gameMap->addOneCollectedObject("Kill_ShieldSoldier");
					}
				}
			}
		}
	}
}

bool WuJiang::blocksInRange() const
{
	return blocksInRange("Blocks")
		|| blocksInRange("SpearSoldiers")
		|| blocksInRange("Houses")
		|| blocksInRange("ShieldSoldiers");
}

bool WuJiang::blocksInRange(const std::string &name) const
{
	auto terrains = _gameMap->getTerrains();
	auto positionX = getPositionX();
	for (auto terrain : terrains)
	{
		auto terrainPosition = terrain->getPosition();
		auto blocks = terrain->getChildByName(name);
		if (blocks != nullptr) {
			for (auto block : blocks->getChildren()) {
				auto object = dynamic_cast<GameObject*>(block);
				if (object == nullptr || object->isNeedRemove())
					continue;

				auto position = terrainPosition + object->getPosition();
				auto rect = object->_armature->getBoundingBox();
				rect.origin += position;

				Rect wujiangRect = _wujiang->getBoundingBox();
				wujiangRect.origin += getPosition();

				if (wujiangRect.intersectsRect(rect)) {
					return true;
				}
			}
		}
	}

	return false;
}

void WuJiang::checkCollisionWithJumpRegions()
{
	if (_state == State::Jumping)
		return;

	auto wujiangRect = _wujiang->getBoundingBox();
	wujiangRect.origin += getPosition();

	auto terrains = _gameMap->getTerrains();
	for (auto terrain : terrains)
	{
		auto terrainPosition = terrain->getPosition();
		auto platforms = terrain->getChildByName("Platforms");

		auto terrainRect = terrain->getBoundingBox();
		if (!terrainRect.intersectsRect(wujiangRect))
			continue;

		for (auto node : platforms->getChildren())
		{
			auto platform = dynamic_cast<Platform*>(node);
			if (platform == nullptr || !platform->hasJumpRegion() || !platform->isJumpOpen())
				continue;

			auto platformPosition = platform->getPosition();
			auto origin = terrainPosition + platformPosition;
			auto rect = platform->getJumpRegion();
			rect.origin += origin;

			if (wujiangRect.intersectsRect(rect)) {
				platform->setJumpOpen(false);
				jump();
				return;
			}
		}
	}
}

void WuJiang::checkVerticalCollisionWithPlatforms()
{
	if (_state == State::Jumping)
		return;

	auto vertices1 = _leftfoot->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
	auto vertices2 = _rightfoot->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
	Math::Polygon leftfoot(vertices1);
	Math::Polygon rightfoot(vertices2);
	leftfoot.setPosition(getPositionX(), getPositionY());
	rightfoot.setPosition(getPositionX(), getPositionY());

	auto wujiangRect = _wujiang->getBoundingBox();
	wujiangRect.origin += getPosition();

	auto terrains = _gameMap->getTerrains();
	for (auto terrain : terrains)
	{
		auto terrainPosition = terrain->getPosition();
		auto platforms = terrain->getChildByName("Platforms");

		auto terrainRect = terrain->getBoundingBox();
		if (!terrainRect.intersectsRect(wujiangRect))
			continue;

		for (auto node : platforms->getChildren())
		{
			auto platform = dynamic_cast<Platform*>(node);
			if (platform == nullptr)
				continue;

			auto platformPosition = node->getPosition();
			auto origin = terrainPosition + platformPosition;
			auto collisionDownY = platform->getCollisionRegionDownY();
			MinimumTranslationVector mtk;
			collisionDownY.setPosition(origin.x, origin.y);

			if (Intersector::overlapConvexPolygons(collisionDownY, leftfoot, &mtk)
				|| Intersector::overlapConvexPolygons(collisionDownY, rightfoot, &mtk)) {

				land();

				//setPosition(getPosition() + mtk.normal * mtk.depth);

				return;
			}
		}
	}
}


void WuJiang::run()
{
	if (_state == State::Running)
		return;

	_state = State::Running;
	_animation->play("Run");
}

void WuJiang::resetAttackState()
{
	if (_isAttacking)
	{
		_attackingTime = 0;
		_attackStateTime = 0;
		_isAttacking = false;
	}
}

void WuJiang::jump()
{
	if (_state == State::Jumping)
		return;

	resetAttackState();

	_state = State::Jumping;

	vector<string> names{ "Jump0", "Jump1" };
	_animation->playWithNames(names, -1, false);

	_velocity.y = 900;
}

void WuJiang::fall()
{
	if (_state == State::Falling)
		return;

	_state = State::Falling;

	vector<string> names{ "Fall0", "Fall1" };
	_animation->playWithNames(names, -1, false);
}

void WuJiang::land()
{
	_velocity.y = 0;

	if (_state == State::Landing || _state == State::Running
		|| _state == State::Attacking)
		return;

	_state = State::Landing;

	_animation->play("Land");
}

void WuJiang::attack()
{
	if (_state == State::Attacking)
		return;

	_state = State::Attacking;

	_animation->play("Attack");
}

void WuJiang::setGameMap(GameMap *gameMap)
{
	_gameMap = gameMap;
}

void WuJiang::setInitPositionX(float x)
{
	_initPositionX = x;
}

float WuJiang::getInitPositionX() const
{
	return _initPositionX;
}

