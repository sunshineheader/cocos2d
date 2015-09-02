#include "House.h"
#include "Game/GameMap.h"
#include "Game/ZhuGong.h"

#include "Math/MathUtils.h"
#include "Math/Polygon.h"
#include "Math/Intersector.h"


#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;

House::House()
: _isAttacking(false)
{
}

House::~House()
{
}

bool House::init()
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Test/LiangChe01.ExportJson");
	_armature = Armature::create("LiangChe01");
	_animation = _armature->getAnimation();
	_animation->play("Idle");

	addChild(_armature);

	_animation->setMovementEventCallFunc(
		[=](Armature * armature, MovementEventType type, const string &movementId)
	{
		if (movementId == "Broken" && type == MovementEventType::COMPLETE)
		{
			_isAttacking = false;
		}
	});

	scheduleUpdate();

	
	return true;
}

void House::update(float delta)
{
	return;

	if (_isAttacking)
	{
		checkAttack();
	}
	else
	{
		checkJump();
		checkTouch();
	}
}

void House::die()
{
	setNeedRemove(true);

	_animation->play("Broken");

	getGameMap()->addDustAnimation(this);

	getGameMap()->addOneCollectedObject("Kill_LiangChe");

	_isAttacking = true;
}

void House::checkJump()
{
	if (isNeedRemove())
		return;

	auto _zhugong = getGameMap()->getZhuGong();
	if (_zhugong->getState() != ZhuGong::State::Falling)
		return;

	auto parentPosition = getParent()->getParent()->getPosition();
	auto position = getPosition() + parentPosition;
	position *= getParent()->getScale();

	auto distance = (position - _zhugong->getPosition()).length();
	if (distance > 150)
		return;


	auto vertices = _armature->getBone("WholeBody")->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
	auto collision = Math::Polygon(vertices);

	collision.setPosition(position.x, position.y);

	if (_zhugong->checkCollisionWithFeet(collision)) {
		die();

		getGameMap()->getZhuGong()->stepJump();
	}
}

void House::checkTouch()
{
	if (isNeedRemove())
		return;

	auto _zhugong = getGameMap()->getZhuGong();

	auto parentPosition = getParent()->getParent()->getPosition();
	auto position = getPosition() + parentPosition;
	position *= getParent()->getScale();

	auto distance = (position - _zhugong->getPosition()).length();
	if (distance > 150)
		return;

	Rect rect = _armature->getBoundingBox();
	rect.origin += position;
	Math::Polygon collsionRegion;
	MathUtils::rectToPolygon(rect, collsionRegion);

	if (_zhugong->checkCollisionWithAllBones(collsionRegion))
	{
		die();
	}
}

void House::checkAttack()
{
	vector<string> bonesNames{ "BaShou", "DengZi", "Tie", "LunZi", "YuanBao", "CheZi",
					"BaoXiang", "QiZi" };
	auto parentPosition = getParent()->getParent()->getPosition();
	auto position = getPosition() + parentPosition;
	position *= getParent()->getScale();

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

		checkAttack(boneRegion, "Blocks");
		checkAttack(boneRegion, "SpearSoldiers");
		checkAttack(boneRegion, "Houses");
		checkAttack(boneRegion, "ShieldSoldiers");
	}
}

void House::checkAttack(Math::Polygon &region, const std::string &name)
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

				Math::Polygon hurtRegion;
				MathUtils::rectToPolygon(rect, hurtRegion);

				if (Intersector::overlapConvexPolygons(region, hurtRegion)) {
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