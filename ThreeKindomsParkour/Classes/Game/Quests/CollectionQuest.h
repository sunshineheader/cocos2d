#ifndef __TKP_COLLECTION_QUEST_H__
#define __TKP_COLLECTION_QUEST_H__

#include "Quest.h"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include <string>

class CollectionQuest : public Quest
{
public:

	CollectionQuest();
	virtual ~CollectionQuest();

	virtual void init(SceneGame *game);
	virtual void update(SceneGame *game);
	virtual bool isCompleted() const;

	void setCollectedTypeName(const std::string &collectedTypeName);
	const std::string& getCollectedTypeName() const;

	void setTargetNumber(int number);
	int getTargetNumber() const;

private:
	std::string _collectedTypeName;
	int			_targetNumber;
	int			_currentNumber;

	cocos2d::ui::Text *_count;
};

#endif // __TKP_COLLECTION_QUEST_H__