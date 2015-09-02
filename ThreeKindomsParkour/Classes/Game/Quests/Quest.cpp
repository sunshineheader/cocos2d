#include "Quest.h"

void Quest::setIconName(const std::string &iconName)
{
	_iconName = iconName;
}

const std::string& Quest::getIconName() const
{
	return _iconName;
}

void Quest::setQuestName(const std::string &questName)
{
	_questName = questName;
}

const std::string& Quest::getQuestName() const
{
	return _questName;
}

void Quest::setDescription(const std::string &description)
{
	_description = description;
}

const std::string& Quest::getDescription() const
{
	return _description;
}