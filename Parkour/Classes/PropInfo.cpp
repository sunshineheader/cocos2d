#include "PropInfo.h"
#include "GameData.h"
#include "PlayerState.h"
#include "CallAndroidMethod.h"
#include "GameStateInfo.h"
#include "GameState.h"

PropInfo* PropInfo::_instance = nullptr;
Player* PropInfo::m_player = nullptr;
PropInfo::PropInfo(){
	this->init();
}

PropInfo* PropInfo::getInstance(Player* player){
	if(_instance == 0){
		_instance = new PropInfo();
	}
	m_player = player;
	return _instance;
}

PropInfo* PropInfo::getInstance2(){
	return _instance;
}

bool PropInfo::init(){
	if(!Node::init()){
		return false;
	}
	showVisible = true;
	potentialIcon = Sprite::createWithSpriteFrameName("lobby_prop_potential.png");
	potentialIcon->setPosition(146,320);
	this->addChild(potentialIcon);
	
	int potentialPropNum = GAMEDATA::getInstance()->getPotentialPropNum();

	potentialNum = LabelAtlas::create(String::createWithFormat("%d",potentialPropNum)->_string,"prop_num.png",14,18,48);
	potentialNum->setPosition(146,290);
	potentialNum->setAnchorPoint(Point(0.5, 0.5));	
	if(potentialPropNum > 0){
		potentialNum->setVisible(true);
	}else{
		potentialNum->setVisible(false);
	}
	this->addChild(potentialNum);	

	superIcon = Sprite::createWithSpriteFrameName("lobby_prop_super.png");
	superIcon->setPosition(200,320);
	this->addChild(superIcon);
	
	int superPropNum = GAMEDATA::getInstance()->getSuperPropNum();
	superNum = LabelAtlas::create(String::createWithFormat("%d",superPropNum)->_string,"prop_num.png",14,18,48);
	superNum->setPosition(200,290);
	superNum->setAnchorPoint(Point(0.5, 0.5));
	if(superPropNum > 0){
		superNum->setVisible(true);
	}else{
		superNum->setVisible(false);
	}
	this->addChild(superNum);	

	magneticIcon = Sprite::createWithSpriteFrameName("lobby_prop_magnetic.png");
	magneticIcon->setPosition(254,320);
	this->addChild(magneticIcon);
	
	int magneticPropNum = GAMEDATA::getInstance()->getMagneticPropNum();
	magneticNum = LabelAtlas::create(String::createWithFormat("%d",magneticPropNum)->_string,"prop_num.png",14,18,48);
	magneticNum->setPosition(254,290);
	magneticNum->setAnchorPoint(Point(0.5, 0.5));
	if(magneticPropNum > 0){
		magneticNum->setVisible(true);
	}else{
		magneticNum->setVisible(false);
	}
	this->addChild(magneticNum);

	use_info = Sprite::create("use_prop_info_text.png");
	use_info->setPosition(200,380);
	this->addChild(use_info);

	listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = CC_CALLBACK_2(PropInfo::usePropPotential,this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1,potentialIcon);

	listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = CC_CALLBACK_2(PropInfo::usePropSuper,this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2,superIcon);

	listener3 = EventListenerTouchOneByOne::create();
	listener3->onTouchBegan = CC_CALLBACK_2(PropInfo::usePropMagnetic,this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener3,magneticIcon);

	return true;
}

void PropInfo::refreshSuperNum(){
	int superPropNum = GAMEDATA::getInstance()->getSuperPropNum();
	if(superPropNum > 0){
		superNum->setVisible(true);
	}else{
		superNum->setVisible(false);
	}
	superNum->setString(String::createWithFormat("%d",superPropNum)->_string);
}

void PropInfo::refreshMagneticNum(){
	int magneticPropNum = GAMEDATA::getInstance()->getMagneticPropNum();
	if(magneticPropNum > 0){
		magneticNum->setVisible(true);
	}else{
		magneticNum->setVisible(false);
	}
	magneticNum->setString(String::createWithFormat("%d",magneticPropNum)->_string);
}

void PropInfo::refreshPotentialNum(){
	int potentialPropNum = GAMEDATA::getInstance()->getPotentialPropNum();
	if(potentialPropNum > 0){
		potentialNum->setVisible(true);
	}else{
		potentialNum->setVisible(false);
	}
	potentialNum->setString(String::createWithFormat("%d",potentialPropNum)->_string);
}

void PropInfo::updatePosition(float x,float y){
	potentialIcon->setPosition(x-34,y+90);
	potentialNum->setPosition(x-34,y+65);
	superIcon->setPosition(x+20,y+90);
	superNum->setPosition(x+20,y+65);
	magneticIcon->setPosition(x+74,y+90);
	magneticNum->setPosition(x+74,y+65);
	use_info->setPosition(x + 54, y + 150);
}

bool PropInfo::usePropPotential(Touch* m_touch, Event* m_event){
	if(this->isVisible()){
		if(GameStateInfo::getInstance()->getGameState() != Game_Playing){
			return true;
		}
		if(m_event->getCurrentTarget()->getBoundingBox().containsPoint(m_touch->getLocation())){
			int potentialPropNum = GAMEDATA::getInstance()->getPotentialPropNum();
			if(potentialPropNum > 0){
				Player::skillState = Player_Fly;
				m_player->quickMove();
				GAMEDATA::getInstance()->setPotentialPropNum(potentialPropNum-1);
				refreshPotentialNum();
			}else{
				#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
					CallAndroidMethod::getInstance()->pay(1);
				#endif				
			}
			this->setVisible(false);
			showVisible = false;
		}
	}
	return false;
}

bool PropInfo::usePropSuper(Touch* m_touch, Event* m_event){
	if(this->isVisible()){
		if(GameStateInfo::getInstance()->getGameState() != Game_Playing){
			return true;
		}
		if(m_event->getCurrentTarget()->getBoundingBox().containsPoint(m_touch->getLocation())){
			int superPropNum = GAMEDATA::getInstance()->getSuperPropNum();
			if(superPropNum > 0){
				Player::skillState = Player_Super;
				m_player->superMove();
				GAMEDATA::getInstance()->setSuperPropNum(superPropNum-1);
				refreshSuperNum();
			}else{
				#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
					CallAndroidMethod::getInstance()->pay(6);
				#endif
			}
			this->setVisible(false);
			showVisible = false;
		}
	}
	return false;
}

bool PropInfo::usePropMagnetic(Touch* m_touch, Event* m_event){
	if(this->isVisible()){
		if(GameStateInfo::getInstance()->getGameState() != Game_Playing){
			return true;
		}
		if(m_event->getCurrentTarget()->getBoundingBox().containsPoint(m_touch->getLocation())){
			int magneticPropNum = GAMEDATA::getInstance()->getMagneticPropNum();
			if(magneticPropNum > 0){
				Player::skillState = Player_Magic;
				m_player->magneticMove();
				GAMEDATA::getInstance()->setMagneticPropNum(magneticPropNum-1);
				refreshMagneticNum();
			}else{
				#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
					CallAndroidMethod::getInstance()->pay(7);
				#endif
			}
			this->setVisible(false);
			showVisible = false;
		}
	}
	return false;
}

bool PropInfo::isShowVisible(){
	return showVisible;
}

void PropInfo::setShowVisible(bool show_visible){
	showVisible = show_visible;
}

void PropInfo::removeTouchListener(){
	getEventDispatcher()->removeEventListener(listener1);
	getEventDispatcher()->removeEventListener(listener2);
	getEventDispatcher()->removeEventListener(listener3);
}
