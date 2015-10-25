#include "Monster.h"
using namespace cocos2d;

bool Monnster::init()
{
	if (!Node::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	runSprite = nullptr;
	runAnimate = nullptr;
	scheduleUpdate();
	return true;
}

void Monnster::addMonsterAmination()
{
	const size_t frames = 2;
	SpriteFrame * spriteFrame = nullptr;
	Vector<SpriteFrame*>spriteFrameVector;
	for (size_t i = 0; i < frames; i++)
	{
		spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("monster_%d.png", (i+1)));
		spriteFrameVector.pushBack(spriteFrame);
	}
	Animation * animation = Animation::createWithSpriteFrames(spriteFrameVector, 0.06f,1);
	runAnimate = RepeatForever::create(Animate::create(animation));
	runSprite = Sprite::createWithSpriteFrameName("monster_1.png");
	//runSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	runSprite->runAction(runAnimate);
	addChild(runSprite);

}
void Monnster::stopMonsterAmination()
{
	runSprite->stopAction(runAnimate);
}
void Monnster::remuseMonsterAmination()
{
	
}
void Monnster::update(float dt)
{

}
