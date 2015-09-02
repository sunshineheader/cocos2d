#include "PropItem.h"
#include "Game/GameMap.h"
#include "Game/Props/AutoCollectScoreItems.h"

USING_NS_CC;



PropItem::PropItem()
: _moveSpeed(0.0f)
{
}

PropItem::~PropItem()
{
}

bool PropItem::init()
{
	scheduleUpdate();

	return true;
}

static float s_moveSpeed = 60.0f;
static float s_direction = 1.0f;
static float s_downDistance = 16.0f;
static float s_upDistance = 16.0f;
static float s_rotateSpeed = 80.0f;

void PropItem::update(float delta)
{
	auto position = getPosition();
	position.y += s_direction * s_moveSpeed * delta;
	position.x += _moveSpeed * delta;

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

	auto rotation = getRotation();
	rotation += s_rotateSpeed * delta;
	setRotation(rotation);
}

void PropItem::setSprite(cocos2d::Node *sprite)
{
	if (sprite == nullptr)
		return;

	_sprite = sprite;
	setContentSize(sprite->getContentSize());
	addChild(sprite);
}

cocos2d::Node* PropItem::getSprite() const
{
	return _sprite;
}

static const PropItem::PropType types[5] = {
	PropItem::PropType::CiTie,
	PropItem::PropType::BaGuaDun,
	PropItem::PropType::FeiNiao,
	PropItem::PropType::FeiXingGuai,
	PropItem::PropType::JiaSu
};

void PropItem::setPropType(PropType type)
{
	int index = RandomHelper::random_int(0, 4);

	type = types[index++];

	Sprite *icon = nullptr;
	Sprite *circle = nullptr;

	_propType = type;
	switch (type)
	{
	case PropItem::PropType::CiTie:
		setTypeName("PropItem_CiTie");
		icon = Sprite::create("Icons/Prop_CiTie.png");
		circle = Sprite::create("GUI/InGame/PropBg_Green.png");
		break;

	case PropItem::PropType::BaGuaDun:
		setTypeName("PropItem_BaGuaDun");
		icon = Sprite::create("Icons/Prop_BaGuaDun.png");
		circle = Sprite::create("GUI/InGame/PropBg_Green.png");
		break;

	case PropItem::PropType::FeiNiao:
		setTypeName("PropItem_FeiNiao");
		icon = Sprite::create("Icons/Prop_FeiNiao.png");
		circle = Sprite::create("GUI/InGame/PropBg_Green.png");
		break;

	case PropItem::PropType::FeiXingGuai:
		setTypeName("PropItem_FeiXingGuai");
		icon = Sprite::create("Icons/Prop_FeiXingGuai.png");
		circle = Sprite::create("GUI/InGame/PropBg_Purple.png");
		break;

	case PropItem::PropType::JiaSu:
		setTypeName("PropItem_JiaSu");
		icon = Sprite::create("Icons/Prop_JiaSu.png");
		circle = Sprite::create("GUI/InGame/PropBg_Purple.png");
		break;
	default:
		break;
	}

	addChild(circle);
	addChild(icon);
}

PropItem::PropType PropItem::getPropType() const
{
	return _propType;
}

void PropItem::setInitalPosition(const cocos2d::Vec2 &position)
{
	_initialPosition = position;
	setPosition(_initialPosition);
}

void PropItem::setMoveSpeed(float speed)
{
	_moveSpeed = speed;
}

void PropItem::takeEffect(GameMap *gameMap)
{
	switch (_propType)
	{
	case PropItem::PropType::CiTie:
		gameMap->addAutoCollectEffect(8.0f);
		break;
	case PropItem::PropType::BaGuaDun:
		gameMap->addInvincibleEffect(8.0f);
		break;
	case PropItem::PropType::FeiNiao:
		gameMap->addQuickFlying(8.0f);
		break;
	case PropItem::PropType::FeiXingGuai:
		gameMap->addFeiXingGuai();
		break;
	case PropItem::PropType::JiaSu:
		gameMap->addJiaSuEffect(8.0f);
		break;
	default:
		break;
	}
}