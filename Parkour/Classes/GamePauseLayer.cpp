#include "GamePauseLayer.h"
#include "GAMEDATA.h"
#include "PlayerState.h"
#include "Player.h"
#include "cocos-ext.h" 
#include "GameState.h"
#include "GameStateInfo.h"
#include "MenuScene.h"
#include "Audio.h"

USING_NS_CC_EXT;

bool GamePauseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto bg = Sprite::createWithSpriteFrameName("more_game_bg.png");
	bg->setScaleX(0.644);
	bg->setScaleY(0.815);
	bg->setPosition(384,285);
	this->addChild(bg);

	auto title = Sprite::createWithSpriteFrameName("hint_title.png");
	title->setPosition(384,408);
	this->addChild(title);

	auto contiGameBtn = MenuItemImage::create(
		"dialog_conti_game_bg_normal.png",
		"dialog_conti_game_bg_click.png",
		CC_CALLBACK_0(GamePauseLayer::contiGame, this));
	auto contiGameMenu = Menu::create(contiGameBtn, NULL);
	contiGameMenu->setPosition(384,311);
	this->addChild(contiGameMenu);
	
	auto contiGameTxt = MenuItemImage::create(
		"dialog_conti_game_txt_normal.png",
		"dialog_conti_game_txt_click.png",
		CC_CALLBACK_0(GamePauseLayer::contiGame, this));
	auto contiGameTxtMenu = Menu::create(contiGameTxt, NULL);
	contiGameTxtMenu->setPosition(384,311);
	this->addChild(contiGameTxtMenu); 

	auto backMenuBtn = MenuItemImage::create(
		"dialog_resume_game_bg_normal.png",
		"dialog_resume_game_bg_click.png",
		CC_CALLBACK_0(GamePauseLayer::backMenu, this));
	auto cancelMenu = Menu::create(backMenuBtn, NULL);
	cancelMenu->setPosition(384,225);
	this->addChild(cancelMenu);
	
	auto backMenuTxt = MenuItemImage::create(
		"dialog_resume_game_txt_normal.png",
		"dialog_resume_game_txt_click.png",
		CC_CALLBACK_0(GamePauseLayer::backMenu, this));
	auto backTxtMenu = Menu::create(backMenuTxt, NULL);
	backTxtMenu->setPosition(384,225);
	this->addChild(backTxtMenu); 

	auto closeBtn = MenuItemImage::create(
		"dialog_close_normal.png",
		"dialog_close_click.png",
		CC_CALLBACK_0(GamePauseLayer::contiGame, this));
	auto closeMenu = Menu::create(closeBtn, NULL);
	closeMenu->setPosition(533,417);
	this->addChild(closeMenu);
	return true;
}

void GamePauseLayer::contiGame(){
	Audio::getInstance()->playSound("Music/paddle_hit.wav");
	this->setVisible(false);
	GameStateInfo::getInstance()->setGameState(Game_Playing);
}

void GamePauseLayer::backMenu(){
	Audio::getInstance()->playSound("Music/paddle_hit.wav");
	Director::getInstance()->replaceScene(TransitionFade::create(1,MenuScene::create()));
}
