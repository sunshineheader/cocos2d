#include "QuitLayer.h"
#include "GAMEDATA.h"
#include "Audio.h"

bool QuitLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto bg = Sprite::createWithSpriteFrameName("more_game_bg.png");
	bg->setScaleX(0.76);
	bg->setScaleY(0.81);
	bg->setPosition(384,287);
	this->addChild(bg);

	auto desc = Sprite::createWithSpriteFrameName("quit_desc.png");
	desc->setPosition(390,291);
	this->addChild(desc);

	auto title = Sprite::createWithSpriteFrameName("quit_title.png");
	title->setPosition(385,407);
	this->addChild(title);

	auto quitBtn = MenuItemImage::create(
		"dialog_quit_bg_normal.png",
		"dialog_quit_bg_click.png",
		CC_CALLBACK_0(QuitLayer::quit, this));
	auto quitMenu = Menu::create(quitBtn, NULL);
	quitMenu->setPosition(273,197);
	this->addChild(quitMenu);
	
	auto quitTxt = MenuItemImage::create(
		"dialog_quit_txt_normal.png",
		"dialog_quit_txt_click.png",
		CC_CALLBACK_0(QuitLayer::quit, this));
	auto quitTxtMenu = Menu::create(quitTxt, NULL);
	quitTxtMenu->setPosition(273,197);
	this->addChild(quitTxtMenu); 

	auto cancelBtn = MenuItemImage::create(
		"dialog_conti_bg_normal.png",
		"dialog_conti_bg_click.png",
		CC_CALLBACK_0(QuitLayer::cancel, this));
	auto cancelMenu = Menu::create(cancelBtn, NULL);
	cancelMenu->setPosition(493,197);
	this->addChild(cancelMenu);
	
	auto cancelTxt = MenuItemImage::create(
		"dialog_conti_txt_normal.png",
		"dialog_conti_txt_click.png",
		CC_CALLBACK_0(QuitLayer::cancel, this));
	auto cancelTxtMenu = Menu::create(cancelTxt, NULL);
	cancelTxtMenu->setPosition(493,197);
	this->addChild(cancelTxtMenu); 

	auto closeBtn = MenuItemImage::create(
		"dialog_close_normal.png",
		"dialog_close_click.png",
		CC_CALLBACK_0(QuitLayer::cancel, this));
	auto closeMenu = Menu::create(closeBtn, NULL);
	closeMenu->setPosition(561,416);
	this->addChild(closeMenu);

	return true;
}

void QuitLayer::cancel()
{
	Audio::getInstance()->playSound("Music/paddle_hit.wav");
	this->setVisible(false);
}

void QuitLayer::quit()
{
	Audio::getInstance()->playSound("Music/paddle_hit.wav");
	Director::getInstance()->end();
}
