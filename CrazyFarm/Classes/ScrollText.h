#ifndef _SCROLLTEXT_H_
#define _SCROLLTEXT_H_
#include "cocos2d.h"

USING_NS_CC;
class ScrollText: public cocos2d::Node {
public:
	/**
	 @pragma  pMask 需要用于遮罩的精灵
	 @pragma  pMoveChild 需要移动的Node
	 @pragma  otherChid 其他需要显示的Node
	 */
	static ScrollText* create(cocos2d::Sprite* pMask, cocos2d::Label* pMoveChild,
			cocos2d::Label* otherChild, ...);
	/**
	 @pragma  isScroll 设置是否需要自动滚动
	 @pragma  byWidth 设置是否需要根据长度来滚动
	 PS：如果按照长度来设置，则长度小于遮罩长度的将不予滚动
	 */
	void setAutoScroll(bool isScroll, bool byWidth = false);
	CREATE_FUNC(ScrollText);
    CC_CONSTRUCTOR_ACCESS:
	ScrollText();
	virtual ~ScrollText();
	virtual bool init();
	virtual bool initWithDatas(cocos2d::Sprite* pMask,
		cocos2d::Label* pMoveChild);
	bool initClipper(cocos2d::Sprite* pMask, cocos2d::Label* pMoveChild);
	void update(float delta);
	void setpMaskString(std::string string);
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	long getCurrentTime();

private:
	cocos2d::Label* _mLable;
	cocos2d::Sprite* pMask;
	cocos2d::Vector<Node*> _mNodes;
	bool _autoScroll;
	std::string marInfo;
	bool ishowDialog;
};
#endif
