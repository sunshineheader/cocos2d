#ifndef __TKP_QUEST_HELPER_H__
#define __TKP_QUEST_HELPER_H__

#include "cocos2d.h"

#include "json/document.h"
#include "json/rapidjson.h"

class Quest;

class QuestHelper
{
public:
	static QuestHelper* getInstance();

	std::string getCurrentQuestIconName();
	std::string getCurrentQuestName();

	Quest* createCurrentQuest();

protected:
	QuestHelper();
	~QuestHelper();
	CC_DISALLOW_COPY_AND_ASSIGN(QuestHelper);

private:
	rapidjson::Document _doc;
};



#endif // __TKP_QUEST_HELPER_H__