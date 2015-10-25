#include "Ball.h"
using namespace cocos2d;

bool Ball::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	ballState = this->getBallState();
	ballSpeed = GameData::getInstance()->getBallSpeed();
	scheduleUpdate();
	return true;
}

Ball *Ball::create(const std::string & filename)
{
	Ball * ball = new (std::nothrow) Ball();
	if (ball && ball->initWithFile(filename))
	{
		ball->autorelease();
		return ball;
	}
	CC_SAFE_DELETE(ball);
	return nullptr;
}


void Ball::update(float dt)
{

	setNextPosition();
	Vec2 currcertPosition = getPosition();
	//log("ball position is %f %f",currcertPosition.x, currcertPosition.y);
	if (checkWidthBorder(currcertPosition.x))
	{
		ballState = getBallState();
		//log("ballState is >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%d", ballState);
		setVisible(true);
		addBall();
	}
	if (checkHeightBorder(currcertPosition.y))
	{
		ballState = getBallState();
		//log("ballState is >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%d", ballState);
		setVisible(true);
		addBall();
	}
}

int Ball::getBallState()
{
	std::srand(time(NULL));
	ballState = std::rand() % 4;;
	return ballState;
}

void Ball::addBall()
{
	switch (ballState)
	{
	case Ball::BallState::Top:
		setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
		break;
	case Ball::BallState::Buttom:
		setPosition(Vec2(visibleSize.width / 2, 0));
		break;
	case Ball::BallState::Left:
		setPosition(Vec2(visibleSize.width, visibleSize.height / 2));
		break;
	case Ball::BallState::Right:
		this->setPosition(Vec2(0, visibleSize.height / 2));
		break;
	default:
		break;
	}
}
void Ball::setNextPosition()
{
    ballPosition = getPosition();
	switch (ballState)
	{
	case Ball::BallState::Top:
		ballPosition.y -= ballSpeed;
		this->setPosition(ballPosition);
		break;
	case Ball::BallState::Buttom:
		ballPosition.y += ballSpeed;
		this->setPosition(ballPosition);
		break;
	case Ball::BallState::Left:
		ballPosition.x -= ballSpeed;
		this->setPosition(ballPosition);
		break;
	case Ball::BallState::Right:
		ballPosition.x += ballSpeed;
		this->setPosition(ballPosition);
		break;
	default:
		break;
	}
}
void Ball::setBallSpeed(int speed)
{
	ballSpeed = speed;
}

bool Ball::checkWidthBorder(float x)
{
	if (x<0 || x>visibleSize.width)
	{
		return true;
	}
	return false;

}
bool Ball::checkHeightBorder(float y)
{
	if (y<0 || y>visibleSize.height)
	{
		return true;
	}
	return false;
}