#include "Block.h"
#include "Game/GameMap.h"
#include "Game/ZhuGong.h"

#include "Math/Intersector.h"
#include "Math/MathUtils.h"

#include "cocostudio\CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace std;


Block::Block()
{
}

Block::~Block()
{
}

bool Block::init()
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Test/Block.ExportJson");
	_armature = Armature::create("Block");
	_animation = _armature->getAnimation();
	//_animation->play("Idle");

	addChild(_armature);

	scheduleUpdate();

	return true;
}

void Block::update(float delta)
{
	return;

	auto _zhugong = getGameMap()->getZhuGong();
	if (_zhugong->isDead() || isNeedRemove())
		return;

	auto parentPosition = getParent()->getParent()->getPosition();
	auto position = getPosition() + parentPosition;
	position *= getParent()->getScaleX();

	auto distance = (position - _zhugong->getPosition()).length();
	if (distance > 150)
		return;

	auto vertices = _armature->getBone("Block")->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
	auto collision = Math::Polygon(vertices);
	collision.setPosition(position.x, position.y);

	if (_zhugong->checkCollisionWithAllBones(collision))
	{
		if (_zhugong->isInvincible())
		{
			die();

			getGameMap()->addOneCollectedObject("Kill_Block");
		}
		else
		{
			_zhugong->die();
		}
	}
}


