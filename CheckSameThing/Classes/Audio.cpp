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

void Audio::playBGM(){
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGORUNDMUSIC, true);
	
	if(GAMEDATA::getInstance()->getMusicState()){
		  CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic(); 
	}else{
	  CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic(); 
	}
}

void Audio::playReadyGo(){
	if (GAMEDATA::getInstance()->getSoundState()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(readyGo, false);
	}
}

void Audio::playBtnEffect(){
	if (GAMEDATA::getInstance()->getSoundState()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CLICK, false);
	}

}

void Audio::cleanitem(){
	if (GAMEDATA::getInstance()->getSoundState()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(ELECTRICITY, false);
	}
}

void Audio::hititems(){
	if (GAMEDATA::getInstance()->getMusicState()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(HITITEM, false);
	}
}

void Audio::timeover(){

	if (GAMEDATA::getInstance()->getMusicState()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(TIMEOVER, false);
	}
}

void Audio::playSound(char* soundName){
	if(GAMEDATA::getInstance()->getMusicState()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(soundName,false);
	}
}



void Audio::prepare(){
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGORUNDMUSIC);

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(CLICK);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(readyGo);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(ELECTRICITY);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(HITITEM);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(TIMEOVER);
	
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.4f);
}