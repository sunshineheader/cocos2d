#ifndef __TKP_SCENE_CHARACTER_SELECT_H__
#define __TKP_SCENE_CHARACTER_SELECT_H__

#include "SceneBase.h"
#include "cocos2d.h"


class SceneCharacterSelect : public SceneBase
{
public:
	CREATE_FUNC(SceneCharacterSelect);

	virtual void initAfterCreate() override;

protected:
	SceneCharacterSelect();
	~SceneCharacterSelect();
	CC_DISALLOW_COPY_AND_ASSIGN(SceneCharacterSelect);

	virtual bool init() override;
	virtual void initCallbackMap() override;
	virtual void onKeyBackReleased() override;
};



#endif // __TKP_SCENE_CHARACTER_SELECT_H__