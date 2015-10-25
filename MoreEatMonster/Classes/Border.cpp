#include "Border.h"
using namespace cocos2d;

bool Border::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	return true;
}
void Border::addBorder()
{
	if (Border::BorderState::Horizontal)
	{
	}
	else if (Border::BorderState::Horizontal)
	{
	}
}

