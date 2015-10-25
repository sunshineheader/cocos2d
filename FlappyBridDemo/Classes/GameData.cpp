#include "GameData.h"
#include "cocos2d.h"
using namespace cocos2d;

GameData*GameData::m_Instance = 0;

GameData::GameData()
	: m_CurrcertSource(0)
	, m_HistorySource(0)
	, m_CurrcertRank(0)
	, m_HistoryRank(0)
	, m_GoldNumber(0)
	, m_MoveSpeed(0)
	, m_AllGoldNumber(0)
	, m_MusicState(true)
	, m_SoundState(true)
{}

GameData::~GameData()
{
	destoryInstance();
}

GameData * GameData::getInstance()
{
	if (0 == m_Instance)
	{
		m_Instance = new GameData();
	}
	return m_Instance;
	
}

void GameData::destoryInstance()
{
	m_Instance = nullptr;
	delete m_Instance;
}

void GameData::SaveCurrcertSource()
{
	UserDefault::getInstance()->setIntegerForKey("CurrcertSorce", getCurrcertSource());
}

void GameData::SaveHistorySource()
{
	UserDefault::getInstance()->setIntegerForKey("HistorySource", getHistorySource());
}

void GameData::SaveCurrcertRank()
{
	UserDefault::getInstance()->setIntegerForKey("CurrcertRank", getHistorySource());
}

void GameData::SaveHistoryRank()
{
	UserDefault::getInstance()->setIntegerForKey("HistoryRank", getHistorySource());
}

void GameData::SaveCurrcertGoldNumber()
{
	UserDefault::getInstance()->setIntegerForKey("CurrcertGoldNumber", getGoldNumber());
}

void GameData::SaveAllGoldNumber()
{
	UserDefault::getInstance()->setIntegerForKey("AllGoldNumber", m_AllGoldNumber);
}

void GameData::SaveCurrcertSpeed()
{
	UserDefault::getInstance()->setIntegerForKey("MoveSpeed", getMoveSpeed());
}
void GameData::SaveMusicState()
{
	UserDefault::getInstance()->setBoolForKey("MusicState",getMusicState());
}
void GameData::SaveSoundState()
{
	UserDefault::getInstance()->setBoolForKey("SoundState", getSoundState());
}
int GameData::CompareSorce()
{
	int currecrtSorce = getCurrcertSource();
	int historySorce = UserDefault::getInstance()->getIntegerForKey("HistorySource");
	if (currecrtSorce >= historySorce)
	{
		setHistorySource(currecrtSorce);
		SaveHistorySource();
		return currecrtSorce;
	}
	return historySorce;

}
int GameData::CompareRank()
{
	int currcertRank = getCurrcertRank();
	int historyRank = UserDefault::getInstance()->getIntegerForKey("HistoryRank");
	if (currcertRank >= historyRank)
	{
		setHistoryRank(currcertRank);
		SaveHistoryRank();
		return currcertRank;
	}
	return historyRank;
}

int GameData::SaveAllGolds()
{
	m_AllGoldNumber = UserDefault::getInstance()->getIntegerForKey("AllGoldNumber");
	m_AllGoldNumber += getGoldNumber();
	SaveAllGoldNumber();
	return m_AllGoldNumber;
}
