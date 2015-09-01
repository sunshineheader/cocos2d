#include "Upgrade.h"
#include "Chinese.h"
#include "CallAndroidMethod.h"
#include "GameData.h"

Upgrade* Upgrade::_instance = 0;
Upgrade::Upgrade(){
	this->init();
}

Upgrade* Upgrade::getInstance(){
	_instance = new Upgrade();
	return _instance;
}

bool Upgrade::init(){
	if(!Node::init()){
		return false;
	}

	animTime = 0;
	auto bg = Sprite::create("bg_mainscene.jpg");
	bg->setPosition(240,400);
	this->addChild(bg);

	auto shineBg = Sprite::create("upgrade_shine_bg.png");
	shineBg->setPosition(240,400);
	this->addChild(shineBg);
	shineBg->runAction(RepeatForever::create(RotateBy::create(3,360)));

	auto title = Sprite::create("upgrade_title.png");
	title->setPosition(240,521);
	this->addChild(title);

	int levelNum = GAMEDATA::getInstance()->getUserLevel()+1;

	auto levelTxt = Sprite::create("upgrade_lv.png");
	auto level = LabelAtlas::create(String::createWithFormat("%d",levelNum)->_string,"upgrade_level_num.png",50,92,48);
	level->setAnchorPoint(Point(0.5,0.5));
	if(levelNum < 10){
		levelTxt->setPosition(197,400);
		level->setPosition(283,400);
	}else if(levelNum < 100){
		levelTxt->setPosition(175,400);
		level->setPosition(305,400);
	}else{
		levelTxt->setPosition(150,400);
		level->setPosition(330,400);
	}
	this->addChild(levelTxt);
	this->addChild(level);

	auto upgradePrize = Sprite::create("upgrade_prize.png");
	upgradePrize->setPosition(40,287);
	upgradePrize->setAnchorPoint(Point(0,0.5));
	this->addChild(upgradePrize);

	auto goldPack = Sprite::create("gold_pack.png");
	goldPack->setPosition(114,224);
	goldPack->setAnchorPoint(Point(0.5,0.5));
	this->addChild(goldPack);

	auto addScorePer = Sprite::create("upgrade_add_per.png");
	addScorePer->setPosition(440,287);
	addScorePer->setAnchorPoint(Point(1,0.5));
	this->addChild(addScorePer);

	auto goldNum = LabelAtlas::create(String::createWithFormat("%d",GAMEDATA::getInstance()->getUpgradePrizeNum(levelNum))->_string,
			"game_result_gold_num.png",15,27,48);
	goldNum->setPosition(114,180);
	goldNum->setAnchorPoint(Point(0.5,0.5));
	this->addChild(goldNum);

	int perNum = (int)(GAMEDATA::getInstance()->getScoreAddPer(levelNum)*100);
	auto addPer = LabelAtlas::create(String::createWithFormat("%d",perNum)->_string,
			"add_score_per_num.png",25,44,48);
	auto per = Sprite::create("upgrade_per.png");
	addPer->setAnchorPoint(Point(0.5,0.5));
	if(perNum < 10){
		addPer->setPosition(340-18,202);
		per->setPosition(340+18,202);
	}else{
		addPer->setPosition(340-28,202);
		per->setPosition(340+28,202);
	}
	this->addChild(addPer);
	this->addChild(per);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Upgrade::hideSelf,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	scheduleUpdate();
	return true;
}

bool Upgrade::hideSelf(Touch* touch,Event* event){
	if(animTime > 20){
		this->setVisible(false);
		this->removeFromParentAndCleanup(true);
	}
	return true;
}

void Upgrade::update(float dt){
	if(this->isVisible()){
		animTime += dt/0.05;
	}
}
