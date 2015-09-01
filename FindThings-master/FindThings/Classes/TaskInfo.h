#ifndef _TASK_INFO_H_
#define _TASK_INFO_H_
#include <string>
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;
class TaskInfo: public Node{
public:
	int id;//任务ID
	std::string name;//任务名称
	std::string imageName;//任务图片的名称
	vector<std::string> thingsId;//可以完成任务的物品ID
	int needNumber;//需要的物品数量
	int findNumber;
};
#endif