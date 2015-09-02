#ifndef __TKP_SCENE_LOADING_H__
#define __TKP_SCENE_LOADING_H__

#include "SceneBase.h"
#include "cocos2d.h"
#include "ui\CocosGUI.h"

class SceneLoading : public SceneBase
{
public:
	CREATE_FUNC(SceneLoading);

	virtual void update(float delta) override;
	virtual void initAfterCreate() override;

protected:
	SceneLoading();
	~SceneLoading();
	CC_DISALLOW_COPY_AND_ASSIGN(SceneLoading);

	virtual bool init() override;
	virtual void initCallbackMap() override;
	virtual void onKeyBackReleased() override;

	void updateProgress(float percent);
	std::string percentString(float percent) const;

private:
	cocos2d::ui::LoadingBar *_progressbar;
	cocos2d::Node			*_light;
	cocos2d::ui::Text		*_percent;
	float _length;
};



#endif // __TKP_SCENE_LOADING_H__