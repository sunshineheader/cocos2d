#ifndef __TKP_FIRE_BALL_H__
#define __TKP_FIRE_BALL_H__


#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"

#include "GameObject.h"

class FireBall : public GameObject
{
public:
	CREATE_FUNC(FireBall);

	virtual void update(float delta);

protected:
	FireBall();
	virtual ~FireBall();
	CC_DISALLOW_COPY_AND_ASSIGN(FireBall);

	virtual bool init();

};



#endif // __TKP_FIRE_BALL_H__