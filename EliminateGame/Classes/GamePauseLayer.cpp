#include "GamePauseLayer.h"
#include "Audio.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
#include "GameState.h"

GamePauseLayer* GamePauseLayer::create(){
	GamePauseLayer* ret = new GamePauseLayer();
	if (ret && ret->init()){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}


bool GamePauseLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	//add sprite to this scene
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* pause_bg = Sprite::create("scene_abo.png");
	pause_bg->setAnchorPoint(ccp(0, 0));
	pause_bg->setPosition(0, 0);
	this->addChild(pause_bg);
	//add resume btn to this layer
	MenuItemImage* resume_btn = MenuItemImage::create("btn_ret.png", "btn_ret.png", CC_CALLBACK_0(GamePauseLayer::resumeGame, this));
	Menu* resume_game = Menu::create(resume_btn, NULL);
	resume_game->setPosition(400, 745);
	this->addChild(resume_game);

	//add bg music btn to this layer
	MenuItemImage* musicBtnOn = MenuItemImage::create("btn_mus_on.png", "btn_mus_on.png");
	MenuItemImage* musicBtnOff = MenuItemImage::create("btn_mus_off.png", "btn_mus_off.png");
	MenuItemToggle* musicTog = MenuItemToggle::createWithTarget(this, menu_selector(GamePauseLayer::getMusicState), musicBtnOn, musicBtnOff, NULL);
	if (GAMEDATA::getInstance()->getMusicState())
	{
		musicTog->setSelectedIndex(0);
	}
	else
	{
		musicTog->setSelectedIndex(1);
	}
	Menu* musicMenu = Menu::create(musicTog, NULL);
	musicMenu->setPosition(320, 455);
	this->addChild(musicMenu);

	//add sound btn to this layer
	MenuItemImage* soundBtnOn = MenuItemImage::create("btn_mus_on.png", "btn_mus_on.png");
	MenuItemImage* soundBtnOff = MenuItemImage::create("btn_mus_off.png", "btn_mus_off.png");
	MenuItemToggle* soundTog = MenuItemToggle::createWithTarget(this, menu_selector(GamePauseLayer::getSoundState), soundBtnOn, soundBtnOff, NULL);
	if (GAMEDATA::getInstance()->getSoundState())
	{
		soundTog->setSelectedIndex(0);
	}
	else
	{
		soundTog->setSelectedIndex(1);
	}
	Menu* soundMenu = Menu::create(soundTog, NULL);
	soundMenu->setPosition(320, 575);
	this->addChild(soundMenu);


	return true;
}
void GamePauseLayer::resumeGame(){
	// resume game
	GAMESTATE::getInstance()->setGamePause(true);
	Audio::getInstance()->playSound(CLICK);
	this->removeFromParentAndCleanup(true);
}


void GamePauseLayer::getMusicState(cocos2d::Ref* pSender){

	CCMenuItemToggle* temp = (CCMenuItemToggle*)pSender;
	if (temp->getSelectedIndex() == 1)
	{
		Audio::getInstance()->playSound(CLICK);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		GAMEDATA::getInstance()->setMusicState(false);

	}
	if (temp->getSelectedIndex() == 0)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		GAMEDATA::getInstance()->setMusicState(true);
	}
}

void GamePauseLayer::getSoundState(cocos2d::Ref* pSender){

	CCMenuItemToggle* temp = (CCMenuItemToggle*)pSender;
	if (temp->getSelectedIndex() == 1)
	{
		Audio::getInstance()->playSound(CLICK);
		GAMEDATA::getInstance()->setSoundState(false);

	}
	if (temp->getSelectedIndex() == 0)
	{
		GAMEDATA::getInstance()->setSoundState(true);
	}
}
