#include "Ball.h"

bool Ball::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	scheduleUpdate();
	state = getBallState();
	setBallState();
	return true;
}


void Ball::setPhysicsConfiger()
{
	auto body = PhysicsBody::createBox(getContentSize(),PHYSICSBODY_MATERIAL_DEFAULT);
	body->setDynamic(false);
	body->setCategoryBitmask(0x01);
	body->setCollisionBitmask(0x01);
	body->setContactTestBitmask(0x01);
	setPhysicsBody(body);
}

bool Ball::checkWidthBorder(float x)
{
	if (x<0 || x>visibleSize.width)
	{
		return true;
	}
	return false;
}
void Ball::setBallState()
{
	if (state == Ball::BallState::Right)
	{
		setPosition(visibleSize.width,visibleSize.height/2);
	}
	else
	{
		setPosition(0, visibleSize.height / 2);
	}
}

int Ball::getBallState()
{
	return (std::rand() % 2);

}
void  Ball:: setNextPosition()
{
	Vec2 currcertPosition=getPosition();
	if (state==Ball::BallState::Right)
	{
		auto moveTo = MoveTo::create(0.02, Vec3(currcertPosition.x - 2, currcertPosition.y, 0));
		runAction(moveTo);
	}
	else
	{
		auto moveTo = MoveTo::create(0.02, Vec3(currcertPosition.x + 2, currcertPosition.y, 0));
		runAction(moveTo);
	}

}
void Ball::update(float dt)
{
	setNextPosition();
	if (checkWidthBorder(getPosition().x))
	{
		state=getBallState();
		setBallState();
	}
}