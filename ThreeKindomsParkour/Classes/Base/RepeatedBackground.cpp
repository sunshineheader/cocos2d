#include "RepeatedBackground.h"

USING_NS_CC;
using namespace std;

RepeatedBackground* RepeatedBackground::create(const string &name)
{
	RepeatedBackground *bg = new (std::nothrow) RepeatedBackground(name);
	if (bg && bg->init())
	{
		bg->autorelease();
		return bg;
	}
	CC_SAFE_DELETE(bg);
	return nullptr;
}

RepeatedBackground::RepeatedBackground(const string &name)
: _backgroundName(name)
, _lastPositionX(0.0f)
, _backgroundWidth(0.0f)
, _previousPositionX(0.0f)
{
	_screenWidth = Director::getInstance()->getOpenGLView()->getVisibleSize().width;
}

RepeatedBackground::~RepeatedBackground()
{
}

bool RepeatedBackground::init()
{
	do {
		addBackground();
	} while (_lastPositionX <= _screenWidth);
	addBackground();

	scheduleUpdate();

	return true;
}

void RepeatedBackground::addBackground()
{
	auto sprite = Sprite::create(_backgroundName);
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPositionX(_lastPositionX);
	_backgroundWidth = sprite->getContentSize().width;
	addChild(sprite);
	_lastPositionX += _backgroundWidth;
}

void RepeatedBackground::update(float delta)
{
	if (fabs(_previousPositionX - getPositionX()) >= _backgroundWidth)
	{
		addBackground();
		//getChildren().at(0)->removeFromParent();
		_previousPositionX = getPositionX();
	}
}