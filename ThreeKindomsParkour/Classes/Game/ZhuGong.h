#ifndef __TKP_ZHUGONG_H__
#define __TKP_ZHUGONG_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"


#include "Math/Polygon.h"

class GameMap;

class ZhuGong : public cocos2d::Node
{
public:
    enum class State
    {
		Running,
		Jumping,
		Falling,
		Landing
    };

public:
    CREATE_FUNC(ZhuGong);

    virtual void update(float delta) override;

	void run();
	void jump();
	void fall();
	void land();
	void die();

    void setGameMap(GameMap *gameMap);

    int getScore() const;

    bool isDead() const;

    void setInitPositionX(float x);
    float getInitPositionX() const;

	void setFlying(bool isFlying);
	bool isFlying() const;

	void setInvincible(bool isInvincible);
	bool isInvincible() const;

	State getState() const;

	void setAttackRegion(const std::vector<float> &vertices);
	void setDefenceRegion(const std::vector<float> &vertices);
	Math::Polygon& getAttackRegion();
	Math::Polygon& getDefenceRegion();

	bool checkCollisionWithAllBones(Math::Polygon &region);
	bool checkCollisionWithFeet(Math::Polygon &region);

	void stepJump();

protected:
    ZhuGong();
    ~ZhuGong();
    DISALLOW_COPY_AND_ASSIGN(ZhuGong);

    virtual bool init() override;

    void updatePosition(float delta);
    void applyDamping();

    void checkVerticalCollisionWithPlatforms();
    void checkHorizoztalCollisionWithPlatforms();
    void checkWithStars();

public:
    cocostudio::Armature *_zhugong;
    cocostudio::ArmatureAnimation *_animation;
	cocostudio::Bone *_leftfoot;
	cocostudio::Bone *_rightfoot;

    State _state;
    cocos2d::Vec2 _velocity;
    int _numJump;
    int _maxJump;

    GameMap *_gameMap;
    float _initPositionX;

	bool _isDead;
	bool _isFlying;
	bool _isInvincible;

	Math::Polygon _attackRegion;
	Math::Polygon _defenceRegion;
};

#endif // __TKP_ZHUGONG_H__