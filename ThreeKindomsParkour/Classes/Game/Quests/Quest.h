#ifndef __TKP_QUEST_H__
#define __TKP_QUEST_H__

#include <string>

class SceneGame;

class Quest
{
public:
	virtual ~Quest() { };

	virtual void init(SceneGame *game) = 0;
	virtual void update(SceneGame *game) = 0;
	virtual bool isCompleted() const = 0;

	void setIconName(const std::string &iconName);
	const std::string& getIconName() const;

	void setQuestName(const std::string &questName);
	const std::string& getQuestName() const;

	void setDescription(const std::string &description);
	const std::string& getDescription() const;

private:
	std::string _iconName;
	std::string _questName;
	std::string _description;
};


#endif // __TKP_QUEST_H__