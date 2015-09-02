#ifndef __TKP_JIA_SU_EFFECT_H__
#define __TKP_JIA_SU_EFFECT_H__

#include "cocos2d.h"

class GameMap;
class ScoreItem;
class ZhuGong;

class JiaSuEffect : public cocos2d::Node
{
public:
	CREATE_FUNC(JiaSuEffect);

	virtual	void update(float delta);

	void setZhuGong(ZhuGong *zhugong);
	void setGameMap(GameMap *gameMap);
	void setTotalTime(float time);

protected:
	JiaSuEffect();
	~JiaSuEffect();
	CC_DISALLOW_COPY_AND_ASSIGN(JiaSuEffect);

	virtual bool init();

private:
	ZhuGong *_zhugong;
	GameMap *_gameMap;

	float _stateTime;
	float _totalTime;

	float _oldMoveSpeed;
};



#endif // __TKP_JIA_SU_EFFECT_H__