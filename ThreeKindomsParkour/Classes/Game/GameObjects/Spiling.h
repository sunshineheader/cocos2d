#ifndef __TKP_SPILING_H__
#define __TKP_SPILING_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "GameObject.h"

class Spiling : public GameObject
{
public:
	CREATE_FUNC(Spiling);

	virtual void update(float delta);

	void checkHurt();
	void checkAttack();
	void checkInvincible();

	virtual void die();

protected:
	Spiling();
	virtual ~Spiling();
	CC_DISALLOW_COPY_AND_ASSIGN(Spiling);

	virtual bool init();

};



#endif // __TKP_SPILING_H__