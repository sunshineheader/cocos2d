#ifndef __TKP_SCORE_ITEM_H__
#define __TKP_SCORE_ITEM_H__

#include "GameObject.h"

class ScoreItem : public GameObject
{
public:
	CREATE_FUNC(ScoreItem);

	void setCollecting(bool isCollecting);
	bool isCollecting() const;

	void setSprite(cocos2d::Node *sprite);
	cocos2d::Node* getSprite() const;

protected:
	ScoreItem();
	virtual ~ScoreItem();
	CC_DISALLOW_COPY_AND_ASSIGN(ScoreItem);

	virtual bool init();

private:
	bool _isCollecting;

	cocos2d::Node *_sprite;
};

#endif // __TKP_SCORE_ITEM_H__