#ifndef __TKP_SCENE_LEVEL_SELECT_H__
#define __TKP_SCENE_LEVEL_SELECT_H__

#include "SceneBase.h"
#include "cocos2d.h"


class SceneLevelSelect : public SceneBase
{
public:
	CREATE_FUNC(SceneLevelSelect);

	virtual void initAfterCreate();
	virtual void update(float delta) override;

protected:
	SceneLevelSelect();
	~SceneLevelSelect();
	CC_DISALLOW_COPY_AND_ASSIGN(SceneLevelSelect);

	virtual bool init() override;
	virtual void initCallbackMap() override;
	virtual void onKeyBackReleased() override;

protected:
	void onBackMain(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onForwardQuest(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void onStartGoldCopy(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void onShowWenChenSelect(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onShowZhuGongSelect(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onShowWuJiangSelect(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

private:
	void initScroll();
	void initQuest();
};



#endif // __TKP_SCENE_LEVEL_SELECT_H__