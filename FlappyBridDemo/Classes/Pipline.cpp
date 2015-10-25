#include "Pipline.h"

Vector<Pipline*> Pipline::piplineList =  Vector<Pipline*>();

Pipline* Pipline::create(const std::string & file)
{
	Pipline * pipline = new  Pipline();
	if (pipline && pipline->init())
	{
		pipline->initWithFile(file);
		pipline->autorelease();
		return pipline;
	}
	CC_SAFE_DELETE(pipline);
	return nullptr;
}
bool Pipline::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	scheduleUpdate();
	m_state = 0;
	return true;
}
void Pipline::setNextPosition()
{
	Vec2 currcertPosition = getPosition();
	auto moveTo = MoveTo::create(0.02, Vec3(currcertPosition.x - 2, currcertPosition.y, 0));
	runAction(moveTo);
}
void Pipline::setPhysicsConfiger()
{
	auto body = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	body->setDynamic(false);
	this->setPhysicsBody(body);
	body->setCategoryBitmask(0x01);
	body->setCollisionBitmask(0x01);
	body->setContactTestBitmask(0x01);
}

void Pipline::update(float dt)
{
	setNextPosition();
	if (checkWidthBorder(getPosition().x))
	{
	  distance = std::rand() % 50-20;
	  dy = std::rand() % 180 - 50;
	  setPiplineState(getPiplineState());
	}
}

void Pipline::pushbackToList()
{
	Pipline::piplineList.pushBack(this);
}

void Pipline::removeFromList()
{
	Pipline::piplineList.eraseObject(this);
}

bool Pipline::checkWidthBorder(float x)
{
	if (x<-50)
	{
		return true;
	}
	return false;
}

void Pipline::setPiplineState(int state)
{
	m_state = state;
	if (m_state == Pipline::PiplineState::Top)
	{
		setPosition(visibleSize.width + 400 + distance , visibleSize.height - dy);
	}
	else if (m_state == Pipline::PiplineState::Down)
	{
		setPosition(visibleSize.width + 400 , 0 - dy);
	}

}
int  Pipline::getPiplineState()
{
	return m_state;
}