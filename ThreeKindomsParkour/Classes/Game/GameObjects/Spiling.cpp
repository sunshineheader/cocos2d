#include "Spiling.h"
#include "Game/GameMap.h"
#include "Game/ZhuGong.h"

#include "Math/Intersector.h"

USING_NS_CC;
using namespace cocostudio;
using namespace std;

Spiling::Spiling()
{
}

Spiling::~Spiling()
{
}

bool Spiling::init()
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Test/DaoJu.ExportJson");
	_armature = Armature::create("DaoJu");
	_animation = _armature->getAnimation();
	_animation->play("Idle");

	addChild(_armature);

	scheduleUpdate();

	return true;
}

static float s_moveSpeed = 60.0f;
static float s_direction = 1.0f;
static float s_downDistance = 16.0f;
static float s_upDistance = 16.0f;

void Spiling::update(float delta)
{
	return;

	auto position = getPosition();
	position.x += -150 * delta;

	setPosition(position);


	auto parentPosition = getParent()->getParent()->getPosition();
	position += parentPosition;
	position *= getParent()->getScale();

	auto _zhugong = getGameMap()->getZhuGong();
	auto distance = (position - _zhugong->getPosition()).length();
	if (distance > 150)
		return;

	checkHurt();
	checkInvincible();
	checkAttack();
}



void Spiling::checkHurt()
{
	if (isNeedRemove())
		return;


	auto _zhugong = getGameMap()->getZhuGong();
	if (_zhugong->getState() != ZhuGong::State::Falling)
		return;

	auto parentPosition = getParent()->getParent()->getPosition();
	auto position = getPosition() + parentPosition;
	auto vertices = _armature->getBone("Spiling")->getColliderDetector()->getColliderBodyList().at(2)->getCalculatedVertexList();
	auto collision = Math::Polygon(vertices);
	collision.setPosition(position.x, position.y);

	if (_zhugong->checkCollisionWithFeet(collision)) {
		setNeedRemove(true);
		runAction(Sequence::createWithTwoActions(ScaleTo::create(0.25f, 0.0f),
			Hide::create()));

		getGameMap()->addDustAnimation(this);

		getGameMap()->getZhuGong()->stepJump();
	}
}

void Spiling::checkAttack()
{
	auto _zhugong = getGameMap()->getZhuGong();
	if (_zhugong->isInvincible() || isNeedRemove())
		return;

	auto parentPosition = getParent()->getParent()->getPosition();
	auto position = getPosition() + parentPosition;
	auto vertices0 = _armature->getBone("Spiling")->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
	auto collision0 = Math::Polygon(vertices0);
	collision0.setPosition(position.x, position.y);

	if (_zhugong->checkCollisionWithAllBones(collision0))
	{
		getGameMap()->getZhuGong()->die();
		return;
	}

	auto vertices1 = _armature->getBone("Spiling")->getColliderDetector()->getColliderBodyList().at(1)->getCalculatedVertexList();
	auto collision1 = Math::Polygon(vertices1);
	collision1.setPosition(position.x, position.y);

	if (_zhugong->checkCollisionWithAllBones(collision1)) 
	{
		getGameMap()->getZhuGong()->die();
	}
}

void Spiling::checkInvincible()
{
	auto _zhugong = getGameMap()->getZhuGong();
	if (!_zhugong->isInvincible())
		return;

	auto parentPosition = getParent()->getParent()->getPosition();
	auto position = getPosition() + parentPosition;
	auto vertices0 = _armature->getBone("Spiling")->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
	auto collision0 = Math::Polygon(vertices0);
	collision0.setPosition(position.x, position.y);

	if (_zhugong->checkCollisionWithAllBones(collision0))
	{
		die();
		return;
	}

	auto vertices1 = _armature->getBone("Spiling")->getColliderDetector()->getColliderBodyList().at(1)->getCalculatedVertexList();
	auto collision1 = Math::Polygon(vertices1);
	collision1.setPosition(position.x, position.y);

	if (_zhugong->checkCollisionWithAllBones(collision1))
	{
		die();
	}
}

void Spiling::die()
{
	runAction(Sequence::createWithTwoActions(ScaleTo::create(0.25f, 0.0f),
		Hide::create()));

	_gameMap->addDustAnimation(this);

	setNeedRemove(true);

	getGameMap()->addOneCollectedObject("Kill_Spiling");
}