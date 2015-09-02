#include "ShieldSoldier.h"
#include "Game/GameMap.h"
#include "Game/ZhuGong.h"

#include "Math/Intersector.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;

ShieldSoldier::ShieldSoldier()
{
}

ShieldSoldier::~ShieldSoldier()
{
}

bool ShieldSoldier::init()
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Test/Monster.ExportJson");
	_armature = Armature::create("Monster");
	_animation = _armature->getAnimation();
	_animation->play("Idle");

	addChild(_armature);

	scheduleUpdate();

	return true;
}

void ShieldSoldier::update(float delta)
{
	return;

	auto _zhugong = getGameMap()->getZhuGong();
	if (_zhugong->isDead() || isNeedRemove())
		return;

	vector<string> bonesNames{ "Weapon", "Shield", "Head"};
	auto parentPosition = getParent()->getParent()->getPosition();
	auto position = getPosition() + parentPosition;
	position *= getParent()->getScale();

	auto distance = (position - _zhugong->getPosition()).length();
	if (distance > 150)
		return;

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
			if (_zhugong->isInvincible())
			{
				die();
			}
			else
			{
				_zhugong->die();
			}
		}
	}
}





void ShieldSoldier::checkAttack()
{
	auto _zhugong = getGameMap()->getZhuGong();
	if (_zhugong->isInvincible() || isNeedRemove())
		return;

	auto position = getPosition() + getParent()->getParent()->getPosition();
	auto size = getContentSize();
	auto anchor = getAnchorPoint();
	position.y -= size.height * getScale() / 2;
	_attackRegion.setPosition(position.x, position.y);
	_attackRegion.setScale(getScale());

	auto defence = _zhugong->getDefenceRegion();
	defence.setPosition(_zhugong->getPositionX(), _zhugong->getPositionY());

	if (Intersector::overlapConvexPolygons(_attackRegion, defence)) {
		_zhugong->die();
	}
}

void ShieldSoldier::checkInvincible()
{
	auto _zhugong = getGameMap()->getZhuGong();
	if (!_zhugong->isInvincible())
		return;

	auto position = getPosition() + getParent()->getParent()->getPosition();
	auto size = getContentSize();
	auto anchor = getAnchorPoint();
	position.y -= size.height * getScale() / 2;

	auto defence = _zhugong->getDefenceRegion();
	defence.setPosition(_zhugong->getPositionX(), _zhugong->getPositionY());

	_attackRegion.setPosition(position.x, position.y);

	bool flag1 = Intersector::overlapConvexPolygons(_attackRegion, defence);

	_defenceRegion.setPosition(position.x, position.y);
	bool flag2 = Intersector::overlapConvexPolygons(_defenceRegion, defence);

	if (flag1 || flag2) {
		setNeedRemove(true);
		runAction(Sequence::createWithTwoActions(ScaleTo::create(0.25f, 0.0f),
			Hide::create()));

		getGameMap()->addDustAnimation(this);
	}
}

void ShieldSoldier::die()
{
	setNeedRemove(true);

	_animation->play("Die");

	getGameMap()->addDustAnimation(this);

	getGameMap()->addOneCollectedObject("Kill_ShieldSoldier");
}

