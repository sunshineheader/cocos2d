#include "GameAudio.h"

GameAudio * GameAudio::m_Instance = 0;

GameAudio::GameAudio()
{
}

GameAudio::~GameAudio()
{
	destoryInstance();
}

GameAudio * GameAudio::getInstance()
{
	if (nullptr == m_Instance)
	{
		m_Instance = new GameAudio();
	}
	return m_Instance;
}
void   GameAudio::destoryInstance()
{
	m_Instance = nullptr;
	delete m_Instance;
}

void GameAudio::LoadingMusic()
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/game_bg.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/sfx_die.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/4.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/sfx_point.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/sfx_swooshing.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/sfx_wing.ogg");
}
void GameAudio::playBackgroundMusic()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/game_bg.mp3",-1);
}
void GameAudio::stopBackgroundMusic()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
}

void GameAudio::playDieEffect()
{
	SimpleAudioEngine::getInstance()->playEffect("Music/sfx_die.ogg");
}
void GameAudio::playHitEffect()
{
	SimpleAudioEngine::getInstance()->playEffect("Music/4.mp3");
}
void GameAudio::playPointEffect()
{
	SimpleAudioEngine::getInstance()->playEffect("Music/sfx_point.ogg");
}
void GameAudio::playSwooshingEffect()
{
	SimpleAudioEngine::getInstance()->playEffect("Music/sfx_swooshing.ogg");
}
void GameAudio::playWingEffect()
{
	SimpleAudioEngine::getInstance()->playEffect("Music/sfx_wing.ogg");
}