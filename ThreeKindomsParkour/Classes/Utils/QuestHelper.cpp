#include "QuestHelper.h"
#include "UserData.h"

USING_NS_CC;
using namespace std;

static const char *s_kQuestDataFilepath = "Data/Quests/json";


QuestHelper* QuestHelper::getInstance()
{
	static QuestHelper instance;

	return &instance;
}

QuestHelper::QuestHelper()
{
	auto content = FileUtils::getInstance()->getStringFromFile(s_kQuestDataFilepath);
	_doc.Parse<0>(content.c_str());
	if (_doc.HasParseError())
	{
		CCLOG("<QuestHelper>: PARSE %s ERROR!", s_kQuestDataFilepath);
	}
}

QuestHelper::~QuestHelper()
{
}

std::string QuestHelper::getCurrentQuestIconName()
{
	if (_doc.HasMember("Quests") || _doc.HasMember("IconNames"))
	{
		CCLOG("<QuestHelper>: Error Data File.");
		return "";
	}

	const auto &quests = _doc["Quests"];
	const auto &quest = quests[UserData::getInstance()->getCurrentLevel() - 1];
	const string majorType = quest["MajorType"].GetString();
	const string minorType = quest["MinorType"].GetString();
	const string typeName = majorType + minorType;

	return "";
}

std::string QuestHelper::getCurrentQuestName()
{
	return "";
}

Quest* QuestHelper::createCurrentQuest()
{
	return nullptr;
}