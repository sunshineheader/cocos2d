#include "ResultGold.h"
#include "GameData.h"
#include "Audio.h"
#include "CallAndroidMethod.h"

bool ResultGold::clickedUpgradeProp = false;
ResultGold* ResultGold::_instance = nullptr;
ResultGold::ResultGold(){
	this->init();
}

ResultGold* ResultGold::getInstance(){
	if (_instance == 0){
		_instance = new ResultGold();
	}
	return _instance;
}

void ResultGold::cleanInstance(){
	if (_instance != 0){
		_instance = 0;
	}
}


bool ResultGold::init(){
	if (!Node::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	playerGold = LabelAtlas::create(String::createWithFormat("%d", GAMEDATA::getInstance()->getGoldNum())->_string, "lobby_gold_num.png", 20, 21, 48);
	playerGold->setPosition(654, 412);
	playerGold->setAnchorPoint(Point(0, 0.5));
	this->addChild(playerGold);

	levelNum = LabelAtlas::create(String::createWithFormat("%d", GAMEDATA::getInstance()->getPlayerLevel())->_string, "lobby_level_num.png", 20, 24, 48);
	levelNum->setAnchorPoint(Point(0, 0.5));
	levelNum->setPosition(430, 412);
	this->addChild(levelNum);

	/*无敌功能*/
	auto superSecTxt = Sprite::createWithSpriteFrameName("lobby_sec_txt.png");
	superSecTxt->setPosition(621, 355);
	superSecTxt->setTag(1001);
	this->addChild(superSecTxt);

	MenuItemImage* superUpgradeBg = MenuItemImage::create();
	superUpgradeBg->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("lobby_upgrade_bg.png"));
	superUpgradeBg->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("lobby_upgrade_bg.png"));
	superUpgradeBg->setCallback(CC_CALLBACK_0(ResultGold::upgradeSuper, this));
	Menu* superMenu = Menu::create(superUpgradeBg, NULL);
	superMenu->setPosition(706, 340);
	superMenu->setTag(1002);
	this->addChild(superMenu);

	superUpgradeGold = LabelAtlas::create(String::createWithFormat("%d", GAMEDATA::getInstance()->getSuperUpgradeGold())->_string, "lobby_upgrade_num.png", 14, 16, 48);
	superUpgradeGold->setPosition(698, 340);
	superUpgradeGold->setAnchorPoint(Point(0, 0.5));
	this->addChild(superUpgradeGold);


	int superLevel = GAMEDATA::getInstance()->getSuperLevel();
	superTime1 = LabelAtlas::create(GAMEDATA::getInstance()->getShowSuperTime(), "lobby_prop_time_num.png", 19, 22, '0');
	superTime1->setPosition(600, 355);
	superTime1->setAnchorPoint(Point(1, 0.5));
	this->addChild(superTime1);
	if (superLevel == 1){
		superProgress = Sprite::create("lobby_progress_green.png", Rect(246, 0, 5, 21));
	}
	else{
		superProgress = Sprite::create("lobby_progress_green.png", Rect(251 - (superLevel - 1) * 20, 0, (superLevel - 1) * 20, 21));
	}
	superProgress->setAnchorPoint(Point(0, 0.5));
	superProgress->setPosition(445, 328);
	this->addChild(superProgress);

	/*磁铁功能*/
	auto magneticSecTxt = Sprite::createWithSpriteFrameName("lobby_sec_txt.png");
	magneticSecTxt->setPosition(621, 270);
	magneticSecTxt->setTag(1003);
	this->addChild(magneticSecTxt);

	MenuItemImage* magneticUpgradeBg = MenuItemImage::create();
	magneticUpgradeBg->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("lobby_upgrade_bg.png"));
	magneticUpgradeBg->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("lobby_upgrade_bg.png"));
	magneticUpgradeBg->setCallback(CC_CALLBACK_0(ResultGold::upgradeMagenic, this));
	Menu* magneticMenu = Menu::create(magneticUpgradeBg, NULL);
	magneticMenu->setPosition(706, 255);
	magneticMenu->setTag(1004);
	this->addChild(magneticMenu);

	magneticUpgradeGold = LabelAtlas::create(String::createWithFormat("%d", GAMEDATA::getInstance()->getMagneticUpgradeGold())->_string, "lobby_upgrade_num.png", 14, 16, 48);
	magneticUpgradeGold->setPosition(698, 255);
	magneticUpgradeGold->setAnchorPoint(Point(0, 0.5));
	this->addChild(magneticUpgradeGold);

	int magneticLevel = GAMEDATA::getInstance()->getMagneticLevel();

	magneticTime1 = LabelAtlas::create(GAMEDATA::getInstance()->getShowMagneticTime(), "lobby_prop_time_num.png", 19, 22, '0');
	magneticTime1->setPosition(600, 270);
	magneticTime1->setAnchorPoint(Point(1, 0.5));
	this->addChild(magneticTime1);

	if (magneticLevel == 1){
		magneticProgress = Sprite::create("lobby_progress_blue.png", Rect(246, 0, 5, 21));
	}
	else{
		magneticProgress = Sprite::create("lobby_progress_blue.png", Rect(251 - (magneticLevel - 1) * 20, 0, (magneticLevel - 1) * 20, 21));
	}
	magneticProgress->setAnchorPoint(Point(0, 0.5));
	magneticProgress->setPosition(445, 243);
	this->addChild(magneticProgress);

	/*潜能功能*/
	auto potentialSecTxt = Sprite::createWithSpriteFrameName("lobby_sec_txt.png");
	potentialSecTxt->setPosition(621, 185);
	potentialSecTxt->setTag(1005);
	this->addChild(potentialSecTxt);

	MenuItemImage* potentialUpgradeBg = MenuItemImage::create();
	potentialUpgradeBg->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("lobby_upgrade_bg.png"));
	potentialUpgradeBg->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("lobby_upgrade_bg.png"));
	potentialUpgradeBg->setCallback(CC_CALLBACK_0(ResultGold::upgradePotential, this));
	Menu* potentialMenu = Menu::create(potentialUpgradeBg, NULL);
	potentialMenu->setPosition(706, 170);
	potentialMenu->setTag(1006);
	this->addChild(potentialMenu);

	potentialUpgradeGold = LabelAtlas::create(String::createWithFormat("%d", GAMEDATA::getInstance()->getPotentialUpgradeGold())->_string, "lobby_upgrade_num.png", 14, 16, 48);
	potentialUpgradeGold->setPosition(698, 170);
	potentialUpgradeGold->setAnchorPoint(Point(0, 0.5));
	this->addChild(potentialUpgradeGold);

	int potentialLevel = GAMEDATA::getInstance()->getPotentialLevel();

	potentialTime1 = LabelAtlas::create(GAMEDATA::getInstance()->getShowPotentialTime(), "lobby_prop_time_num.png", 19, 22, '0');
	potentialTime1->setPosition(600, 185);
	potentialTime1->setAnchorPoint(Point(1, 0.5));
	this->addChild(potentialTime1);
	if (potentialLevel == 1){
		potentialProgress = Sprite::create("lobby_progress_orange.png", Rect(246, 0, 5, 21));
	}
	else{
		potentialProgress = Sprite::create("lobby_progress_orange.png", Rect(251 - (potentialLevel - 1) * 20, 0, (potentialLevel - 1) * 20, 21));
	}
	potentialProgress->setAnchorPoint(Point(0, 0.5));
	potentialProgress->setPosition(445, 158);
	this->addChild(potentialProgress);

	if (superLevel == 11){
		superSecTxt->setVisible(true);
		superUpgradeBg->setVisible(false);
		superTime1->setVisible(true);
		superUpgradeGold->setVisible(false);
	}

	if (magneticLevel == 11){
		magneticSecTxt->setVisible(true);
		magneticUpgradeBg->setVisible(false);
		magneticTime1->setVisible(true);
		magneticUpgradeGold->setVisible(false);
	}

	if (potentialLevel == 11){
		potentialSecTxt->setVisible(true);
		potentialUpgradeBg->setVisible(false);
		potentialTime1->setVisible(true);
		potentialUpgradeGold->setVisible(false);
	}

	//道具数字显示
	Sprite* sup_num_bg = Sprite::create("prop_num_bg.png");
	sup_num_bg->setPosition(ccp(395, 365));
	this->addChild(sup_num_bg);
	prop_sup_num = LabelAtlas::create(String::createWithFormat("%d", GAMEDATA::getInstance()->getSuperPropNum())->_string, "prop_num.png", 13, 15, '0');
	prop_sup_num->setPosition(ccp(389, 358));
	this->addChild(prop_sup_num);

	Sprite* mag_num_bg = Sprite::create("prop_num_bg.png");
	mag_num_bg->setPosition(ccp(395, 280));
	this->addChild(mag_num_bg);
	prop_mag_num = LabelAtlas::create(String::createWithFormat("%d", GAMEDATA::getInstance()->getMagneticPropNum())->_string, "prop_num.png", 13, 15, '0');
	prop_mag_num->setPosition(ccp(389, 273));
	this->addChild(prop_mag_num);

	Sprite* pot_num_bg = Sprite::create("prop_num_bg.png");
	pot_num_bg->setPosition(ccp(395, 195));
	this->addChild(pot_num_bg);
	prop_pot_num = LabelAtlas::create(String::createWithFormat("%d", GAMEDATA::getInstance()->getPotentialPropNum())->_string, "prop_num.png", 13, 15, '0');
	prop_pot_num->setPosition(ccp(389, 188));
	this->addChild(prop_pot_num);
	return true;
}

void ResultGold::refreshGold(){
	playerGold->setString(String::createWithFormat("%d", GAMEDATA::getInstance()->getGoldNum())->_string);
}

void ResultGold::refreshMagenicInfo(){
	int magneticLevel = GAMEDATA::getInstance()->getMagneticLevel();
	if (magneticLevel == 11){
		this->getChildByTag(1003)->setVisible(true);
		this->getChildByTag(1004)->setVisible(false);
		magneticTime1->setVisible(true);
		magneticUpgradeGold->setVisible(false);
	}
	magneticUpgradeGold->setString(String::createWithFormat("%d", GAMEDATA::getInstance()->getMagneticUpgradeGold())->_string);
	magneticTime1->setPosition(600, 270);
	magneticTime1->setString(GAMEDATA::getInstance()->getShowMagneticTime());
	magneticProgress->setTextureRect(Rect(251 - (magneticLevel - 1) * 20, 0, (magneticLevel - 1) * 20, 21));
}

void ResultGold::refreshSuperInfo(){
	int superLevel = GAMEDATA::getInstance()->getSuperLevel();
	if (superLevel == 11){
		this->getChildByTag(1001)->setVisible(true);
		this->getChildByTag(1002)->setVisible(false);
		superTime1->setVisible(true);
		superUpgradeGold->setVisible(false);
	}

	superUpgradeGold->setString(String::createWithFormat("%d", GAMEDATA::getInstance()->getSuperUpgradeGold())->_string);
	superTime1->setPosition(600, 355);
	superTime1->setString(GAMEDATA::getInstance()->getShowSuperTime());
	superProgress->setTextureRect(Rect(251 - (superLevel - 1) * 20, 0, (superLevel - 1) * 20, 21));
}

void ResultGold::refreshPotentialInfo(){
	int potentialLevel = GAMEDATA::getInstance()->getPotentialLevel();
	if (potentialLevel == 11){
		this->getChildByTag(1005)->setVisible(true);
		this->getChildByTag(1006)->setVisible(false);
		potentialTime1->setVisible(true);
		potentialUpgradeGold->setVisible(false);
	}
	potentialUpgradeGold->setString(String::createWithFormat("%d", GAMEDATA::getInstance()->getPotentialUpgradeGold())->_string);
	potentialTime1->setPosition(600, 185);
	potentialTime1->setString(GAMEDATA::getInstance()->getShowPotentialTime());
	potentialProgress->setTextureRect(Rect(251 - (potentialLevel - 1) * 20, 0, (potentialLevel - 1) * 20, 21));
}

void ResultGold::refreshPlayerLevel(){
	levelNum->setString(String::createWithFormat("%d", GAMEDATA::getInstance()->getPlayerLevel())->_string);
}


void ResultGold::upgradeSuper(){
	Audio::getInstance()->playSound("Music/upgrade_btn.ogg");
	int goldNum = GAMEDATA::getInstance()->getGoldNum();
	int upgradeGold = GAMEDATA::getInstance()->getSuperUpgradeGold();
	int level = GAMEDATA::getInstance()->getSuperLevel();
	if (goldNum >= upgradeGold){
		GAMEDATA::getInstance()->setGoldNum(goldNum - upgradeGold);
		GAMEDATA::getInstance()->setSuperLevel(level + 1);
		ResultGold::getInstance()->refreshSuperInfo();
		ResultGold::getInstance()->refreshGold();
		GAMEDATA::getInstance()->setCostGoldNums(GAMEDATA::getInstance()->getCostGoldNums() + upgradeGold);
		Audio::getInstance()->playSound("Music/upgrade_success.mp3");
	}
	else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (clickedUpgradeProp){
			return;
		}
		clickedUpgradeProp = true;
		CallAndroidMethod::getInstance()->pay(11);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum() + 50000);
		ResultGold::getInstance()->refreshGold();
#endif
	}
}

void ResultGold::upgradeMagenic(){
	int level = GAMEDATA::getInstance()->getMagneticLevel();
	Audio::getInstance()->playSound("Music/upgrade_btn.ogg");
	int goldNum = GAMEDATA::getInstance()->getGoldNum();
	int upgradeGold = GAMEDATA::getInstance()->getMagneticUpgradeGold();
	if (goldNum >= upgradeGold){
		GAMEDATA::getInstance()->setGoldNum(goldNum - upgradeGold);
		GAMEDATA::getInstance()->setMagneticLevel(level + 1);
		ResultGold::getInstance()->refreshMagenicInfo();
		ResultGold::getInstance()->refreshGold();
		GAMEDATA::getInstance()->setCostGoldNums(GAMEDATA::getInstance()->getCostGoldNums() + upgradeGold);
		Audio::getInstance()->playSound("Music/upgrade_success.mp3");
	}
	else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if(clickedUpgradeProp){
			return;
		}
		clickedUpgradeProp = true;
		CallAndroidMethod::getInstance()->pay(11);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum() + 50000);
		ResultGold::getInstance()->refreshGold();
#endif
	}
}

void ResultGold::upgradePotential(){
	int level = GAMEDATA::getInstance()->getPotentialLevel();
	Audio::getInstance()->playSound("Music/upgrade_btn.ogg");
	int goldNum = GAMEDATA::getInstance()->getGoldNum();
	int upgradeGold = GAMEDATA::getInstance()->getPotentialUpgradeGold();
	if (goldNum >= upgradeGold){
		GAMEDATA::getInstance()->setGoldNum(goldNum - upgradeGold);
		GAMEDATA::getInstance()->setPotentialLevel(level + 1);
		ResultGold::getInstance()->refreshPotentialInfo();
		ResultGold::getInstance()->refreshGold();
		GAMEDATA::getInstance()->setCostGoldNums(GAMEDATA::getInstance()->getCostGoldNums() + upgradeGold);
		Audio::getInstance()->playSound("Music/upgrade_success.mp3");
	}
	else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if(clickedUpgradeProp){
			return;
		}
		clickedUpgradeProp = true;
		CallAndroidMethod::getInstance()->pay(11);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum() + 50000);
		ResultGold::getInstance()->refreshGold();
#endif
	}
}

void ResultGold::refreshPropNum(){
	prop_sup_num->setString(String::createWithFormat("%d", GAMEDATA::getInstance()->getSuperPropNum())->_string);
	prop_mag_num->setString(String::createWithFormat("%d", GAMEDATA::getInstance()->getMagneticPropNum())->_string);;
	prop_pot_num->setString(String::createWithFormat("%d", GAMEDATA::getInstance()->getPotentialPropNum())->_string);;
}
