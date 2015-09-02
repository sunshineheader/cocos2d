#include "SpearSoldier.h"
#include "Game/GameMap.h"
#include "Game/ZhuGong.h"

#include "Math/Intersector.h"

USING_NS_CC;
using namespace cocostudio;
using namespace std;

SpearSoldier::SpearSoldier()
: _isAttacking(false)
{
}

SpearSoldier::~SpearSoldier()
{
}

bool SpearSoldier::init()
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Test/Monster2.ExportJson");
	_armature = Armature::create("Monster2");
	_animation = _armature->getAnimation();
	_animation->play("Idle");

	_animation->setMovementEventCallFunc(
		[=](Armature * armature, MovementEventType type, const string &movementId)
	{
		if (movementId == "Attack" && type == MovementEventType::COMPLETE)
		{
			_animation->play("Idle");
			_isAttacking = false;
		}
	});



	addChild(_armature);
	scheduleUpdate();

	return true;
}

void SpearSoldier::update(float delta)
{
	return;

	auto _zhugong = getGameMap()->getZhuGong();
	auto parentPosition = getParent()->getParent()->getPosition();
	auto position = getPosition() + parentPosition;
	position *= getParent()->getScale();

	auto distance = (position - _zhugong->getPosition()).length();
	if (distance > 150)
		return;

	checkInvincible();
	checkHurt();
	checkAttack();
	check();
}


void SpearSoldier::checkHurt()
{
	if (isNeedRemove())
		return;

	auto _zhugong = getGameMap()->getZhuGong();
	if (_zhugong->getState() != ZhuGong::State::Falling)
		return;

	auto parentPosition = getParent()->getParent()->getPosition();
	auto position = getPosition() + parentPosition;
	auto vertices = _armature->getBone("Head")->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
	auto collision = Math::Polygon(vertices);
	collision.setPosition(position.x, position.y);

	if (_zhugong->checkCollisionWithFeet(collision)) {
		die();


		getGameMap()->getZhuGong()->stepJump();
	}
}

void SpearSoldier::checkInvincible()
{
	if (isNeedRemove())
		return;

	auto _zhugong = getGameMap()->getZhuGong();
	if (!_zhugong->isInvincible())
		return;

	vector<string> bonesNames{ "Head", "Weapon" };
	auto parentPosition = getParent()->getParent()->getPosition();
	auto position = getPosition() + parentPosition;
	for (auto name : bonesNames)
	{
		auto bone = _armature->getBone(name);
		if (bone == nullptr)
			continue;

		if (bone->getColliderDetector() == nullptr
			|| bone->getColliderDetector()->getColliderBodyList().size() == 0)
			continue;

		auto vertices = bone->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
		auto boneRegion = Math::Polygon(vertices);
		boneRegion.setPosition(position.x, position.y);

		if (_zhugong->checkCollisionWithAllBones(boneRegion))
		{
			die();
		}
	}
}

void SpearSoldier::checkAttack()
{
	if (isNeedRemove())
		return;

	auto zhugong = getGameMap()->getZhuGong();
	auto position = getPosition() + getParent()->getParent()->getPosition();
	auto distance = (position - zhugong->getPosition()).length();
	if (distance < 220 && !_isAttacking)
	{
		_animation->play("Attack");
		_isAttacking = true;
	}
}


void SpearSoldier::check()
{
	if (!_isAttacking || isNeedRemove())
		return;

	auto _zhugong = getGameMap()->getZhuGong();
	if (_zhugong->isInvincible() || _zhugong->isDead() || isNeedRemove())
		return;

	auto parentPosition = getParent()->getParent()->getPosition();
	auto position = getPosition() + parentPosition;
	auto vertices = _armature->getBone("Weapon")->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
	auto collision = Math::Polygon(vertices);
	collision.setPosition(position.x, position.y);

	if (_zhugong->checkCollisionWithAllBones(collision))
	{
		_zhugong->die();
	}
}


void SpearSoldier::die()
{
	setNeedRemove(true);

	_animation->play("Die");

	getGameMap()->addDustAnimation(this);

	getGameMap()->addOneCollectedObject("Kill_SpearSoldier");
}