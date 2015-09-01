#include "TaskSprite.h"


bool TaskSprite::init(){
	if(!Sprite::init()){
		return false;
	}
	return true;
}

void TaskSprite::showTaskSprite(string name,int tar_num){
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	CCLog("task name = %s",name.c_str());
#endif
	title = Sprite::createWithSpriteFrameName(name+".png");
	title->setAnchorPoint(ccp(0,0));
	title->setPosition(5,8);
	this->addChild(title,1);

	auto si = title->getTextureRect().size;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	task_bg = Scale9Sprite::create("task_bg.png");
	task_bg->setAnchorPoint(ccp(0,0));
	task_bg->setPosition(0,0);
	task_bg -> setPreferredSize(CCSizeMake(si.width+72,52));
	this->addChild(task_bg,-1);

    curNum = Sprite::create("num_0.png");
	curNum->setAnchorPoint(ccp(0,0));
	curNum->setPosition(si.width+8,10);
	this->addChild(curNum);

	split = Sprite::create("split.png");
	split->setAnchorPoint(ccp(0,0));
	split->setPosition(si.width+29,10);
	this->addChild(split);

	tarNum = Sprite::create("num_"+cocos2d::String::createWithFormat("%d",tar_num)->_string+".png");
	tarNum->setAnchorPoint(ccp(0,0));
	tarNum->setPosition(si.width+44,10);
	this->addChild(tarNum);
}

void TaskSprite::updateCurNum(int cur_num){
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("num_"+cocos2d::String::createWithFormat("%d",cur_num)->_string+".png");
    curNum->setTexture(texture);
}
