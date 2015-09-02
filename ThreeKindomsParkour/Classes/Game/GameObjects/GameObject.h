#ifndef __TKP_ITEM_H__
#define __TKP_ITEM_H__

#include "cocos2d.h"

#include "Math/Polygon.h"

#include "cocostudio\CocoStudio.h"

class GameMap;

class GameObject : public cocos2d::Node
{
public:
	void setTypeName(const std::string &typeName);
	std::string getTypeName() const;

    void setNeedRemove(bool isNeedRemove);
	bool isNeedRemove() const;

	void setScore(int score);
	int getScore() const;

	void setGameMap(GameMap *gameMap);
	GameMap* getGameMap() const;

	void setAttackRegion(const std::vector<float> &vertices);
	void setDefenceRegion(const std::vector<float> &vertices);
	Math::Polygon& getAttackRegion();
	Math::Polygon& getDefenceRegion();

	virtual void die();

protected:
	GameObject();
	virtual ~GameObject();

protected:
	std::string _typeName;
	bool _isNeedRemove;
	int _score;

	GameMap *_gameMap;

protected:
	Math::Polygon _attackRegion;
	Math::Polygon _defenceRegion;

public:
	cocostudio::Armature *_armature;
	cocostudio::ArmatureAnimation *_animation;
};

#endif // __TKP_ITEM_H__