#ifndef __TKP_SCENE_BASE_H__
#define __TKP_SCENE_BASE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"

class SceneBase : public cocos2d::Scene, public cocostudio::WidgetCallBackHandlerProtocol
{
public:
	virtual cocos2d::ui::Widget::ccWidgetTouchCallback onLocateTouchCallback(const std::string &callbackName);
	virtual void initAfterCreate();

protected:
	SceneBase();
	virtual ~SceneBase();
	CC_DISALLOW_COPY_AND_ASSIGN(SceneBase);

	virtual bool init() override;
	virtual void initCallbackMap();
	virtual void onKeyBackReleased();

	void addKeyBackReleasedListener();
	void registerCallback(const std::string &name, cocos2d::ui::Widget::ccWidgetTouchCallback callback);

private:
	std::map<std::string, cocos2d::ui::Widget::ccWidgetTouchCallback> _callbackMap;
};

#endif // __TKP_SCENE_BASE_H__