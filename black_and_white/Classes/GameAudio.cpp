#include "GameAudio.h"
#include "SimpleAudioEngine.h"
#include "json\reader.h"
#include "json\document.h"
#include "json\writer.h"
#include "json\stringbuffer.h"
#include "GameDefinition.h"
#include "MusicInfoUtil.h"
using namespace CocosDenshion;
using namespace cocos2d;

GameAudio*GameAudio::_instance = nullptr;

GameAudio::GameAudio()
{
	this->init();
}


void GameAudio::init()
{
	//CCLOG("GameAudio init");
	music_index = 0;
	currentMusic_Type = rand() % 7;
	this->prepare();
	MusicInfoUtil::getInstance();
}


GameAudio*GameAudio::getInstance()
{
	if (_instance == 0)
	{
		_instance = new GameAudio();
	}
	return _instance;
	delete _instance;
}

void GameAudio::playsounds()
{
	if (music_index<MusicInfoUtil::getInstance()->getMusicInfo(currentMusic_Type).size()-1){
		music_index++;
	}
	else{
		int type = rand() % 7;
		while (type == currentMusic_Type)
		{
			type = rand() % 7;
		}

		currentMusic_Type = type;
		music_index = 0;
	}
	string name = "res/piano/"+MusicInfoUtil::getInstance()->getMusicInfo(currentMusic_Type).at(music_index);
	//std::string my_sorce_sort = ChineseWord("pai") + String::createWithFormat("%d", currcert_sort)->_string + ChineseWord("ming");
	//CCLOG( name.c_str());
	SimpleAudioEngine::getInstance()->playEffect(name.c_str(), false);

}

void GameAudio::playerror()
{
	SimpleAudioEngine::getInstance()->playEffect("error_piano.m4a", false);
}

void GameAudio::prepare()
{
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/1.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/2.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/3.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/4.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/5.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/6.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/7.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/8.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/9.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/10.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/11.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/12.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/13.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/14.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/15.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/16.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/17.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/18.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/19.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/20.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/21.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/20.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/21.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/22.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/23.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/24.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/25.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("res/piano/26.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("error_piano.m4a");

}

