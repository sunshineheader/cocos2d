#ifndef __TKP_PROP_ITEM_H__
#define __TKP_PROP_ITEM_H__

#include "GameObject.h"

class GameMap;

class PropItem : public GameObject
{
public:
	enum class PropType {
		CiTie,
		BaGuaDun,
		FeiNiao,
		FeiXingGuai,
		JiaSu
	};

public:
	CREATE_FUNC(PropItem);

	void setSprite(cocos2d::Node *sprite);
	cocos2d::Node* getSprite() const;

	virtual void update(float delta);

	void setInitalPosition(const cocos2d::Vec2 &position);

	void setPropType(PropType type);
	PropType getPropType() const;

	void setMoveSpeed(float speed);

	void takeEffect(GameMap *gameMap);

protected:
	PropItem();
	virtual ~PropItem();
	CC_DISALLOW_COPY_AND_ASSIGN(PropItem);

	virtual bool init();

private:
	cocos2d::Node *_sprite;

	cocos2d::Vec2 _initialPosition;

	float _moveSpeed;

	PropType _propType;
};

#endif // __TKP_PROP_ITEM_H__