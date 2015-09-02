#ifndef  __TKP_SHIELD_SOLDIER_H__
#define __TKP_SHIELD_SOLDIER_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "GameObject.h"

class ShieldSoldier : public GameObject
{
public:
	CREATE_FUNC(ShieldSoldier);

	virtual void update(float delta);

	void checkAttack();
	void checkInvincible();

	virtual void die();

	bool checkBones();

protected:
	ShieldSoldier();
	virtual ~ShieldSoldier();
	CC_DISALLOW_COPY_AND_ASSIGN(ShieldSoldier);

	virtual bool init();

};



#endif // __TKP_SHIELD_SOLDIER_H__