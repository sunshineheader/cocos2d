#ifndef _TASKMENU_H_
#define _TASKMENU_H_
#include <string>
#include "TaskInfo.h"
#include "cocos2d.h"
#include "TaskSprite.h"

using namespace cocos2d;

class TaskMenu : public Node {
public:
	static TaskMenu* getInstance();
	void refreshTask(TaskInfo* task);
	void showFinishTask(TaskInfo* task);
	virtual bool init();
	void gamePause();
	void updateFirstTask();
	void updateSecondTask();
	void updateThridTask();
    void cleanTaskMenu();
	TaskInfo* createTask();
	TaskInfo* createGuideTask();
	void showTaskPad(TaskInfo* info);//显示任务信息板
	void addTimeAnim();
	void payLevel();
	bool checkTask(TaskInfo* info);
private :
	TaskSprite* task1;
	TaskSprite* task2;
	TaskSprite* task3;
private:
	static TaskMenu* instance;
};
#endif