#include "Brid.h"

Brid *Brid::create()
{
	Brid  * brid = new Brid();
	if (brid && brid->init())
	{
		brid->autorelease();
		return brid;
	}
	CC_SAFE_DELETE(brid);
	return nullptr;
}

bool Brid::init()
{
	if (!Node::init())
	{
		return false;
	}
	scheduleUpdate();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	initBridAmination();
	return true;
}

void Brid::initBridAmination()
{
	const int frames = 3;
	SpriteFrame * runFrames = nullptr;
	Vector<SpriteFrame*>runFramesVector;
	for (size_t i = 0; i < frames; i++)
	{
		runFrames = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("bird_blue_%d.png", i));
		runFramesVector.pushBack(runFrames);
	}
	Animation * animation = Animation::createWithSpriteFrames(runFramesVector, 0.06f);
	runAnimate = RepeatForever::create(Animate::create(animation));
	runSprite = Sprite::createWithSpriteFrameName("bird_blue_0.png");
	runSprite->runAction(runAnimate);
	addChild(runSprite);
}
void Brid::stopBridAmination()
{
	runSprite->stopAction(runAnimate);
}


void Brid::setPhysicsConfiger()
{
	runSprite->setAnchorPoint(Vec2(0.0f,0.0f));
	setBridContentSize();
	auto bridBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	bridBody->setCategoryBitmask(0x01);
	bridBody->setCollisionBitmask(0x01);
	bridBody->setContactTestBitmask(0x01);
	this->setPhysicsBody(bridBody);
}


void Brid::setBridContentSize()
{
	setContentSize(runSprite->getContentSize());
}

void Brid::update(float dt)
{

}