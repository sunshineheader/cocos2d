#ifndef __TKP_AUTO_COLLECT_SCORE_ITEMS_H__
#define __TKP_AUTO_COLLECT_SCORE_ITEMS_H__

#include "cocos2d.h"

class GameMap;
class ScoreItem;
class ZhuGong;

class AutoCollectScoreItems : public cocos2d::Node
{
public:
	CREATE_FUNC(AutoCollectScoreItems);

	virtual	void update(float delta);

	void setZhuGong(ZhuGong *zhugong);
	void setGameMap(GameMap *gameMap);
	void setTotalTime(float time);

protected:
	AutoCollectScoreItems();
	~AutoCollectScoreItems();
	CC_DISALLOW_COPY_AND_ASSIGN(AutoCollectScoreItems);

	virtual bool init();

	void disableScoreItemsCollecting();

private:
	ZhuGong *_zhugong;
	GameMap *_gameMap;

	float _stateTime;
	float _totalTime;
};



#endif // __TKP_AUTO_COLLECT_SCORE_ITEMS_H__