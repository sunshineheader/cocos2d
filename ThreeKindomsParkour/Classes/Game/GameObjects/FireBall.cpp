#include "FireBall.h"
#include "Game/GameMap.h"
#include "Game/ZhuGong.h"

#include "Math/Intersector.h"

USING_NS_CC;
using namespace cocostudio;
using namespace std;

FireBall::FireBall()
{
}

FireBall::~FireBall()
{
}

bool FireBall::init()
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Test/FireBall.ExportJson");
	_armature = Armature::create("FireBall");
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

void FireBall::update(float delta)
{
	return;

	auto position = getPosition();
	position.x += -200 * delta;

	setPosition(position);

	auto _zhugong = getGameMap()->getZhuGong();
	if (_zhugong->isDead() || isNeedRemove())
		return;

	auto parentPosition = getParent()->getParent()->getPosition();
	position += parentPosition;
	position *= getParent()->getScale();

	auto distance = (position - _zhugong->getPosition()).length();
	if (distance > 150)
		return;

	auto vertices = _armature->getBone("FireBall")->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
	auto collision = Math::Polygon(vertices);
	collision.setPosition(position.x, position.y);

	if (_zhugong->checkCollisionWithAllBones(collision))
	{
		if (_zhugong->isInvincible())
		{
			die();

			getGameMap()->addOneCollectedObject("Kill_FireBall");
		}
		else
		{
			_zhugong->die();
		}
	}
}
