#ifndef __TKP_RACING_QUEST_H__
#define __TKP_RACING_QUEST_H__

#include "Quest.h"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include <string>

class RacingQuest : public Quest
{
public:
	enum class RacingType
	{
		Distance,
		Score,
		Fever,
		DoubleJump
	};

public:
	RacingQuest();
	virtual ~RacingQuest();

	virtual void init(SceneGame *game);
	virtual void update(SceneGame *game);
	virtual bool isCompleted() const;

	void setRacingType(RacingType type);
	RacingType getRacingType() const;

	void setTargetNumber(int number);
	int getTargetNumber() const;

private:
	RacingType	_racingType;
	int			_targetNumber;
	int			_currentNumber;

	cocos2d::ui::Text *_count;
};

#endif // __TKP_RACING_QUEST_H__