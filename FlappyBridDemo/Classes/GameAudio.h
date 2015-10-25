#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;

class GameAudio {

public:
	GameAudio();
	~GameAudio();
	static GameAudio * getInstance();
	static void    destoryInstance();
public:
	void LoadingMusic();
	void playBackgroundMusic();
	void stopBackgroundMusic();
	void playDieEffect();
	void playHitEffect();
	void playPointEffect();
	void playSwooshingEffect();
	void playWingEffect();
private:
	static GameAudio * m_Instance;



};

