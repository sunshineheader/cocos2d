#include "Player.h"
#include "ObjectTag.h"
#include "cocos2d.h"
#include "PlayerState.h"
#include "MonsterLayer.h"
#include "TollgateScene.h"
#include "Audio.h"
#include "PayHandler.h"

USING_NS_CC;

int Player::state = Player_Run;
int Player::skillState = Player_Normal;
bool Player::jumpFromGround = false;

Player::Player(){
	m_iHP = 100;
}

Player::~Player()
{
}

bool Player::init()
{
    if (!Node::init())
    {
        return false;
    }
	hasSlide = false;
	hasRun = false;
	hasJump = false;
	hasStartSlide = false;
	initSkillTime = false;
	startFly = false;
	startFlyTransition = false;
	hasStartBlink = false;
	superTime = 0;
	potentialTime = 0;
	activeTime = 0;
	superTransitionTime = 0;
	activeTransitionTime = 0;
	magneticTime = 0;
	state = Player_Run;
	skillState = Player_Normal;
	upSpeed = 0;
	this->setTag(ObjectTag_Player);
	playerSp = Sprite::createWithSpriteFrameName("run_1.png");
	playerSp->setTag(111);
	this->setContentSize(playerSp->getContentSize()*0.6f);

	playerSp2 = Sprite::create("black_bg.png");
	
	this->addChild(playerSp2);
    this->addChild(playerSp);
    
    return true;
}

void Player::move()
{
	if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
		return;
	}
	CCLOG("move>>>>>>state=%d",state);
	if(state == Player_Slide){
		this->setPositionY(this->getPositionY()+45);
	}
	this->setVisible(true);
	state = Player_Run;
	if(TollgateScene::needSlide){
		slideMove();
		return;
	}
	playerSp->stopAllActions();
	playerSp2->stopAllActions();
	//if(!hasRun){
		Vector<SpriteFrame*> m_runFrames;
		SpriteFrame* frame1;
		for(int i=0;i<9;i++){
			frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("run_%d.png",i+1)->_string);
			m_runFrames.pushBack(frame1);
		}
		auto animation1 = Animation::createWithSpriteFrames(m_runFrames,0.06f);
		runAnimate = RepeatForever::create(Animate::create(animation1));
		hasRun = true;
	//}
		if(Player::skillState == Player_Magic){
			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("magnetic_bg_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
			playerSp->runAction(runAnimate);
		}else if(Player::skillState == Player_Super || Player::skillState == Player_Transition_Super){
			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("shield_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
			playerSp->runAction(runAnimate);
		}else if(Player::skillState == Player_Fly || Player::skillState == Player_Active){
			Vector<SpriteFrame*> m_flyFrames;
			SpriteFrame* frame3;
			for(int i=0;i<2;i++){
				frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_1.png");
				m_flyFrames.pushBack(frame3);
			}
			auto animation3 = Animation::createWithSpriteFrames(m_flyFrames,0.1f);
			auto flyAnimate = RepeatForever::create(Animate::create(animation3));
			playerSp->runAction(flyAnimate);

			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("fly_bg_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
		}else if(skillState == Player_Transition_Fly){
			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("fly_bg_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
			playerSp->runAction(runAnimate);
		}else{
			CCLOG(">>>>>>>>>>>>>>>>>>>>>>>>stop playerSp2 action");
			playerSp2->stopAllActions();
			playerSp2->setVisible(false);
			playerSp->runAction(runAnimate);
		}
}

void Player::jump()
{
	if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
		return;
	}
	CCLOG("jump>>>>>>>>>>state=%d",state);
	this->setVisible(true);
	Audio::getInstance()->playSound("Music/jump.mp3");
	if(state == Player_Run){
		GAMEDATA::getInstance()->setJumpTimes(GAMEDATA::getInstance()->getJumpTimes()+1);
		state = Player_Jump;	
		Player::jumpFromGround = true;
		upSpeed = 40;
		playerSp->stopAllActions();
		playerSp2->stopAllActions();
		//if(!hasJump){
			Vector<SpriteFrame*> m_jumpFrames;
			SpriteFrame* frame3;
			for(int i=0;i<9;i++){
				frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("jum_%d.png",i+1)->_string);
				m_jumpFrames.pushBack(frame3);
			}
			auto animation3 = Animation::createWithSpriteFrames(m_jumpFrames,0.05f);
			jumpAnimate = Animate::create(animation3);		
			hasJump = true;
		//}
		if(Player::skillState == Player_Magic){
			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("magnetic_bg_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
			playerSp->runAction(jumpAnimate);
		}else if(Player::skillState == Player_Super || Player::skillState == Player_Transition_Super){
			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("shield_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
			playerSp->runAction(jumpAnimate);
		}else if(Player::skillState == Player_Fly || Player::skillState == Player_Active){
			Vector<SpriteFrame*> m_flyFrames;
			SpriteFrame* frame3;
			for(int i=0;i<2;i++){
				frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_1.png");
				m_flyFrames.pushBack(frame3);
			}
			auto animation3 = Animation::createWithSpriteFrames(m_flyFrames,0.1f);
			auto flyAnimate = RepeatForever::create(Animate::create(animation3));
			playerSp->runAction(flyAnimate);

			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("fly_bg_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
		}else if(skillState == Player_Transition_Fly){
			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("fly_bg_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
			playerSp->runAction(jumpAnimate);
		}else{
			playerSp2->stopAllActions();
			playerSp2->setVisible(false);
			playerSp->runAction(jumpAnimate);
		}
	}
}

void Player::smallJump()
{
	if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
		return;
	}
	Audio::getInstance()->playSound("Music/jump.mp3");
	if(state == Player_Run){
		this->setVisible(true);
		state = Player_Jump;	
		Player::jumpFromGround = true;
		upSpeed = 30;
		playerSp->stopAllActions();
		playerSp2->stopAllActions();
		//if(!hasJump){
			Vector<SpriteFrame*> m_jumpFrames;
			SpriteFrame* frame3;
			for(int i=0;i<9;i++){
				frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("jum_%d.png",i+1)->_string);
				m_jumpFrames.pushBack(frame3);
			}
			auto animation3 = Animation::createWithSpriteFrames(m_jumpFrames,0.05f);
			jumpAnimate = Animate::create(animation3);		
			hasJump = true;
		//}
		if(Player::skillState == Player_Magic){
			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("magnetic_bg_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
			playerSp->runAction(jumpAnimate);
		}else if(Player::skillState == Player_Super || Player::skillState == Player_Transition_Super){
			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("shield_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
			playerSp->runAction(jumpAnimate);
		}else if(Player::skillState == Player_Fly || Player::skillState == Player_Active){
			Vector<SpriteFrame*> m_flyFrames;
			SpriteFrame* frame3;
			for(int i=0;i<2;i++){
				frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_1.png");
				m_flyFrames.pushBack(frame3);
			}
			auto animation3 = Animation::createWithSpriteFrames(m_flyFrames,0.1f);
			auto flyAnimate = RepeatForever::create(Animate::create(animation3));
			playerSp->runAction(flyAnimate);

			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("fly_bg_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
		}else if(skillState == Player_Transition_Fly){
			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("fly_bg_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
			playerSp->runAction(jumpAnimate);
		}else{
			playerSp2->stopAllActions();
			playerSp2->setVisible(false);
			playerSp->runAction(jumpAnimate);
		}
	}
}

void Player::slideMove(){
	if(Player::skillState == Player_Active || Player::skillState == Player_Fly || startFly){
		return;
	}
	this->setVisible(true);
	if(state == Player_Run){
		GAMEDATA::getInstance()->setSlideTimes(GAMEDATA::getInstance()->getSlideTimes()+1);
		state = Player_Slide;
		playerSp->stopAllActions();
		playerSp2->stopAllActions();
		Vector<SpriteFrame*> m_slideFrames;
		SpriteFrame* frame2;
		for(int i=0;i<9;i++){
			frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("slide.png");
			m_slideFrames.pushBack(frame2);
		}
		auto animation2 = Animation::createWithSpriteFrames(m_slideFrames,0.05f);
		slideAnimate = RepeatForever::create(Animate::create(animation2));
		hasSlide = true;
		this->setPositionY(this->getPositionY()-45);
		if(Player::skillState == Player_Magic){
			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("magnetic_bg_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
			playerSp->runAction(slideAnimate);
		}else if(Player::skillState == Player_Super || Player::skillState == Player_Transition_Super){
			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("shield_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
			playerSp->runAction(slideAnimate);
		}else if(Player::skillState == Player_Fly || Player::skillState == Player_Active){
			Vector<SpriteFrame*> m_flyFrames;
			SpriteFrame* frame3;
			for(int i=0;i<2;i++){
				frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_1.png");
				m_flyFrames.pushBack(frame3);
			}
			auto animation3 = Animation::createWithSpriteFrames(m_flyFrames,0.1f);
			auto flyAnimate = RepeatForever::create(Animate::create(animation3));
			playerSp->runAction(flyAnimate);

			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("fly_bg_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
		}else if(skillState == Player_Transition_Fly){
			Vector<SpriteFrame*> m_superFrames;
			SpriteFrame* frame2;
			for(int i=0;i<3;i++){
				frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("fly_bg_%d.png",i+1)->_string);
				m_superFrames.pushBack(frame2);
			}
			auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
			auto superAnimate = RepeatForever::create(Animate::create(animation2));

			playerSp2->runAction(superAnimate);
			playerSp->runAction(slideAnimate);
		}else{
			playerSp2->stopAllActions();
			playerSp2->setVisible(false);
			playerSp->runAction(slideAnimate);
		}
	}
}

void Player::quickMove()
{
	if(skillState == Player_Active){
		GAMEDATA::getInstance()->setActivePotentialTimes(GAMEDATA::getInstance()->getActivePotentialTimes()+1);
	}else if(skillState == Player_Fly){
		GAMEDATA::getInstance()->setPropPotentialTimes(GAMEDATA::getInstance()->getPropPotentialTimes()+1);
	}
	setUpSpeed(0);
	playerSp->stopAllActions();
	playerSp2->stopAllActions();
	playerSp2->setVisible(true);
	startFly = true;
	Vector<SpriteFrame*> m_flyFrames;
	SpriteFrame* frame3;
	for(int i=0;i<2;i++){
		frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("fly_1.png");
		m_flyFrames.pushBack(frame3);
	}
	auto animation3 = Animation::createWithSpriteFrames(m_flyFrames,0.1f);
	auto flyAnimate = RepeatForever::create(Animate::create(animation3));
	playerSp->runAction(flyAnimate);

	Vector<SpriteFrame*> m_superFrames;
	SpriteFrame* frame2;
	for(int i=0;i<3;i++){
		frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("fly_bg_%d.png",i+1)->_string);
		m_superFrames.pushBack(frame2);
	}
	auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
	auto superAnimate = RepeatForever::create(Animate::create(animation2));

	playerSp2->runAction(superAnimate);
}

void Player::magneticMove(){
	playerSp2->stopAllActions();
	playerSp2->setVisible(true);
	Vector<SpriteFrame*> m_superFrames;
	SpriteFrame* frame2;
	for(int i=0;i<3;i++){
		frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("magnetic_bg_%d.png",i+1)->_string);
		m_superFrames.pushBack(frame2);
	}
	auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
	auto superAnimate = RepeatForever::create(Animate::create(animation2));

	playerSp2->runAction(superAnimate);
}

void Player::superMove(){
	playerSp2->stopAllActions();
	playerSp2->setVisible(true);
	Vector<SpriteFrame*> m_superFrames;
	SpriteFrame* frame2;
	for(int i=0;i<3;i++){
		frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("shield_%d.png",i+1)->_string);
		m_superFrames.pushBack(frame2);
	}
	auto animation2 = Animation::createWithSpriteFrames(m_superFrames,0.1f);
	auto superAnimate = RepeatForever::create(Animate::create(animation2));

	playerSp2->runAction(superAnimate);
}

void Player::pause(){
	playerSp->pauseSchedulerAndActions();
	playerSp2->pauseSchedulerAndActions();
}

void Player::resume(){
	playerSp->resumeSchedulerAndActions();
	playerSp2->resumeSchedulerAndActions();
}

void Player::setState(int m_state){
	state = m_state;
}

int Player::getState(){
	return state;
}

void Player::setUpSpeed(int up_speed){
	upSpeed = up_speed;
}

int Player::getUpSpeed(){
	return upSpeed;
}

void Player::logic(float dt){
	if(startFly){
		Audio::getInstance()->playSound("Music/active.mp3");
		if(this->getPositionX() < 200){
			this->setPositionX(getPositionX()+30);
		}
		if(this->getPositionY() < 360){
			this->setPositionY(getPositionY()+30);
		}
		if(this->getPositionX() > 200){
			this->setPositionX(200);
		}
		if(this->getPositionY() > 360){
			this->setPositionY(360);
		}
		CCLOG("p.x=%f",getPositionX());
		CCLOG("p.y=%f",getPositionY());
		if(this->getPositionX() >= 199.9 && this->getPositionY() >= 359.9){
			CCLOG("end start fly");
			startFly =  false;
		}
	}
	if(startFlyTransition){
		this->setPositionY(getPositionY()-30);
		if(MonsterLayer::playerRowNum == 7){
			if(this->getPositionY() < 231){
				this->setPositionY(230.4);
				startFlyTransition = false;
				Player::skillState = Player_Transition_Fly;
				move();
			}
		}else if(MonsterLayer::playerRowNum == 6){
			if(this->getPositionY() < 231+32){
				this->setPositionY(230.4+32);
				startFlyTransition = false;
				Player::skillState = Player_Transition_Fly;
				move();
			}
		}else if(MonsterLayer::playerRowNum == 5){
			if(this->getPositionY() < 231+64){
				this->setPositionY(230.4+64);
				startFlyTransition = false;
				Player::skillState = Player_Transition_Fly;
				move();
			}
		}else if(MonsterLayer::playerRowNum == 8){
			if(this->getPositionY() < 231-32){
				this->setPositionY(230.4-32);
				startFlyTransition = false;
				Player::skillState = Player_Transition_Fly;
				move();
			}
		}else if(MonsterLayer::playerRowNum == 9){
			if(this->getPositionY() < 231-64){
				this->setPositionY(230.4-64);
				startFlyTransition = false;
				Player::skillState = Player_Transition_Fly;
				move();
			}
		}else if(MonsterLayer::playerRowNum == 10){
			if(this->getPositionY() < 231-96){
				this->setPositionY(230.4-96);
				startFlyTransition = false;
				Player::skillState = Player_Transition_Fly;
				move();
			}
		}
	}
	if(!initSkillTime || PayHandler::revivaled){
		initSkillTime = true;
		magneticLevelTime = GAMEDATA::getInstance()->getMagneticTime();
		superLevelTime = GAMEDATA::getInstance()->getSuperTime();
		potentialLevelTime = GAMEDATA::getInstance()->getPotentialTime();
		if(PayHandler::revivaled){
			PayHandler::revivaled = false;
			potentialLevelTime = 5;
		}
		CCLOG(">>>>>>>>>>>>>>>time=%f",potentialLevelTime);
	}
	if(Player::skillState == Player_Magic){
		superTime = 0;
		potentialTime = 0;
		activeTime = 0;
		superTransitionTime = 0;
		activeTransitionTime = 0;
		CCLOG("magneticTime=%f",magneticTime);
		magneticTime += dt;
		if(magneticTime >= magneticLevelTime){
			Player::skillState = Player_Normal;
		}
	}else if(Player::skillState == Player_Super){
		CCLOG("superTime=%f",superTime);
		superTime += dt;
		potentialTime = 0;
		activeTime = 0;
		superTransitionTime = 0;
		activeTransitionTime = 0;
		magneticTime = 0;
		if(superTime >= superLevelTime){
			Player::skillState = Player_Transition_Super;
		}
	}else if(Player::skillState == Player_Fly){
		superTime = 0;
		CCLOG("potentialTime=%f",potentialTime);
		potentialTime += dt;
		activeTime = 0;
		superTransitionTime = 0;
		activeTransitionTime = 0;
		magneticTime = 0;
		if(potentialTime >= potentialLevelTime){
			startFlyTransition = true;
		}
	}else if(Player::skillState == Player_Active){
		superTime = 0;
		potentialTime = 0;
		CCLOG("activeTime=%f",activeTime);
		CCLOG("potentialLevelTime=%f",potentialLevelTime);
		activeTime += dt;
		superTransitionTime = 0;
		activeTransitionTime = 0;
		magneticTime = 0;
		if(!startFly && !startFlyTransition){
			this->setPosition(200,360);
		}
		if(activeTime >= potentialLevelTime){
			startFlyTransition = true;
		}
	}else if(Player::skillState == Player_Transition_Super){
		superTime = 0;
		potentialTime = 0;
		activeTime = 0;
		CCLOG("superTransitionTime=%f",superTransitionTime);
		superTransitionTime += dt;
		activeTransitionTime = 0;
		magneticTime = 0;
		if(((int)(superTransitionTime*100))%18 > 8){
			playerSp2->setVisible(false);
		}else{
			playerSp2->setVisible(true);
		}
		if(superTransitionTime >= 2.0){
			playerSp2->setVisible(true);
			Player::skillState = Player_Normal;
			if(state == Player_Run){
				move();
			}else if(state == Player_Jump){
				jump();
			}else if(state == Player_Slide){
				slideMove();
			}
		}
	}else if(Player::skillState == Player_Transition_Fly){
		superTime = 0;
		potentialTime = 0;
		activeTime = 0;
		superTransitionTime = 0;
		CCLOG("activeTransitionTime=%f",activeTransitionTime);
		activeTransitionTime += dt;
		magneticTime = 0;
		if(((int)(activeTransitionTime*100))%18 > 8){
			playerSp2->setVisible(false);
		}else{
			playerSp2->setVisible(true);
		}
		if(activeTransitionTime >= 2.0){
			playerSp2->setVisible(true);
			Player::skillState = Player_Normal;
			if(state == Player_Run){
				move();
			}else if(state == Player_Jump){
				jump();
			}else if(state == Player_Slide){
				slideMove();
			}
		}
	}
}
