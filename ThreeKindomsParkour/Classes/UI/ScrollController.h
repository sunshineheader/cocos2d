#ifndef __TKP_SCROLL_CONTROLLER_H__
#define __TKP_SCROLL_CONTROLLER_H__

#include "cocos2d.h"

class ScrollController : public cocos2d::Node
{
public:
	static ScrollController* create(cocos2d::Node *scroll);

	virtual void update(float delta) override;

	void selectLevel(int index);

protected:
	ScrollController(cocos2d::Node *scroll);
	~ScrollController();
	CC_DISALLOW_COPY_AND_ASSIGN(ScrollController);

	virtual bool init();

private:
	void setFootprintLocked(cocos2d::Node *footprint, bool locked);
	void selectFootprint(cocos2d::Node *footprint);

private:
	cocos2d::Node *_scroll;
	cocos2d::Node *_scrollContainer;
	cocos2d::Node *_scrollRight;
	cocos2d::Node *_routeCover;
};

#endif // __TKP_SCROLL_CONTROLLER_H__