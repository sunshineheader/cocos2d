#include "RacingQuest.h"
#include "Scenes/SceneGame.h"
#include "Game/GameMap.h"

#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;

RacingQuest::RacingQuest()
{
}

RacingQuest::~RacingQuest()
{
}

void RacingQuest::init(SceneGame *game)
{
	auto quest = game->getChildByName("GUI")->getChildByName("QuestStats")->getChildByName("Quest");
	auto icon = dynamic_cast<Sprite*>(quest->getChildByName("Icon"));
	auto questName = dynamic_cast<Text*>(quest->getChildByName("QuestName"));
	_count = dynamic_cast<Text*>(quest->getChildByName("Count"));

	icon->setTexture(getIconName());
	questName->setString(getQuestName());
	_count->setString("0/0");
}

void RacingQuest::update(SceneGame *game)
{
	switch (_racingType)
	{
	case RacingQuest::RacingType::Distance:
		_currentNumber = game->getGameMap()->getDistanceInMeter();
		break;
	case RacingQuest::RacingType::Score:
		_currentNumber = game->getGameMap()->getScore();
		break;
	case RacingQuest::RacingType::Fever:
		_currentNumber = game->getGameMap()->getNumFever();
		break;
	case RacingQuest::RacingType::DoubleJump:
		_currentNumber = game->getGameMap()->getNumDoubleJump();
		break;
	default:
		break;
	}
	_count->setString(String::createWithFormat("%d/%d", _currentNumber, _targetNumber)->getCString());
}

bool RacingQuest::isCompleted() const
{
	return _currentNumber >= _targetNumber;
}

void RacingQuest::setRacingType(RacingType type)
{
	_racingType = type;
}

RacingQuest::RacingType RacingQuest::getRacingType() const
{
	return _racingType;
}

void RacingQuest::setTargetNumber(int number)
{
	_targetNumber = number;
}

int RacingQuest::getTargetNumber() const
{
	return _targetNumber;
}