#include "ZhuGong.h"
#include "GameMap.h"
#include "Platform.h"
#include "Utils/Properties.h"
#include "Utils/TmxMapHelper.h"

#include "Math/Intersector.h"
#include "Math/MathUtils.h"

#include "Game/GameObjects/ScoreItem.h"

#include "cocostudio\CocoStudio.h"

#include <list>

USING_NS_CC;
using namespace cocostudio;
using namespace std;

static const char *s_kJumpName[] = {
    "Jump1", "Jump2", "Jump3"
};
static bool s_isInit = false;
static float s_Damping;
static float s_Gravity;
static float s_JumpSpeed[3];

static float s_moveSpeed = 120;
static float s_quickMoveSpeed = 800;

static std::vector<float> s_vertices[5][2];


ZhuGong::ZhuGong()
: _zhugong(nullptr)
, _animation(nullptr)
, _state(State::Falling)
, _numJump(0)
, _maxJump(3)
, _isDead(false)
, _initPositionX(0.0f)

, _isFlying(false)
, _isInvincible(false)
{
}

ZhuGong::~ZhuGong()
{
}

bool ZhuGong::init()
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
	//schedule([=](float delta){
	//	Properties p("Data/Config.json");
	//	s_Damping = p.getDoubleForKey("Damping", 0.25);
	//	s_Gravity = p.getDoubleForKey("Gravity", -2.5);
	//	s_JumpSpeed[0] = p.getDoubleForKey("FirstJumpSpeed", 60);
	//	s_JumpSpeed[1] = p.getDoubleForKey("SecondJumpSpeed", 40);
	//	s_JumpSpeed[2] = p.getDoubleForKey("ThirdJumpSpeed", 30);
	//	s_moveSpeed = p.getDoubleForKey("InitalMoveSpeed", 120);
	//}, 1, "GameMap");

	ArmatureDataManager::getInstance()->addArmatureFileInfo("Test/WuJiangLiuBeiGongCheng.ExportJson");
	_zhugong = Armature::create("WuJiangLiuBeiGongCheng");
	_animation = _zhugong->getAnimation();
	_animation->play("Run");

	_leftfoot = _zhugong->getBone("LeftLeg");
	_rightfoot = _zhugong->getBone("RightLeg");

	_animation->setMovementEventCallFunc(
		[=](Armature * armature, MovementEventType type, const string &movementId)
	{
		if (type == MovementEventType::COMPLETE
			|| type == MovementEventType::LOOP_COMPLETE)
		{
			if (movementId == "Land")
			{
				run();
			}
		}
	});


	addChild(_zhugong);

	setScale(0.8f);

    scheduleUpdate();

    return true;
}

void ZhuGong::update(float delta)
{
	if (_isFlying)
	{
		setPositionX(getPositionX() + _gameMap->getMoveSpeed() * delta);
		return;
	}

    if (getPositionX() + getParent()->getPositionX() < _initPositionX)
    {
        _velocity.x = s_quickMoveSpeed;
    }
    else
    {
		_velocity.x = _gameMap->getMoveSpeed();
    }

    _velocity.y += s_Gravity;
    _velocity *= delta;

    if (_state == State::Jumping && _velocity.y < 1) {
		fall();
    }

  checkVerticalCollisionWithPlatforms();
	checkHorizoztalCollisionWithPlatforms();

    setPosition(getPosition() + _velocity);
    _velocity *= 1 / delta;

	checkWithStars();

    if (getPositionY() < -36) {
//       die();
    }
}

void ZhuGong::checkVerticalCollisionWithPlatforms()
{
    if (_state == State::Jumping)
        return;

	auto vertices1 = _leftfoot->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
	auto vertices2 = _rightfoot->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
	Math::Polygon leftfoot(vertices1);
	Math::Polygon rightfoot(vertices2);
	leftfoot.setPosition(getPositionX(), getPositionY());
	rightfoot.setPosition(getPositionX(), getPositionY());

	auto zhugongRect = _zhugong->getBoundingBox();
	zhugongRect.origin += getPosition();

	auto terrains = _gameMap->getTerrains();
	for (auto terrain : terrains)
	{
		auto terrainPosition = terrain->getPosition();
		auto platforms = terrain->getChildByName("Platforms");

		auto terrainRect = terrain->getBoundingBox();
		if (!terrainRect.intersectsRect(zhugongRect))
			continue;

		for (auto node : platforms->getChildren())
		{
			auto platform = dynamic_cast<Platform*>(node);
			if (platform == nullptr || !platform->hasCollisionRegionDownY())
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

void ZhuGong::checkWithStars()
{
	auto zhugongRect = _zhugong->getBoundingBox();
	zhugongRect.origin += getPosition();

    auto terrains = _gameMap->getTerrains();
    for (auto terrain : terrains)
    {
        auto terrainPosition = terrain->getPosition();
        auto platforms = terrain->getChildByName("Platforms");

        auto stars = terrain->getChildByName("Stars");
        if (stars != nullptr) {
            for (auto node : stars->getChildren()) {
				auto star = dynamic_cast<ScoreItem*>(node);
				if (star == nullptr || star->isCollecting() || star->isNeedRemove())
					continue;
                
                Rect rect;
                auto position = star->getPosition();
                auto size = star->getContentSize();
                auto anchor = star->getAnchorPoint();
                rect.origin.x = terrainPosition.x + position.x - size.width * anchor.x;
                rect.origin.y = terrainPosition.y + position.y - size.height * anchor.y;
                rect.size = size;

				if (zhugongRect.intersectsRect(rect)) {
					star->setNeedRemove(true);
                    star->runAction(Sequence::createWithTwoActions(ScaleTo::create(0.25f, 0.0f),
                        Hide::create()));

                    _gameMap->addScore(50);

					_gameMap->addOneCollectedObject(star->getTypeName());
                }
            }
        }
    }
}

void ZhuGong::checkHorizoztalCollisionWithPlatforms()
{
    if (_state == State::Jumping)
        return;

	auto zhugongRect = _zhugong->getBoundingBox();
	Math::Polygon zhugongRegion;
	MathUtils::rectToPolygon(zhugongRect, zhugongRegion);
	zhugongRegion.setPosition(getPositionX(), getPositionY());

    auto terrains = _gameMap->getTerrains();
    for (auto terrain : terrains)
    {
        auto terrainPosition = terrain->getPosition();
        auto platforms = terrain->getChildByName("Platforms");

		auto terrainRect = terrain->getBoundingBox();
		if (!terrainRect.intersectsRect(zhugongRect))
			continue;

        for (auto node : platforms->getChildren())
        {
			auto platform = dynamic_cast<Platform*>(node);
			if (platform == nullptr || !platform->hasCollisionRegionX())
				continue;

			auto platformPosition = node->getPosition();
			auto origin = terrainPosition + platformPosition;
			auto collisionX = platform->getCollisionRegionX();
			collisionX.setPosition(origin.x, origin.y);

			if (Intersector::overlapConvexPolygons(collisionX, zhugongRegion))
			{
				_velocity.x = 0;
				return;
			}
        }
    }
}


void ZhuGong::setGameMap(GameMap *gameMap)
{
	_gameMap = gameMap;
}

void ZhuGong::run()
{
	if (_state == State::Running)
		return;

	_state = State::Running;


	_animation->play("Run");
}

void ZhuGong::jump()
{
	if (_numJump >= _maxJump || _isFlying)
		return;

	_state = State::Jumping;

	_animation->play(s_kJumpName[_numJump]);

	_velocity.y = s_JumpSpeed[_numJump];
	_numJump += 1;

	if (_numJump == 2)
	{
		_gameMap->addNumDoubleJump();
	}
}

void ZhuGong::fall()
{
	if (_state == State::Falling)
		return;

	_state = State::Falling;

	_animation->play("Fall");
}

void ZhuGong::land()
{
	_velocity.y = 0;

	_numJump = 0;

	if (_state == State::Landing || _state == State::Running)
		return;

	_state = State::Landing;

	_animation->play("Land");
}

void ZhuGong::die()
{
    //_animation->play("Die");

    _isDead = true;

	//_velocity.y = 1000;
}

bool ZhuGong::isDead() const
{
    return _isDead;
}

void ZhuGong::setInitPositionX(float x)
{
    _initPositionX = x;
}

float ZhuGong::getInitPositionX() const
{
    return _initPositionX;
}

void ZhuGong::setFlying(bool isFlying)
{
	_isFlying = isFlying;
	if (isFlying)
	{
		_numJump = 0;
		_isInvincible = true;

		_animation->play("Flying");
	}
	else
	{
		_isInvincible = false;

		fall();
	}
}

bool ZhuGong::isFlying() const
{
	return _isFlying;
}

void ZhuGong::setInvincible(bool isInvincible)
{
	_isInvincible = isInvincible;
}

bool ZhuGong::isInvincible() const
{
	return _isInvincible;
}

ZhuGong::State ZhuGong::getState() const
{
	return _state;
}

void ZhuGong::setAttackRegion(const std::vector<float> &vertices)
{
	_attackRegion.setVertices(vertices);
}

void ZhuGong::setDefenceRegion(const std::vector<float> &vertices)
{
	_defenceRegion.setVertices(vertices);
}

Math::Polygon& ZhuGong::getAttackRegion()
{
	_attackRegion.setScale(getScale());
	return _attackRegion;
}

Math::Polygon& ZhuGong::getDefenceRegion()
{
	_defenceRegion.setScale(getScale());
	return _defenceRegion;
}

bool ZhuGong::checkCollisionWithAllBones(Math::Polygon &region)
{
	vector<string> bonesNames{ "Head", "Body", "RightLeg", "LeftLeg" };
	for (auto name : bonesNames)
	{
		auto bone = _zhugong->getBone(name);
		if (bone == nullptr)
			continue;

		if (bone->getColliderDetector() == nullptr
			|| bone->getColliderDetector()->getColliderBodyList().size() == 0)
			continue;

		auto vertices = bone->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
		auto boneRegion = Math::Polygon(vertices);
		boneRegion.setPosition(getPositionX(), getPositionY());
		if (Intersector::overlapConvexPolygons(region, boneRegion))
			return true;
	}

	return false;
}

bool ZhuGong::checkCollisionWithFeet(Math::Polygon &region)
{
	vector<string> bonesNames{ "RightLeg", "LeftLeg" };
	for (auto name : bonesNames)
	{
		auto bone = _zhugong->getBone(name);
		if (bone == nullptr)
			continue;

		if (bone->getColliderDetector() == nullptr
			|| bone->getColliderDetector()->getColliderBodyList().size() == 0)
			continue;

		auto vertices = bone->getColliderDetector()->getColliderBodyList().at(0)->getCalculatedVertexList();
		auto boneRegion = Math::Polygon(vertices);
		boneRegion.setPosition(getPositionX(), getPositionY());
		if (Intersector::overlapConvexPolygons(region, boneRegion))
			return true;
	}

	return false;
}

void ZhuGong::stepJump()
{
	_numJump = 1;

	_state = State::Jumping;

	_animation->play(s_kJumpName[_numJump]);

	_velocity.y = s_JumpSpeed[_numJump];
}


