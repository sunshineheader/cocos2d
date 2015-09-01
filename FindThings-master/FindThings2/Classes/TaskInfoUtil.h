#ifndef _TASK_INFO_UTIL_
#define _TASK_INFO_UTIL_
#include "TaskInfo.h"
#include "cocos2d.h"
#include <map>
using namespace cocos2d;
class TaskInfoUtil{
public:
	static TaskInfoUtil* getInstance();
	TaskInfo* getTaskById(int id);
	std::map<int,TaskInfo*> getAllTask();
private:
	void init();
	TaskInfoUtil();
	~TaskInfoUtil();
	std::vector<std::string> split(std::string str,std::string pattern); 
private:
	static TaskInfoUtil* m_instance;
	std::map<int,TaskInfo*> infoMap;

};
#endif