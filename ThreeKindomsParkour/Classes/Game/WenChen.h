#ifndef  __TKP_WEN_CHEN_H__
#define __TKP_WEN_CHEN_H__

#include "cocos2d.h"

class WenChen : public cocos2d::Node
{
public:
	CREATE_FUNC(WenChen);

	virtual void update(float delta);

	void setInitalPosition(const cocos2d::Vec2 &position);

protected:
	WenChen();
	virtual ~WenChen();
	CC_DISALLOW_COPY_AND_ASSIGN(WenChen);

	virtual bool init();

private:
	cocos2d::Vec2 _initialPosition;
};



#endif // __TKP_WEN_CHEN_H__