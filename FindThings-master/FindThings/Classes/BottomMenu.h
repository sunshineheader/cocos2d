#ifndef _BOTTOMMENU_H_
#define _BOTTOMMENU_H_
#include <string>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d::ui;
using namespace cocos2d::extension;
using namespace cocos2d;

#define TOTALTIME (60)
#define PROPPLUSTIME (30)

class BottomMenu : public Node {
public:
	static BottomMenu* getInstance();
	static bool clickFindBtn;
	static bool clickTimeBtn;
	virtual bool init();
	void pauseGame();
	void updateTime(float dt);
    void initGameTime();
	void updateScore();
	void plusGameTime(int time);
	void findTouchEvent(Ref* pSender,Widget::TouchEventType type);
	void timeTouchEvent(Ref* pSender,Widget::TouchEventType type);
	void updatePropNum();
private:
	LabelAtlas* record;//玩家记录
	LabelAtlas* curScore;//本局得分
	LabelAtlas* gameTime;//游戏时间
	LabelAtlas* find_prop_num;
	LabelAtlas* time_prop_num;
	int playTime;
	static BottomMenu* instance;
};
#endif