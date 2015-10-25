#include "GameData.h"

GameData *GameData::m_instance = 0;

GameData::GameData()
	:ballSpeed(2)
	, goldsNumber(0)
	, currcertSorce(0)
{}

GameData::~GameData()
{
	//destoryInstance();
}

GameData*GameData::getInstance()
{
	if (0 == m_instance)
	{
		m_instance = new GameData();
	}
	return m_instance;
}
void GameData::destoryInstance()
{
	m_instance = 0;
	delete m_instance;
}
