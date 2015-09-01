#include "BankRaiseLayer.h"
#include "GAMEDATA.h"
#include "PlayerRank.h"

bool BankRaiseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	animeTime = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* background = Sprite::create("black_bg.png");
	background->setScaleX(800);
	background->setScaleY(480);
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background);

	upBg = Sprite::createWithSpriteFrameName("bank_up.png");
	upBg->setPosition(232,281);
	upBg->setTag(2001);
	this->addChild(upBg);
	
	upNum = LabelAtlas::create(String::createWithFormat("%d",
		PLAYERRANK::getInstance()->getRankList(GAMEDATA::getInstance()->getGameScore()))->_string,"bank_num.png",
		28,37,48);
	upNum->setTag(2002);
	upNum->setAnchorPoint(Point(0.5,0.5));
	upNum->setPosition(232,247);
	this->addChild(upNum);

	downBg = Sprite::createWithSpriteFrameName("bank_down.png");
	downBg->setPosition(552,190);
	downBg->setTag(2003);
	this->addChild(downBg);

	downNum = LabelAtlas::create(String::createWithFormat("%d",
		PLAYERRANK::getInstance()->getRankList(GAMEDATA::getInstance()->getHistoryScore()))->_string,"bank_num.png",
		28,37,48);
	downNum->setTag(2004);
	downNum->setAnchorPoint(Point(0.5,0.5));
	downNum->setPosition(552,234);
	this->addChild(downNum);

	this->scheduleUpdate();
	return true;
}

void BankRaiseLayer::update(float dt){
	if(this->isVisible()){
		animeTime += dt/0.05;
		if(((int)animeTime)/16 % 2 == 0){
			upBg->setPositionY(upBg->getPositionY()+1);
			upNum->setPositionY(upNum->getPositionY()+1);
			downBg->setPositionY(downBg->getPositionY()-1);
			downNum->setPositionY(downNum->getPositionY()-1);
		}else{
			upBg->setPositionY(upBg->getPositionY()-1);
			upNum->setPositionY(upNum->getPositionY()-1);
			downBg->setPositionY(downBg->getPositionY()+1);
			downNum->setPositionY(downNum->getPositionY()+1);
		}
	}
}

void BankRaiseLayer::refreshInfo(){
	
}