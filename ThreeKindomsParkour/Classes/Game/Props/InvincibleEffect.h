#ifndef __TKP_INVINCIBLE_EFFECT_H__
#define __TKP_INVINCIBLE_EFFECT_H__

#include "cocos2d.h"

class GameMap;
class ScoreItem;
class ZhuGong;

class InvincibleEffect : public cocos2d::Node
{
public:
	CREATE_FUNC(InvincibleEffect);

	virtual	void update(float delta);

	void setZhuGong(ZhuGong *zhugong);
	void setGameMap(GameMap *gameMap);
	void setTotalTime(float time);

protected:
	InvincibleEffect();
	~InvincibleEffect();
	CC_DISALLOW_COPY_AND_ASSIGN(InvincibleEffect);

	virtual bool init();

private:
	ZhuGong *_zhugong;
	GameMap *_gameMap;

	float _stateTime;
	float _totalTime;

	float _oldMoveSpeed;

	cocos2d::Sprite *_baguadun;
};



#endif // __TKP_INVINCIBLE_EFFECT_H__