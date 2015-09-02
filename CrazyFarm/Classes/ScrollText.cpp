#include "ScrollText.h"
#include "CallAndroidMethod.h"
#include "Chinese.h"
#include "GameState.h"
#include "GameData.h"

USING_NS_CC;
#define IF_RETURN(cont,p) if ((cont)){return (p);}
#define IF_RETURN_FALSE(cont) IF_RETURN(cont,false)
bool ScrollText::init() {
	bool ret = true;
	if (Node::init()) {
	    pMask = Sprite::create("hot_marquee_bg.png");
		marInfo = "";
		ishowDialog = false;
		_mLable = Label::create(ChineseWord("marquee"), "Arial-BoldMT", 16);
		_mLable->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		IF_RETURN_FALSE(!initClipper(pMask, _mLable));
		scheduleUpdate();
		setAutoScroll(true);
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(ScrollText::onTouchBegan,
				this);
		touchListener->onTouchMoved = CC_CALLBACK_2(ScrollText::onTouchMoved,
				this);
		touchListener->onTouchEnded = CC_CALLBACK_2(ScrollText::onTouchEnded,
				this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,
				this);
		return ret;
	}
	return ret;
}

void ScrollText::setpMaskString(std::string string) {
	_mLable = Label::createWithSystemFont(string, "Arial-BoldMT", 16);
}

bool ScrollText::initClipper(cocos2d::Sprite* pMask,
		cocos2d::Label* pMoveChild) {
	auto clipper = ClippingNode::create();
	IF_RETURN_FALSE(!clipper);
	IF_RETURN_FALSE(!pMask);
	setContentSize(pMask->getContentSize());
	IF_RETURN_FALSE(!pMask->getTexture());
	auto _clipperStencil = Sprite::createWithTexture(pMask->getTexture());
	IF_RETURN_FALSE(!_clipperStencil);
	_clipperStencil->retain();
	clipper->setAlphaThreshold(0.1f);
	clipper->setStencil(_clipperStencil);
	clipper->addChild(pMask);
	clipper->addChild(pMoveChild, 1);
	addChild(clipper);
	for (auto child : _mNodes) {
		IF_RETURN_FALSE(!child);
		clipper->addChild(child);
	}
	return true;
}

ScrollText::ScrollText() :
		_autoScroll(false) {
}

ScrollText::~ScrollText() {
	CC_SAFE_RELEASE(_mLable);
}

void ScrollText::update(float delta) {
	if (!_mLable) {
		return;
	}
	float currentX = _mLable->getPositionX();
	float contentX = getContentSize().width * (-1.0f);
	float lableX = _mLable->getContentSize().width * (-1.0f);

	if (_autoScroll) {
		if (_mLable->getPositionX() >= (lableX + contentX / 2))
			_mLable->setPositionX(_mLable->getPositionX() - 0.25f);
		else {
			_mLable->setPositionX(-contentX / 2);
		}

	} else {
		_mLable->setPositionX(contentX / 2);
	}
	if (GAMESTATE::getInstance()->getIsShowMarquee()) {
		marInfo = GAMESTATE::getInstance()->getShowMarqueeInfo();
		_mLable->setString(ChineseWord("marquee") + "  " + marInfo);
		GAMESTATE::getInstance()->setIsShowMarquee(false);
	}
}

void ScrollText::setAutoScroll(bool isScroll, bool byWidth/*=false*/) {
	if (!byWidth) {
		_autoScroll = isScroll;
	} else {
		_autoScroll =
				_mLable->getContentSize().width > getContentSize().width ?
						true : false;
	}
}

ScrollText* ScrollText::create(cocos2d::Sprite* pMask,
		cocos2d::Label* pMoveChild, cocos2d::Label* otherChild, ...) {
	auto *sTxt = new ScrollText();

	if (sTxt) {
		va_list lst;
		va_start(lst, otherChild);
		Node* pNow;
		pNow = otherChild;
		while (otherChild) {
			if (pNow) {
				sTxt->_mNodes.pushBack(pNow);
			pNow = va_arg(lst, Node*);
		} else
			break;
	}
	va_end(lst);
	if (sTxt->initWithDatas(pMask, pMoveChild)) {
		sTxt->autorelease();
		return sTxt;
	} else {
		delete sTxt;
		sTxt = NULL;
		return NULL;
	}
} else {
	delete sTxt;
	sTxt = NULL;
	return NULL;
}
}

bool ScrollText::initWithDatas(cocos2d::Sprite* pMask,
	cocos2d::Label* pMoveChild) {
bool ret = false;
if (Node::init()) {
	IF_RETURN_FALSE(!pMask);
	_mLable = pMoveChild;
	_mLable->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	initClipper(pMask, _mLable);
	scheduleUpdate();
	return true;
}
return ret;
}

bool ScrollText::onTouchBegan(Touch *touch, Event *event) {
if (pMask->getBoundingBox().containsPoint(touch->getLocation())) {} else {}
if (GAMEDATA::getInstance()->getScore() > 5 && !ishowDialog) {
	CallAndroidMethod::getInstance()->showHotDialog();
	ishowDialog = true;
}
return false;

}

void ScrollText::onTouchMoved(Touch *touch, Event *event) {


}

void ScrollText::onTouchEnded(Touch *touch, Event *event) {

}

long ScrollText::getCurrentTime() {
struct timeval tv;
gettimeofday(&tv, NULL);
return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

