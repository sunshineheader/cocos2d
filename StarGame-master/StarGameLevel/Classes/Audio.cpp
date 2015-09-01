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
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/music.ogg",true);
	if(GAMEDATA::getInstance()->getMusicState()){
		  CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}else{
	  CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

void Audio::playReadyGo(){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/readygo.ogg",false);}
}

void Audio::playPop(){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/pop.ogg",false);}
}

void Audio::playClick(){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/select.ogg",false);}
}


void Audio::playScore(){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		scoreId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/coin.ogg",false);}
}

void Audio::playCombo(int size){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		if(size < 5)
			return;
		if(size >= 9){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_3.ogg");
		}else if(size >= 7){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_2.ogg");
		}else {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_1.ogg");
		}
	}
}


void Audio::playNextGameRound(){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/NextGameRound.ogg",false);}
}

void Audio::playPropBomb(){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/Props_Bomb.ogg",false);}
}

void Audio::playPropRainbow(){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/Props_Rainbow.ogg",false);}
}

void Audio::playPropPlusTime(){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/Props_Paint.ogg",false);}
}

void Audio::playClear(){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/clear.ogg",false);}
}

void Audio::playBeep(){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/beep.ogg",false);}
}

void Audio::playLanding(){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/landing.ogg",false);}
}

void Audio::playUpgrade(){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/upgrade.ogg",false);}
}

void Audio::playSignin(){
	if(GAMEDATA::getInstance()->getSoundEffect()){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/sign_in.ogg",false);}
}


void Audio::prepare(){
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/music.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/readygo.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/pop.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_1.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_2.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_3.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/NextGameRound.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/Props_Bomb.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/Props_Rainbow.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/Props_Paint.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/clear.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/beep.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/landing.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/upgrade.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/coin.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Music/sign_in.ogg");
}
