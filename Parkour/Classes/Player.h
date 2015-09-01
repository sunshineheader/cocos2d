#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "GAMEDATA.h"

USING_NS_CC;

class Player : public cocos2d::Node
{
public:
	Player();
	~Player();
    CREATE_FUNC(Player);
    virtual bool init();
	void move();
    void jump();
	void smallJump();
	void slideMove();
    void quickMove();
	void magneticMove();
	void superMove();
	void pause();
	void resume();
	void logic(float dt);
	void setUpSpeed(int up_speed);
	int getUpSpeed();
	static void setState(int state);
	static int getState();
	static bool jumpFromGround;
private:
	CC_SYNTHESIZE(int, m_iHP, iHP);
	Sprite* playerSp;
	Sprite* playerSp2;
	static int state;
	static int skillState;
	Action* runAnimate;
	Action* jumpAnimate;
	Action* slideAnimate;
	bool hasSlide;
	bool hasJump;
	bool hasRun;
	bool hasStartSlide;
	bool hasStartBlink;
	int upSpeed;
	float magneticTime;
	float superTime;
	float potentialTime;
	float activeTime;
	float superTransitionTime;
	float activeTransitionTime;
	bool initSkillTime;
	float magneticLevelTime;
	float superLevelTime;
	float potentialLevelTime;
	bool startFly;
	bool startFlyTransition;
};

#endif 
