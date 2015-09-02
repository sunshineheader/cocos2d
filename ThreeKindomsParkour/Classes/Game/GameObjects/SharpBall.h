#ifndef  __TKP_SHARP_BALL_H__
#define __TKP_SHARP_BALL_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "GameObject.h"

class SharpBall : public GameObject
{
public:
    CREATE_FUNC(SharpBall);

	virtual void update(float delta);

protected:
    SharpBall();
    virtual ~SharpBall();
    CC_DISALLOW_COPY_AND_ASSIGN(SharpBall);

    virtual bool init();


};



#endif // __TKP_SHARP_BALL_H__