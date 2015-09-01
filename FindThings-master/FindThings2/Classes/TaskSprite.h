#ifndef __TASK_SPRITE_H__
#define __TASK_SPRITE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d::ui; 
using namespace cocos2d;
using namespace std;

class TaskSprite : public Sprite{
public:
	virtual bool init();
	void showTaskSprite(string titleName,int tar_num);
	void updateCurNum(int cur_num);
	CREATE_FUNC(TaskSprite);
private:
	ui::Scale9Sprite* task_bg;
	Sprite* title;
	Sprite* curNum;
	Sprite* tarNum;
	Sprite* split;
	int cur_num;
	int tar_num;
};
#endif
