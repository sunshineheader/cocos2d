#ifndef __TKP_SCENE_PROP_SELECT_H__
#define __TKP_SCENE_PROP_SELECT_H__

#include "SceneBase.h"
#include "cocos2d.h"


class ScenePropSelect : public SceneBase
{
public:
	CREATE_FUNC(ScenePropSelect);

	virtual void initAfterCreate() override;

protected:
	ScenePropSelect();
	~ScenePropSelect();
	CC_DISALLOW_COPY_AND_ASSIGN(ScenePropSelect);

	virtual bool init() override;
	virtual void initCallbackMap() override;
	virtual void onKeyBackReleased() override;
};



#endif // __TKP_SCENE_PROP_SELECT_H__