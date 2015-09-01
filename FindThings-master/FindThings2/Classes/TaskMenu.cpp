#include "TaskMenu.h"
#include "Chinese.h"
#include "GamePauseLayer.h"
#include "GameData.h"
#include "GameState.h"
#include "TaskInfoUtil.h"
#include "GuideInfoUtil.h"
#include "cocos-ext.h"   
#include "BottomMenu.h"
#include "GameParticle.h"
#include "CallAndroidMethod.h"
#include "Audio.h"
USING_NS_CC_EXT;

TaskMenu* TaskMenu::instance=NULL;

TaskMenu* TaskMenu::getInstance(){
	if (instance == NULL){
		instance = new TaskMenu();
		instance->init();
	}
	return instance;
}

bool TaskMenu::init(){
	if(!Node::init()){
		return false;
	}
	task1 = TaskSprite::create();
	task1->setPosition(Point(10,420));
	task1->setVisible(false);
	this->addChild(task1);

	task2 = TaskSprite::create();
	task2->setVisible(false);
	task2->setPosition(Point(240,420));
	this->addChild(task2);

	task3 = TaskSprite::create();
	task3->setVisible(false);
	task3->setPosition(Point(470,420));
	this->addChild(task3);

	auto visibleSize= Director::getInstance()->getVisibleSize();
	auto pause =  MenuItemImage::create("pause.png","pause.png",CC_CALLBACK_0(TaskMenu::gamePause,this));
	auto pauseMenu = Menu::create(pause,NULL);
	pauseMenu->setPosition(Point(750,450));
	this->addChild(pauseMenu);
	return true;
}

void TaskMenu::gamePause(){
	GAMESTATE::getInstance()->setGamePause(true);//暂停时间
	auto gamePauseLayer=GamePauseLayer::create();
	this->addChild(gamePauseLayer);
}

void TaskMenu::cleanTaskMenu(){
	task1->setVisible(false);
	task2->setVisible(false);
	task3->setVisible(false);
	//显示第一个任务
	updateFirstTask();
}


TaskInfo* TaskMenu::createTask(){
	//CCLOG("create stetp 1");
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CCLog("create stetp 1");
#endif
	GAMEDATA* data = GAMEDATA::getInstance();
	//获取当前的所有物品
	Vector<Materials*> oldMaterials = data->myMaterials;
	Vector<Materials*> newMaterials(oldMaterials.size());
	for(Materials* m:oldMaterials){
		newMaterials.pushBack(m);
	}
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CCLog("create stetp 2 = %d",newMaterials.size());
#endif
	//CCLOG("create stetp 2 = %d",newMaterials.size());
	//获取不被现有任务包含的物品
	Vector<TaskInfo*> allTasks =  data->getCurrentTask();
	Vector<TaskInfo*> taskCopy;
	for(TaskInfo* copy: allTasks){
		taskCopy.pushBack(copy);
	}
	Vector<Materials*> needReMove;
	for(Materials*  mater : newMaterials){
		for(TaskInfo* task:taskCopy){
			for(std::string v:task->thingsId){	
				if(mater->getMaterialsName().compare(v)==0){			
					needReMove.pushBack(mater);
				}
			}
		}
	}
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CCLog("check = %d",needReMove.size());
#endif
	//CCLOG("check = %d",needReMove.size());
	for(Materials* remove:needReMove){
		newMaterials.eraseObject(remove);
	}
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CCLog("create stetp 3 =%d",newMaterials.size());
#endif
	//CCLOG("create stetp 3 =%d",newMaterials.size());
	//随机出一件物品
	int size =  newMaterials.size();
	Materials* ma = newMaterials.at(random(1,size-1));
	while(ma->getMaterialsName().compare("szh2")==0||ma->getMaterialsName().compare("szh3")==0
		||ma->getMaterialsName().compare("szh4")==0||ma->getMaterialsName().compare("szh5")==0){
			ma = newMaterials.at(random(1,size-1));
	}
	//遍历移除所有任务，得到可以需要这件物品的任务
	ValueVector taskIds;
	std::map<int,TaskInfo*> infomap = TaskInfoUtil::getInstance()->getAllTask();
	map<int,TaskInfo*>::iterator it;
	//获得当前可以完成的任务
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CCLog("NAME = %s",ma->getMaterialsName().c_str());
#endif
	//CCLOG("NAME = %s",ma->getMaterialsName().c_str());
	for(it=infomap.begin();it!=infomap.end();++it){
		std::vector<std::string> things = it->second->thingsId;
		for(std::string name : things){
			if(ma->getMaterialsName().compare(name) == 0){
				taskIds.push_back(Value(it->first));
			}		
		}
	}
	//从可选任务中取出一个任务
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CCLog("create stetp 4 = %d",taskIds.size());
#endif
	//CCLOG("create stetp 4 = %d",taskIds.size());
	TaskInfo* info = TaskInfoUtil::getInstance()->getTaskById(taskIds.at(0).asInt());
	//生成任务的物品数量
	int num=0;
	for(std::string va:info->thingsId){
		for(Materials* ma :newMaterials){
			if(ma->getMaterialsName().compare(va) == 0){
				num++;
			}
		}
	}
	//CCLOG("create stetp 5 needNumber = %d",num);
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CCLog("create stetp 5 needNumber = %d",num);
#endif
	if(num<4 && num>=1){
		num = random(1,num);
	}else{
		num = random(1,4);
	}
	info->needNumber=num;
	info->findNumber =0;
	return info;
}

TaskInfo* TaskMenu::createGuideTask(){
	auto id = GuideInfoUtil::getInstance()->getGuideInfo()->taskid;
	TaskInfo* info = TaskInfoUtil::getInstance()->getTaskById(id);
	info->needNumber = 2;
	task1->removeAllChildrenWithCleanup(true);
	task1->showTaskSprite(info->imageName,info->needNumber);
	task1->setTag(info->id);
	task1->setVisible(true);
	return info;
}


void TaskMenu::updateFirstTask(){
	TaskInfo* info = NULL;
	if(GAMEDATA::getInstance()->getLoginTimes()==1 && !GAMESTATE::getInstance()->getIsCreateGuideTask()){
		info = createGuideTask();
		GAMESTATE::getInstance()->setIsCreateGuideTask(true);
	}else{
		info = createTask();
	}
	//CCLOG("check first task");
	//while(checkTask(info)){
	//	CCLOG("new another task 1");
	//	info = createTask();
	//}
	//CCLOG("check first task finish");
	GAMEDATA::getInstance()->addTask(info);
	task1->removeAllChildrenWithCleanup(true);
	task1->showTaskSprite(info->imageName,info->needNumber);
	task1->setTag(info->id);
	task1->setVisible(true);
	showTaskPad(info);
}


void TaskMenu::updateSecondTask(){
	TaskInfo* info2 = createTask();
	//CCLOG("check second task");
	//while(checkTask(info2)){
	//	CCLOG("new another task 2");
	//	info2 = createTask();
	//}
	//CCLOG("check second task finish");
	GAMEDATA::getInstance()->addTask(info2);
	task2->removeAllChildrenWithCleanup(true);
	task2->showTaskSprite(info2->imageName,info2->needNumber);
	task2->setTag(info2->id);
	task2->setVisible(true);
	showTaskPad(info2);
}

void TaskMenu::updateThridTask(){
	TaskInfo* info3 = createTask();
	//CCLOG("check thrid task");
	//while(checkTask(info3)){
	//	CCLOG("new another task 3");
	//	info3 = createTask();
	//}
	//CCLOG("check thrid task finish");
	GAMEDATA::getInstance()->addTask(info3);
	task3->removeAllChildrenWithCleanup(true);
	task3->showTaskSprite(info3->imageName,info3->needNumber);
	task3->setTag(info3->id);
	task3->setVisible(true);
	showTaskPad(info3);
}

bool TaskMenu::checkTask(TaskInfo* info){
	GAMEDATA* data = GAMEDATA::getInstance();
	for(TaskInfo* cur_info : data->getCurrentTask()){
		if(cur_info->id == info->id){
			return true;
		}
	}	
	return false;
}

void TaskMenu::refreshTask(TaskInfo* task){
	Vector<TaskInfo*> infos = GAMEDATA::getInstance()->getCurrentTask();
	task->findNumber += 1;//找到的数量加1
	if(task->id==task1->getTag()){
		task1->updateCurNum(task->findNumber); 
	}else if(task->id==task2->getTag()){
		task2->updateCurNum(task->findNumber);
	}else if(task->id==task3->getTag()){
		task3->updateCurNum(task->findNumber);
	}
	if(task->findNumber>=task->needNumber){
		//完成任务
		Audio::getInstance()->playSound(FINISHTASK);
		//CCLOG("need finish this task");
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		CCLog("need finish this task");
#endif
		GAMEDATA::getInstance()->deleteTask(task);//删除任务
		TaskMenu::getInstance()->showFinishTask(task);	
		GAMEDATA::getInstance()->setFinishTaskNum();
		return;
	}	
}

void TaskMenu::showFinishTask(TaskInfo* task){
	DelayTime* delay = DelayTime::create(0.3f);
	CallFunc* callfun = CallFunc::create([=](){
		//CCLOG("create a new task");
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		CCLog("create a new task");
#endif
		if(task->id==task1->getTag()){
			updateFirstTask();
		}else if(task->id==task2->getTag()){
			updateSecondTask();
		}else if(task->id==task3->getTag()){
			updateThridTask();
		}
		if(GAMEDATA::getInstance()->getCreatTaskNum()==2){
			updateSecondTask();
		}else if(GAMEDATA::getInstance()->getCreatTaskNum()==5){
			updateThridTask();
		}
	});	
	Sequence* seq = Sequence::create(delay,callfun,NULL);
	this->runAction(seq);
}

//显示任务标签
void TaskMenu::showTaskPad(TaskInfo* info){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Layer* taskPad = Layer::create();
	this->addChild(taskPad,99);
	Sprite* pad_bg = Sprite::create("task_info_bg.png");
	pad_bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	taskPad->addChild(pad_bg);
	int level = GAMEDATA::getInstance()->getCreatTaskNum();//获取玩家当前关卡等级
	//CCLOG("LEVEL = %d",level);
	Sprite* title2;
	switch (level)
	{
	case 1:
		title2 = Sprite::create("first_level.png");
		GAMEDATA::getInstance()->setLevel(1);
		break;
	case 3:
		title2 = Sprite::create("second_level.png");
		GAMEDATA::getInstance()->setLevel(2);
		break;
	case 6:
		title2 = Sprite::create("thrid_level.png");
		GAMEDATA::getInstance()->setLevel(3);
		break;
	case 9:
		title2 = Sprite::create("forth_level.png");
		GAMEDATA::getInstance()->setLevel(4);
		break;
	case 10:
		title2 = Sprite::create();
		GAMEDATA::getInstance()->setLevel(5);
		break;
	default:
		title2 = Sprite::create();
		break;
	}
	title2->setPosition(visibleSize.width/2+15,visibleSize.height/2+30);
	taskPad->addChild(title2);

	Sprite* content = Sprite::createWithSpriteFrameName(info->imageName+".png");
	auto si = content->getTextureRect().size;
	content->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	content->setPosition(visibleSize.width/2-si.width/2,visibleSize.height/2-35);
	taskPad->addChild(content);

	Sprite*  curNum = Sprite::create("num_"+cocos2d::String::createWithFormat("%d",info->needNumber)->_string+".png");
	curNum->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	curNum->setPosition(visibleSize.width/2+si.width/2,visibleSize.height/2-32);
	taskPad->addChild(curNum);

	DelayTime* delay = DelayTime::create(1.0);
	CallFunc* callback =CallFunc::create([=](){
		taskPad->removeAllChildren();
		taskPad->removeFromParent();
		//移除展示板，显示加时动画
		if(GAMESTATE::getInstance()->getIsFirstTask()){
			GAMESTATE::getInstance()->setIsFirstTask(false);
			if(GAMEDATA::getInstance()->getLoginTimes()==1){
				//显示新手引导
				GAMESTATE::getInstance()->setIsGuide(true);
			}
		}else{
			addTimeAnim();
		}
	});
	Sequence* seq = Sequence::create(delay,callback,NULL);
	taskPad->runAction(seq);
}

void TaskMenu::addTimeAnim(){
	int time =3;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* animSprite = Sprite::create();
	animSprite->setAnchorPoint(Point::ANCHOR_MIDDLE);
	animSprite->setPosition(visibleSize.width/2-60,visibleSize.height/2);
	this->addChild(animSprite);

	Sprite* symbol = Sprite::create("time_plus.png");
	symbol->setAnchorPoint(Point::ANCHOR_MIDDLE);
	symbol->setPosition(16,0);
	animSprite->addChild(symbol);

	LabelAtlas* time_num = LabelAtlas::create(cocos2d::String::createWithFormat("%d",time)->_string,"time_number.png",15,30,'0');
	time_num->setAnchorPoint(Point::ANCHOR_MIDDLE);
	time_num->setPosition(42,0);
	animSprite->addChild(time_num);

	Sprite* second = Sprite::create("second.png");
	second->setAnchorPoint(Point::ANCHOR_MIDDLE);
	second->setPosition(64,0);
	animSprite->addChild(second);

	auto scale = ScaleTo::create(0.5f,2.0f);
	CallFunc* removeC = CallFunc::create([=](){
		showGameParticleEffect(1,Point(visibleSize.width/2,visibleSize.height/2),this);
		BottomMenu::getInstance()->plusGameTime(time);
		animSprite->removeFromParent();
		payLevel();
	});
	auto sequence = Sequence::create(scale,removeC,NULL);
	animSprite->runAction(sequence);
}

void TaskMenu::payLevel(){
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	GAMEDATA* data =GAMEDATA::getInstance();
	if(data->getCreatTaskNum() == 3){
		//买
		if(!GAMESTATE::getInstance()->getIsPaying()){
			GAMESTATE::getInstance()->setGamePause(true);
			CallAndroidMethod::getInstance()->pay(5);
			GAMESTATE::getInstance()->setIsPaying(true);
		}
	}else if(data->getCreatTaskNum() == 6){
		//送
		if(!GAMESTATE::getInstance()->getIsPaying()){
			GAMESTATE::getInstance()->setGamePause(true);
			CallAndroidMethod::getInstance()->pay(8);
			GAMESTATE::getInstance()->setIsPaying(true);
		}

	}else if(data->getCreatTaskNum() == 9){
		//买
		if(!GAMESTATE::getInstance()->getIsPaying()){
			GAMESTATE::getInstance()->setGamePause(true);
			CallAndroidMethod::getInstance()->pay(5);
			GAMESTATE::getInstance()->setIsPaying(true);
		}
	}
#endif
}
