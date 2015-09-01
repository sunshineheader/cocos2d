#include "Gold.h"
#include "GameData.h"

Gold* Gold::_instance = nullptr;
Gold::Gold(){
	this->init();
}

Gold* Gold::getInstance(){
	if(_instance == 0){
		_instance = new Gold();
	}
	return _instance;
}

bool Gold::init(){
	if(!Node::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	playerGold = LabelAtlas::create(String::createWithFormat("%d",GAMEDATA::getInstance()->getGoldNum())->_string,"gold_num.png",18,26,48);
	playerGold->setPosition(410,755);
	playerGold->setAnchorPoint(Point(1, 0.5));
	this->addChild(playerGold);
	return true;
}

void Gold::refreshGold(){
	playerGold->setString(String::createWithFormat("%d",GAMEDATA::getInstance()->getGoldNum())->_string);
}
