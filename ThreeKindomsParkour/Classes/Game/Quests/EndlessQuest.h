#ifndef __TKP_ENDLESS_QUEST_H__
#define __TKP_ENDLESS_QUEST_H__


#include "Quest.h"

class EndlessQuest : public Quest
{
public:
	EndlessQuest();
	virtual ~EndlessQuest();

	virtual void init(SceneGame *game);
	virtual void update(SceneGame *game);
	virtual bool isCompleted() const;

};

#endif // __TKP_ENDLESS_QUEST_H__