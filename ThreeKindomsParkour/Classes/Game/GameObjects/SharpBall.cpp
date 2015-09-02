#include "SharpBall.h"
#include "Game/GameMap.h"
#include "Game/ZhuGong.h"

#include "Math/Intersector.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;

SharpBall::SharpBall()
{

}

SharpBall::~SharpBall()
{
}

bool SharpBall::init()
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Test/SharpBall.ExportJson");
	_armature = Armature::create("SharpBall");
	_animation = _armature->getAnimation();
	_animation->play("Idle");

	addChild(_armature);

	scheduleUpdate();

	return true;
}

void SharpBall::update(float delta)
{
	return;

	auto _zhugong = getGameMap()->getZhuGong();
	if (_zhugong->isDead() || isNeedRemove())
		return;

	auto parentPosition = getParent()->getParent()->getPosition();
	auto position = getPosition() + parentPosition;
	position *= getParent()->getScale();

	auto distance = (position - _zhugong->getPosition()).length();
	if (distance > 150)
		return;

	auto vertices = _armature->getBone("SharpBall")->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
	auto collision = Math::Polygon(vertices);
	collision.setPosition(position.x, position.y);


	if (_zhugong->checkCollisionWithAllBones(collision))
	{
		if (_zhugong->isInvincible())
		{
			die();

			getGameMap()->addOneCollectedObject("Kill_SharpBall");
		}
		else
		{
			_zhugong->die();
		}
	}
}