#include "WenChen.h"

#include "cocostudio\CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace std;

WenChen::WenChen()
{
}

WenChen::~WenChen()
{
}

bool WenChen::init()
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Test/ZhuGeLiang.ExportJson");
	auto wenchen = Armature::create("ZhuGeLiang");
	auto animation = wenchen->getAnimation();
	animation->play("Idle");

	addChild(wenchen);

	scheduleUpdate();

	return true;
}

static float s_moveSpeed = 60.0f;
static float s_direction = 1.0f;
static float s_downDistance = 32.0f;
static float s_upDistance = 64.0f;

void WenChen::update(float delta)
{
	auto position = getPosition();
	position.y += s_direction * s_moveSpeed * delta;

	if (position.y - _initialPosition.y > s_upDistance)
	{
		position.y = _initialPosition.y + s_upDistance;
		s_direction *= -1.0f;
	}
	if (_initialPosition.y - position.y > s_downDistance)
	{
		position.y = _initialPosition.y - s_downDistance;
		s_direction *= -1.0f;
	}

	setPosition(position);
}

void WenChen::setInitalPosition(const cocos2d::Vec2 &position)
{
	_initialPosition = position;
	setPosition(_initialPosition);
}