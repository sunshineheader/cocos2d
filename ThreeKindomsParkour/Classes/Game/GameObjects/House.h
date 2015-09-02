#ifndef __TKP_HOUSE_H__
#define __TKP_HOUSE_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "GameObject.h"

class House : public GameObject
{
public:
	CREATE_FUNC(House);

	virtual void update(float delta);

	virtual void die();

	void checkJump();
	void checkTouch();

	void checkAttack(Math::Polygon &region, const std::string &name);
	void checkAttack();

protected:
	House();
	virtual ~House();
	CC_DISALLOW_COPY_AND_ASSIGN(House);

	virtual bool init();

	bool _isAttacking;
};



#endif // __TKP_HOUSE_H__