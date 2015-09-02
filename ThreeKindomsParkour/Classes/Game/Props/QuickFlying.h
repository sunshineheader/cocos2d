#ifndef __TKP_QUICK_FLYING_H__
#define __TKP_QUICK_FLYING_H__

#include "cocos2d.h"

class GameMap;
class ZhuGong;

class QuickFlying : public cocos2d::Node
{
public:
	static QuickFlying* create(GameMap *gameMap, ZhuGong *zhugong, 
		cocos2d::Node *carrier, float totalTime);

	virtual	void update(float delta);

	void setTotalTime(float time);
	void setNewGameMapMoveSpeed(float speed);

protected:
	QuickFlying(GameMap *gameMap, ZhuGong *zhugong, cocos2d::Node *carrier, float totalTime);
	~QuickFlying();
	CC_DISALLOW_COPY_AND_ASSIGN(QuickFlying);

	virtual bool init();

private:
	ZhuGong *_zhugong;
	GameMap *_gameMap;
	cocos2d::Node *_carrier;

	float _stateTime;
	float _totalTime;

	float _oldGameMapMoveSpeed;
	float _newGameMapMoveSpeed;
};



#endif // __TKP_QUICK_FLYING_H__