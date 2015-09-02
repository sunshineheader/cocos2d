#include "Player.h"
#include "GameMap.h"
#include "Utils/Properties.h"

#include "cocostudio\CocoStudio.h"

#include <list>

USING_NS_CC;
using namespace cocostudio;
using namespace std;

static const char *s_kJumpName[] = {
	"Jump_1", "Jump_2", "Jump_3"
};
static bool s_isInit = false;
static float s_Damping;
static float s_Gravity;
static float s_JumpSpeed[3];

static float s_moveSpeed = 120;
static float s_quickMoveSpeed = 500;

Player::Player()
: _player(nullptr)
, _animation(nullptr)
, _state(State::Falling)
, _isGrounded(true)
, _numJump(0)
, _maxJump(3)
, _score(0)
, _isDead(false)
, _initPositionX(0.0f)
{
}

Player::~Player()
{
}

bool Player::init()
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
	schedule([](float delta)
	{
		Properties p("Data/Config.json");
		s_Damping = p.getDoubleForKey("Damping", 0.25);
		s_Gravity = p.getDoubleForKey("Gravity", -2.5);
		s_JumpSpeed[0] = p.getDoubleForKey("FirstJumpSpeed", 60);
		s_JumpSpeed[1] = p.getDoubleForKey("SecondJumpSpeed", 40);
		s_JumpSpeed[2] = p.getDoubleForKey("ThirdJumpSpeed", 30);
		s_moveSpeed = p.getDoubleForKey("InitalMoveSpeed", 120);
	}, 1, "aa");


	ArmatureDataManager::getInstance()->addArmatureFileInfo("Test/ZhuGong.ExportJson");
	_player = Armature::create("ZhuGong");
	_animation = _player->getAnimation();
	_animation->play("Run");

	addChild(_player);
	scheduleUpdate();

	setContentSize(Size(100, 100));

	return true;
}

void Player::update(float delta)
{
	if (getPositionX() + getParent()->getPositionX() < _initPositionX)
	{
		_velocity.x = s_quickMoveSpeed;
	}
	else
	{
		_velocity.x = s_moveSpeed;
	}

	_velocity.y += s_Gravity;
	_velocity *= delta;

	if (_state == State::Jumping && _velocity.y < 1) {
		_state = State::Falling;
		_animation->stop();
		_animation->play("Fall");
	}

	checkWithStars();
	checkWithBlocks();
	checkVerticalCollisionWithPlatforms();
	checkHorizoztalCollisionWithPlatforms();

	setPosition(getPosition() + _velocity);
	_velocity *= 1 / delta;
	
	if (getPositionY() < -36) {
		die();
	}
}

void Player::checkVerticalCollisionWithPlatforms()
{
	if (_state == State::Jumping)
		return;

	Rect playerRect;
	Rect rect;
	playerRect.size = getContentSize();
	playerRect.origin = getPosition();
	playerRect.origin.x -= playerRect.size.width / 2;

	auto terrains = _gameMap->getTerrains();
	for (auto terrain : terrains) 
	{
		auto terrainPosition = terrain->getPosition();
		auto platforms = terrain->getChildByName("Platforms");

		for (auto platform : platforms->getChildren())
		{
			auto platformPosition = platform->getPosition();
			auto origin = terrainPosition + platformPosition;

			auto collisionY = platform->getChildByName("CollisionY_Down");
			rect.origin = origin + collisionY->getPosition();
			rect.size = collisionY->getContentSize();

			if (playerRect.intersectsRect(rect)) {
				if (_state != State::Running) {
					_state = State::Running;
					_animation->stop();
					_animation->play("Run");
				}

				_velocity.y = 0;
				_numJump = 0;
				return;
			}
		}
	}
}

void Player::checkWithStars()
{
	Rect playerRect;
	Rect rect;
	playerRect.size = getContentSize();
	playerRect.origin = getPosition();
	playerRect.origin.x -= playerRect.size.width / 2;

	auto terrains = _gameMap->getTerrains();
	for (auto terrain : terrains)
	{
		auto terrainPosition = terrain->getPosition();
		auto platforms = terrain->getChildByName("Platforms");

		auto stars = terrain->getChildByName("Stars");
		if (stars != nullptr) {
			for (auto star : stars->getChildren()) {
				if (star->getNumberOfRunningActions() > 0)
					continue;

				Rect rect;
				auto position = star->getPosition();
				auto size = star->getContentSize();
				auto anchor = star->getAnchorPoint();
				rect.origin.x = terrainPosition.x + position.x - size.width * anchor.x;
				rect.origin.y = terrainPosition.y + position.y - size.height * anchor.y;
				rect.size = size;
				if (playerRect.intersectsRect(rect)) {
					star->runAction(Sequence::createWithTwoActions(ScaleTo::create(0.25f, 0.0f),
						Hide::create()));
					_score += 50;
				}
			}
		}
	}
}

void Player::checkHorizoztalCollisionWithPlatforms()
{
	if (_state == State::Jumping)
		return;

	Rect playerRect;
	Rect rect;
	playerRect.size = getContentSize();
	playerRect.origin = getPosition();
	playerRect.origin.x -= playerRect.size.width / 2;

	auto terrains = _gameMap->getTerrains();
	for (auto terrain : terrains)
	{
		auto terrainPosition = terrain->getPosition();
		auto platforms = terrain->getChildByName("Platforms");

		for (auto platform : platforms->getChildren())
		{
			auto platformPosition = platform->getPosition();
			auto origin = terrainPosition + platformPosition;

			auto collisionX = platform->getChildByName("CollisionX");
			if (collisionX == nullptr)
				continue;

			rect.origin = origin + collisionX->getPosition();
			rect.size = collisionX->getContentSize();
			if (playerRect.intersectsRect(rect)) {
				_velocity.x = 0;
				return;
			}
		}
	}
}

void Player::checkWithBlocks()
{
	Rect playerRect;
	playerRect.size = getContentSize();
	playerRect.origin = getPosition();
	playerRect.origin.x -= playerRect.size.width / 2;

	auto terrains = _gameMap->getTerrains();
	for (auto terrain : terrains) {
		auto terrainPosition = terrain->getPosition();
		auto blocks = terrain->getChildByName("Blocks");
		if (blocks != nullptr) {
			for (auto block : blocks->getChildren()) {
				if (!block->isVisible())
					continue;

				Rect rect;
				auto position = block->getPosition();
				auto size = block->getContentSize();
				auto anchor = block->getAnchorPoint();

				size.width *= 0.5f;
				size.height *= 0.5f;

				rect.origin.x = terrainPosition.x + position.x - size.width * anchor.x;
				rect.origin.y = terrainPosition.y + position.y - size.height * anchor.y;
				rect.size = size;
				if (playerRect.intersectsRect(rect)) {
					die();
					unscheduleUpdate();
					return;
				}
			}
		}
	}
}

void Player::check()
{
	if (_state == State::Jumping)
		return;

	Rect playerRect;
	playerRect.size = getContentSize();
	playerRect.origin = getPosition();
	playerRect.origin.x -= playerRect.size.width / 2;
		
		auto terrains = _gameMap->getTerrains();
		for (auto terrain : terrains) {
			auto terrainPosition = terrain->getPosition();
			auto platforms = terrain->getChildByName("Platforms");

			auto stars = terrain->getChildByName("Stars");
			if (stars != nullptr) {
				for (auto star : stars->getChildren()) {
					if (star->getNumberOfRunningActions() > 0)
						continue;

					Rect rect;
					auto position = star->getPosition();
					auto size = star->getContentSize();
					auto anchor = star->getAnchorPoint();
					rect.origin.x = terrainPosition.x + position.x - size.width * anchor.x;
					rect.origin.y = terrainPosition.y + position.y - size.height * anchor.y;
					rect.size = size;
					if (playerRect.intersectsRect(rect)) {
						star->runAction(Sequence::createWithTwoActions(ScaleTo::create(0.25f, 0.0f),
							Hide::create()));
						_score += 50;
					}
				}
			}

			auto blocks = terrain->getChildByName("Blocks");
			if (blocks != nullptr) {
				for (auto block : blocks->getChildren()) {
					Rect rect;
					auto position = block->getPosition();
					auto size = block->getContentSize();
					auto anchor = block->getAnchorPoint();

					size.width *= 0.5f;
					size.height *= 0.5f;

					rect.origin.x = terrainPosition.x + position.x - size.width * anchor.x;
					rect.origin.y = terrainPosition.y + position.y - size.height * anchor.y;
					rect.size = size;
					if (playerRect.intersectsRect(rect)) {
						die();
						unscheduleUpdate();
						return;
					}
				}
			}

			bool isYBlock = false;
			float y = _velocity.y;
			for (auto platform : platforms->getChildren()) {
				if (isYBlock)
					break;

				auto platformPosition = platform->getPosition();
				for (auto node : platform->getChildren()) {
					Rect rect;
					rect.origin = node->getPosition() + terrainPosition + platformPosition;
					rect.size = node->getContentSize();
					rect.size.height -= 34;
					if (playerRect.intersectsRect(rect)) {

						if (_state != State::Running) {
							_state = State::Running;
							_animation->stop();
							_animation->play("Run");
						}

						if (_state == State::Running)
							_velocity.y = 0;
						_numJump = 0;

						isYBlock = true;
						break;
					}
				}
			}

			bool isXBlock = false;
			for (auto platform : platforms->getChildren()) {
				auto platformPosition = platform->getPosition();
				if (isXBlock)
					break;
				for (auto node : platform->getChildren()) {
					

					Rect rect;
					rect.origin = node->getPosition() + terrainPosition + platformPosition;
					rect.size = node->getContentSize();
					rect.size.width = 1;
					rect.size.height -= 34;
					rect.origin.x += 1;
					if (playerRect.intersectsRect(rect)
						&& (node->getName() == "Left_Upper" || node->getName() == "Left_Lower")) {
						_velocity.x = 0;
						_velocity.y = y;
						isXBlock = true;
						break;
					}
				}
			}
		}
	
}

void Player::jump()
{
	if (_numJump >= _maxJump)
		return;

	_state = State::Jumping;
	_animation->stop();
	_animation->play(s_kJumpName[_numJump]);
	_velocity.y = s_JumpSpeed[_numJump];
	_numJump += 1;
}

void Player::setGameMap(GameMap *gameMap)
{
	_gameMap = gameMap;
}

int Player::getScore() const
{
	return _score;
}

void Player::die()
{
	_animation->stop();
	_isDead = true;
}

bool Player::isDead() const
{
	return _isDead;
}

void Player::setInitPositionX(float x)
{
	_initPositionX = x;
}

float Player::getInitPositionX() const
{
	return _initPositionX;
}

