#include "SignInPrize.h"
#include "SignIn.h"
#include "MenuLayer.h"

bool SignInPrize::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto bg = Sprite::create("sign_in_prize_bg.png");
	bg->setPosition(400,240);
	this->addChild(bg);
	switch (SignIn::currentSignDay)
	{
	case 0:
		icon = Sprite::createWithSpriteFrameName("sign_in_day_1.png");
		icon->setPosition(400, 240);
		this->addChild(icon);
		break;
	case 1:
		icon = Sprite::createWithSpriteFrameName("sign_in_day_2.png");
		icon->setPosition(400, 240);
		this->addChild(icon);
		break;
	case 2:
		icon = Sprite::createWithSpriteFrameName("sign_in_day_3.png");
		icon->setPosition(400, 240);
		this->addChild(icon);
		break;

	case 3:
		icon = Sprite::createWithSpriteFrameName("sign_in_day_4.png");
		icon->setPosition(400, 240);
		this->addChild(icon);
		break;
	case 4:
		icon = Sprite::createWithSpriteFrameName("sign_in_day_5.png");
		icon->setPosition(400, 240);
		this->addChild(icon);
		break;
	case 5:
		icon = Sprite::createWithSpriteFrameName("sign_in_day_6.png");
		icon->setPosition(400, 240);
		this->addChild(icon);
		break;
	case 6:
		icon = Sprite::createWithSpriteFrameName("sign_in_day_7.png");
		icon->setPosition(400, 240);
		this->addChild(icon);
		break;
	case 7:
		icon = Sprite::createWithSpriteFrameName("sign_in_day_8.png");
		icon->setPosition(400, 240);
		this->addChild(icon);
		break;
	case 8:
		icon = Sprite::createWithSpriteFrameName("sign_in_day_9.png");
		icon->setPosition(400, 240);
		this->addChild(icon);
		break;
	case 9:
		icon = Sprite::createWithSpriteFrameName("sign_in_day_7.png");
		icon->setPosition(400, 240);
		this->addChild(icon);
		break;
	}

	auto startGameBtn = MenuItemImage::create(
		"dialog_conti_game_bg_normal.png",
		"dialog_conti_game_bg_click.png",
		CC_CALLBACK_0(SignInPrize::hideSelf, this));
	auto startGameMenu = Menu::create(startGameBtn, NULL);
	startGameMenu->setPosition(400,90);
	this->addChild(startGameMenu);

	auto startGameTxt = MenuItemImage::create(
		"sign_in_confirm_normal_txt.png",
		"sign_in_confirm_cllick_txt.png",
		CC_CALLBACK_0(SignInPrize::hideSelf, this));
	auto startGameTxtMenu = Menu::create(startGameTxt, NULL);
	startGameTxtMenu->setPosition(400,90);
	this->addChild(startGameTxtMenu);

	return true;
}

void SignInPrize::hideSelf(){
	this->setVisible(false);
	MenuLayer::canStartGame = true;
}
