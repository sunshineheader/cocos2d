#include "KillQuest.h"
#include "Scenes/SceneGame.h"
#include "Game/GameMap.h"

#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;


KillQuest::KillQuest()
{
}

KillQuest::~KillQuest()
{
}

void KillQuest::init(SceneGame *game)
{
	auto quest = game->getChildByName("GUI")->getChildByName("QuestStats")->getChildByName("Quest");
	auto icon = dynamic_cast<Sprite*>(quest->getChildByName("Icon"));
	auto questName = dynamic_cast<Text*>(quest->getChildByName("QuestName"));
	_count = dynamic_cast<Text*>(quest->getChildByName("Count"));

	icon->setTexture(getIconName());
	questName->setString(getQuestName());
	_count->setString("0/0");
}

void KillQuest::update(SceneGame *game)
{
	_count->setString(String::createWithFormat("%d/%d", _currentNumber, _targetNumber)->getCString());
}

bool KillQuest::isCompleted() const
{
	return _currentNumber >= _targetNumber;
}

void KillQuest::setKillType(KillType type)
{
	_killType = type;
}

KillQuest::KillType KillQuest::getKillType() const
{
	return _killType;
}

void KillQuest::setTargetNumber(int number)
{
	_targetNumber = number;
}

int KillQuest::getTargetNumber() const
{
	return _targetNumber;
}