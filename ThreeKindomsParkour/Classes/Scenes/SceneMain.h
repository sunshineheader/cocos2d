#ifndef __TKP_SCENE_MAIN_H__
#define __TKP_SCENE_MAIN_H__

#include "SceneBase.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class SceneMain : public SceneBase
{
public:
	CREATE_FUNC(SceneMain);

	virtual void initAfterCreate();

	virtual void update(float delta) override;

protected:
	SceneMain();
	~SceneMain();
	CC_DISALLOW_COPY_AND_ASSIGN(SceneMain);

	virtual bool init() override;
	virtual void initCallbackMap() override;
	virtual void onKeyBackReleased() override;

protected:
	void onExitConfirm(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onExitCancel(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void onShowSignDialog(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onShowActivityDialog(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onStartStageMode(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onStartClassicMode(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void onShowWenChenSelect(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onShowZhuGongSelect(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onShowWuJiangSelect(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	cocostudio::Bone *_bone;
};



#endif // __TKP_SCENE_MAIN_H__