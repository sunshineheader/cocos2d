#ifndef __TKP_WU_JIANG_H__
#define __TKP_WU_JIANG_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"


class GameMap;

class WuJiang : public cocos2d::Node
{
public:
	enum class State
	{
		Running,
		Jumping,
		Falling,
		Landing,
		Attacking
	};

public:
	CREATE_FUNC(WuJiang);

	virtual void update(float delta) override;

	void run();
	void jump();
	void fall();
	void land();
	void attack();

	void setGameMap(GameMap *gameMap);

	void setInitPositionX(float x);
	float getInitPositionX() const;

protected:
	WuJiang();
	~WuJiang();
	DISALLOW_COPY_AND_ASSIGN(WuJiang);

	virtual bool init() override;

	void checkCollisionWithJumpRegions();
	void checkVerticalCollisionWithPlatforms();
	void checkAttackBlocks(float delta);
	void checkAttack(const std::string &name);

	bool blocksInRange() const;
	bool blocksInRange(const std::string &name) const;

	void resetAttackState();

private:
	cocostudio::Armature *_wujiang;
	cocostudio::ArmatureAnimation *_animation;
	cocostudio::Bone *_weapon;
	cocostudio::Bone *_leftfoot;
	cocostudio::Bone *_rightfoot;

	State _state;
	cocos2d::Vec2 _velocity;

	GameMap *_gameMap;

	float _initPositionX;

	bool _isAttacking;
	float _attackDuration;
	float _attackStateTime;
	float _attackTotalTime;
	float _attackingTime;
	float _fowardDistance;

	float _lastPositionX;
	float _stopTime;

};

#endif // __TKP_WU_JIANG_H__