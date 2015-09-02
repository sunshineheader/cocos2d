#ifndef __TKP_GAME_MAP_H__
#define __TKP_GAME_MAP_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include <list>
#include <map>

class ZhuGong;
class WuJiang;
class WenChen;
class RepeatedBackground;

class PropItem;

class GameMap : public cocos2d::Node
{
public:
	CREATE_FUNC(GameMap);

	virtual void update(float delta) override;

	float getDistanceInPoint() const;
	float getDistanceInMeter() const;

	float getEntityLayerPositionX() const;

	const std::list<cocos2d::Node*>& getTerrains() const;

    void pauseMove();
    void resumeMove();

    void addScore(int value);
    int getScore() const;

	int getNumFever() const;
	bool isInFever() const;
	float getFeverPointsPercent() const;
	void addNumFever();

    bool isZhuGongDead() const;
	ZhuGong* getZhuGong() const;

	void addAutoCollectEffect(float time);
	void addQuickFlying(float time);
	void addJiaSuEffect(float time);
	void addFeiXingGuai();
	void addInvincibleEffect(float time);

	void setMoveSpeed(float speed);
	float getMoveSpeed() const;

	void addChildToEntityLayer(cocos2d::Node *node);

	void addDustAnimation(cocos2d::Node *node);

	cocos2d::TMXTiledMap* getCollisionData() const;

	void addOneCollectedObject(const std::string typeName);
	int getNumCollectedObject(const std::string typeName);

	void addNumDoubleJump();
	int getNumDoubleJump() const;

protected:
	GameMap();
	~GameMap();
	DISALLOW_COPY_AND_ASSIGN(GameMap);

	virtual bool init() override;

private:
	void addTouchListener();

	void addTerrain(const std::string &filename);
	void updateTerrain();

	void moveForward(float delta);

	void checkCreatePropItem(float delta);

	void checkCollision(float delta);

private:
	cocos2d::Node *_entitiesLayer;

	std::list<cocos2d::Node*> _terrains;
	float _topTerrainWidth;
	float _lastDistance;
	float _lastTerrainRight;

    ZhuGong *_zhugong;
    WuJiang *_wujiang;
	WenChen *_wenchen;

	float _moveSpeed;
	float _backgroundSpeedScale;
	float _mediumShotSpeedScale;
	float _closeShotSpeedScale;
	RepeatedBackground *_background;
	RepeatedBackground *_mediumShot;
	RepeatedBackground *_closeShot;

	float _distanceInPoint;
	float _pointToMeter;

    int _score;

	int _currentFeverPoints;
	int _maxFeverPoints;
	int _numFever;

	PropItem *_propItem;

	cocos2d::TMXTiledMap *_collisionData;

	std::map<std::string, int> _collectedObjects;

	int _numDoubleJump;
};
#endif // __TKP_GAME_MAP_H__