#ifndef  __TKP_BLOCK_H__
#define __TKP_BLOCK_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "GameObject.h"

class Block : public GameObject
{
public:
	CREATE_FUNC(Block);

	virtual void update(float delta);

protected:
	Block();
	virtual ~Block();
	CC_DISALLOW_COPY_AND_ASSIGN(Block);

	virtual bool init();

};



#endif // __TKP_BLOCK_H__