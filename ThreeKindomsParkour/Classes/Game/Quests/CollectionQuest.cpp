#include "CollectionQuest.h"
#include "Scenes/SceneGame.h"
#include "Game/GameMap.h"

#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;


CollectionQuest::CollectionQuest()
: _currentNumber(0)
, _targetNumber(0)

, _count(nullptr)
{
}

CollectionQuest::~CollectionQuest()
{
}

void CollectionQuest::init(SceneGame *game)
{
	auto quest = game->getChildByName("GUI")->getChildByName("QuestStats")->getChildByName("Quest");
	auto icon = dynamic_cast<Sprite*>(quest->getChildByName("Icon"));
	auto questName = dynamic_cast<Text*>(quest->getChildByName("QuestName"));
	_count = dynamic_cast<Text*>(quest->getChildByName("Count"));

	icon->setTexture(getIconName());
	questName->setString(getQuestName());
	_count->setString("0/0");
}

void CollectionQuest::update(SceneGame *game)
{
	_currentNumber = game->getGameMap()->getNumCollectedObject(getCollectedTypeName());
	_count->setString(String::createWithFormat("%d/%d", _currentNumber, _targetNumber)->getCString());
}

bool CollectionQuest::isCompleted() const
{
	return _currentNumber >= _targetNumber;
}


void CollectionQuest::setCollectedTypeName(const std::string &collectedTypeName)
{
	_collectedTypeName = collectedTypeName;
}

const std::string& CollectionQuest::getCollectedTypeName() const
{
	return _collectedTypeName;
}

void CollectionQuest::setTargetNumber(int number)
{
	_targetNumber = number;
}

int CollectionQuest::getTargetNumber() const
{
	return _targetNumber; 
}