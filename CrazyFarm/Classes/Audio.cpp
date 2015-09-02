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
	if(GAMEDATA::getInstance()->getMusicState()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName,false);
	}
}

void Audio::prepare(){
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGORUNDMUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(COUNTDOWN);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CLICK);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(FINISHTASK);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(QUICKFIND);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(REVIVE);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SELECTCORRECT);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SELECTERROR);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SELECTTIME);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SHOWPAYPOINT);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.4f);
}