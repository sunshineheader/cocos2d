#include "ScrollController.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;

ScrollController* ScrollController::create(cocos2d::Node *scroll)
{
	ScrollController *sc = new (std::nothrow) ScrollController(scroll);
	if (sc && sc->init())
	{
		sc->autorelease();
		return sc;
	}
	CC_SAFE_DELETE(sc);
	return nullptr;
}

ScrollController::ScrollController(cocos2d::Node *scroll)
: _scroll(scroll)
{
}

ScrollController::~ScrollController()
{
}

bool ScrollController::init()
{
	_scrollContainer = _scroll->getChildByName("Container");
	_scrollRight = _scroll->getChildByName("ScrollRight");
	_routeCover = _scrollContainer->getChildByName("RouteCover");

	_scrollContainer->setContentSize(Size(50, 171));
	_scrollRight->setPositionX(_scrollContainer->getPositionX() + 50 - _scrollRight->getContentSize().width);
	_routeCover->setContentSize(Size(50, 171));

	auto footprints = _scrollContainer->getChildByName("Footprints")->getChildren();
	for (size_t i = 0; i < footprints.size(); ++i) 
	{
		auto levelNumber = String::createWithFormat("%d", i + 1)->getCString();
		auto lockedNumber = footprints.at(i)->getChildByName("Flag_Locked")->getChildByName("Number");
		auto unlockedNumber = footprints.at(i)->getChildByName("Flag_Unlocked")->getChildByName("Number");
		dynamic_cast<TextBMFont*>(lockedNumber)->setString(levelNumber);
		dynamic_cast<TextBMFont*>(unlockedNumber)->setString(levelNumber);
	}

	scheduleUpdate();
	return true;
}

void ScrollController::update(float delta)
{
	static float speed = 360;

	auto size = _scrollContainer->getContentSize();
	size.width += speed * delta;
	if (size.width < 900)
		_routeCover->setContentSize(size);
	_scrollContainer->setContentSize(size);

	_scrollRight->setPositionX(_scrollContainer->getPositionX() + size.width - _scrollRight->getContentSize().width);
}

void ScrollController::selectLevel(int index)
{
	index -= 1;

	auto footprints = _scrollContainer->getChildByName("Footprints")->getChildren();
	for (size_t i = 0; i < footprints.size(); ++i)
	{
		auto footprint = footprints.at(i);
		setFootprintLocked(footprint, i > index);
	}
	selectFootprint(footprints.at(index));
}

void ScrollController::setFootprintLocked(cocos2d::Node *footprint, bool locked)
{
	footprint->getChildByName("Footprint_Locked")->setVisible(locked);
	footprint->getChildByName("Footprint_Unlocked")->setVisible(!locked);
	footprint->getChildByName("Flag_Locked")->setVisible(locked);
	footprint->getChildByName("Flag_Unlocked")->setVisible(!locked);
}

void ScrollController::selectFootprint(cocos2d::Node *footprint)
{
	footprint->getChildByName("HeadPortrait")->setVisible(true);
	footprint->getChildByName("Aperture")->setVisible(true);
	footprint->getChildByName("Nameplate")->setVisible(true);
}