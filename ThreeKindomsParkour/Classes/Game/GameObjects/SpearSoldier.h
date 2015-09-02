#ifndef __TKP_SPEAR_SOLDIER_H__
#define __TKP_SPEAR_SOLDIER_H__


#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"

#include "GameObject.h"

class SpearSoldier : public GameObject
{
public:
	CREATE_FUNC(SpearSoldier);

	virtual void update(float delta);

	void check();
	void checkHurt();
	void checkAttack();
	void checkInvincible();

	virtual void die();

protected:
	SpearSoldier();
	virtual ~SpearSoldier();
	CC_DISALLOW_COPY_AND_ASSIGN(SpearSoldier);

	virtual bool init();

public:

	bool _isAttacking;
};



#endif // __TKP_SPEAR_SOLDIER_H__