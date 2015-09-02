#ifndef __TKP_SCENE_SETTLEMENT_H__
#define __TKP_SCENE_SETTLEMENT_H__

#include "SceneBase.h"
#include "cocos2d.h"


class SceneSettlement : public SceneBase
{
public:
	CREATE_FUNC(SceneSettlement);

	void setFinished(bool isFinished);
	void setScore(int score);

	virtual void initAfterCreate() override;

protected:
	SceneSettlement();
	~SceneSettlement();
	CC_DISALLOW_COPY_AND_ASSIGN(SceneSettlement);

	virtual bool init() override;
	virtual void initCallbackMap() override;
	virtual void onKeyBackReleased() override;

private:
	cocos2d::Node *_root;

	bool _isFinished;
	int _score;
};



#endif // __TKP_SCENE_SETTLEMENT_H__