#include "UserData.h"

USING_NS_CC;

UserData* UserData::getInstance()
{
	static UserData instance;

	return &instance;
}

UserData::UserData()
: _gameMode(SceneGame::GameMode::StageMode)
{
	reloadData();
}

UserData::~UserData()
{
	saveData();
	UserDefault::destroyInstance();
}

void UserData::reloadData()
{
	auto data = UserDefault::getInstance();

	_isAudioOn = data->getBoolForKey("isAudioOn", true);
	_currentLevel = data->getIntegerForKey("_currentLevel", 1);
}

void UserData::saveData()
{
	auto data = UserDefault::getInstance();

	data->setBoolForKey("isAudioOn", _isAudioOn);
	data->setIntegerForKey("_currentLevel", _currentLevel);

	data->flush();
}

bool UserData::isAudioOn() const
{
	return _isAudioOn;
}

void UserData::setAudioOn(bool isAudioOn)
{
	_isAudioOn = isAudioOn;
}

void UserData::setCurrentLevel(int index)
{
	_currentLevel = index;
}

void UserData::addOneLevel()
{
	_currentLevel += 1;
}

int UserData::getCurrentLevel() const
{
	return _currentLevel;
}

void UserData::setGameMode(SceneGame::GameMode gameMode)
{
	_gameMode = gameMode;
}

SceneGame::GameMode UserData::getGameMode() const
{
	return _gameMode;
}