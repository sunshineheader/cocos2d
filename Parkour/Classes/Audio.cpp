#include "Audio.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"

Audio* Audio::m_instance = nullptr;
Audio* Audio::getInstance(){
	if(m_instance == nullptr){
		m_instance = new Audio();
	}
	return m_instance;
}

void Audio::playBGM(char* soundName){
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(soundName,true);
	
	if(GAMEDATA::getInstance()->getMusicState()){
		  CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic(); 
	}else{
	  CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic(); 
	}
}

void Audio::playSound(char* soundName){
	if(GAMEDATA::getInstance()->getSoundState()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName,false);
	}
}

void Audio::prepare(){
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/game_bg.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/lobby_bg.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/active.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/game_start.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/gold.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/jump.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/paddle_hit.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/pay_result_fail.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/pay_result_success.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/result_fail.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/result_success.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/sign_in_success.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/sign_in.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/upgrade_btn.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/upgrade_success.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/use_prop.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.6f);
}
