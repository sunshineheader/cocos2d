#ifndef __TKP_PLAYER_H__
#define __TKP_PLAYER_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"


class GameMap;

class Player : public cocos2d::Node
{
public:
	enum class State 
	{
		Running,
		Jumping,
		Falling
	};

public:
	CREATE_FUNC(Player);

	virtual void update(float delta) override;

	void jump();

	void setGameMap(GameMap *gameMap);

	int getScore() const;

	void die();

	bool isDead() const;

	void setInitPositionX(float x);
	float getInitPositionX() const;

protected:
	Player();
	~Player();
	DISALLOW_COPY_AND_ASSIGN(Player);

	virtual bool init() override;

	void updatePosition(float delta);
	void applyDamping();

	void checkVerticalCollisionWithPlatforms();
	void checkHorizoztalCollisionWithPlatforms();
	void checkWithStars();
	void checkWithBlocks();
	void check();

private:
	cocostudio::Armature *_player;
	cocostudio::ArmatureAnimation *_animation;

	State _state;
	cocos2d::Vec2 _velocity;
	bool _isGrounded;
	int _numJump;
	int _maxJump;

	GameMap *_gameMap;

	int _score;
	bool _isDead;

	float _initPositionX;
};

#endif // __TKP_PLAYER_H__