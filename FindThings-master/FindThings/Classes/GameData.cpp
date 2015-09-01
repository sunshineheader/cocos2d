#include "GAMEDATA.h"
#include "cocos2d.h"
using namespace cocos2d;

GAMEDATA* GAMEDATA::_instance = 0;

GAMEDATA::GAMEDATA(){
	this->init();
}

void GAMEDATA::init(){
	this->level = 0;
	this->score = 0;
	this->lastClikTime = 0;
	this->finishTaskNum = 0;
	this->createTaskNum=0;
	this->findTimes=0;
}

GAMEDATA* GAMEDATA::getInstance(){
	if(_instance == 0){
		_instance = new GAMEDATA();
	}
	return _instance;
}

void GAMEDATA::setSoundState(bool state) {
	UserDefault::getInstance()->setBoolForKey("soundState",state);
}

bool GAMEDATA::getSoundState() {
	return UserDefault::getInstance()->getBoolForKey("soundState",true);
}

void GAMEDATA::setMusicState(bool state) {
	UserDefault::getInstance()->setBoolForKey("musicState",state);
}

bool GAMEDATA::getMusicState() {
	return UserDefault::getInstance()->getBoolForKey("musicState",true);
}

int GAMEDATA::getScore(){
	return score;
}

void GAMEDATA::setScore(int score){
	this->score = score;
	auto record =UserDefault::getInstance()->getIntegerForKey("record",0);
	if(score>record){
		UserDefault::getInstance()->setIntegerForKey("record",score);
	}
}

void GAMEDATA::setFindTimes(int t){
	findTimes = t;
}
int  GAMEDATA::getFindTimes(){
	return findTimes;
}

int GAMEDATA::getRecord(){
	return UserDefault::getInstance()->getIntegerForKey("record",0);
}

int GAMEDATA::getLevel(){
	return level;
}
void GAMEDATA::setLevel(int level){
	this->level = level;
}

void GAMEDATA::addTask(TaskInfo* task){
	CCLOG("add the task into list");
	tasks.pushBack(task);
	setCreatTaskNum();
	CCLOG("add success");
}

void GAMEDATA::deleteTask(TaskInfo* task){
	Vector<TaskInfo*>::iterator beg = tasks.begin(); 
	Vector<TaskInfo*>::iterator end = tasks.end(); 
	for (Vector<TaskInfo*>::const_iterator it = beg; it != end; ++it){
	   TaskInfo* info = *it;
	   if(task->id==info->id){
		    CCLOG("delete the task from list");
			tasks.eraseObject(info);
			break;
		}
	} 
}

Vector<TaskInfo*> GAMEDATA::getCurrentTask(){
	return tasks;
}


void GAMEDATA::cleanDatas(){
	level=0;
	tasks.clear();
	myMaterials.clear();
	score = 0;
	createTaskNum=0;
	findTimes=0;
}


int  GAMEDATA::getReviveNum(){
	return UserDefault::getInstance()->getIntegerForKey("reviveNum",0);
}

void  GAMEDATA::setReviveNum(int num){
	UserDefault::getInstance()->setIntegerForKey("reviveNum",num);
}


int GAMEDATA::getLoginTimes(){
	return UserDefault::getInstance()->getIntegerForKey("loginTimes",0);
}


void GAMEDATA::setLoginTimes(){
	auto times = getLoginTimes()+1;
	UserDefault::getInstance()->setIntegerForKey("loginTimes",times);
}

int  GAMEDATA::getLastClikTime(){
	return lastClikTime;
}


void GAMEDATA::setLastClikTime(int clickTime){
	this->lastClikTime = clickTime;
}


long GAMEDATA::getCurrentTime()   
{    
	struct timeval tv;    
	gettimeofday(&tv,NULL);    
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;      
}  

int  GAMEDATA::getFinishTaskNum(){
	return finishTaskNum;
}


void GAMEDATA::setFinishTaskNum(){
	this->finishTaskNum = finishTaskNum+1;
}


int  GAMEDATA::getCreatTaskNum(){
	return createTaskNum;
}
void GAMEDATA::setCreatTaskNum(){
	this->createTaskNum += 1;
}

int GAMEDATA::getPropFindNum(){
	return UserDefault::getInstance()->getIntegerForKey("prop_find_num",1);
}

void GAMEDATA::setPropFindNum(int num){
	UserDefault::getInstance()->setIntegerForKey("prop_find_num",num);
}

int GAMEDATA::getPropTimeNum(){
	return UserDefault::getInstance()->getIntegerForKey("prop_time_num",1);
}

void GAMEDATA::setPropTimeNum(int num){
	UserDefault::getInstance()->setIntegerForKey("prop_time_num",num);
}
