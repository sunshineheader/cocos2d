#ifndef __TKP_KILL_QUEST_H__
#define __TKP_KILL_QUEST_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include <string>
#include "Quest.h"

class KillQuest : public Quest
{
public:
	enum class KillType
	{
		House,
		SharpBall,
		FireBall,
		SpearSoldier,
		ShieldSoldier,
		Block,
		Spiling
	};

public:
	KillQuest();
	virtual ~KillQuest();

	virtual void init(SceneGame *game);
	virtual void update(SceneGame *game);
	virtual bool isCompleted() const;

	void setKillType(KillType type);
	KillType getKillType() const;

	void setTargetNumber(int number);
	int getTargetNumber() const;

private:
	KillType	_killType;
	int			_targetNumber;
	int			_currentNumber;

	cocos2d::ui::Text *_count;
};

#endif // __TKP_KILL_QUEST_H__