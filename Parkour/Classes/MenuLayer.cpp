#include "MenuLayer.h"
#include "GameScene.h"
#include "Audio.h"
#include "TollgateScene.h"
#include "Chinese.h"
#include "CallAndroidMethod.h"
#include "SimpleAudioEngine.h"
#include "ResultGold.h"
#include "Def.h"
#include "GameStateInfo.h"
#include "GameState.h"

using namespace cocos2d;

bool MenuLayer::needShowMoreGame = false;
bool MenuLayer::canStartGame = false;
bool MenuLayer::showSignInPrize = false;
bool MenuLayer::passPropCheck = false;

bool MenuLayer::init(){
	if (!Layer::init()){
		return false;
	}
	Audio::getInstance()->prepare();
	canStartGame = false;
	showSignInPrize = false;
	isShowSuper = false;
	isShowMagnetic = false;
	isShowPotential = false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sign_day_prop.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("prop_light.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("run.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dialog.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("lobby.plist");
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_backgroundLayer = BackgroundLayer::create();
	this->addChild(m_backgroundLayer, -1);

	auto bg = TMXTiledMap::create("map_0.tmx");
	this->addChild(bg);


	Vector<SpriteFrame*> m_runFrames;
	SpriteFrame* frame1;
	for (int i = 0; i < 9; i++){
		frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("run_%d.png", i + 1)->_string);
		m_runFrames.pushBack(frame1);
	}
	auto animation1 = Animation::createWithSpriteFrames(m_runFrames, 0.06f);
	auto runAnimate = RepeatForever::create(Animate::create(animation1));

	if (GAMEDATA::getInstance()->getPlayerLevel() < 29){
		auto missionBg = Sprite::createWithSpriteFrameName("mission_bg.png");
		missionBg->setPosition(218, 318);
		missionBg->setScaleX(1.2f);
		this->addChild(missionBg);

		auto mission = LabelBMFont::create(ChineseWord(String::createWithFormat("mission_%d",
			GAMEDATA::getInstance()->getPlayerLevel())->_string.c_str()), "mission.fnt");
		mission->setPosition(218, 330);
		this->addChild(mission);
	}

	auto player = Sprite::createWithSpriteFrameName("run_1.png");
	player->setPosition(123, 227);
	this->addChild(player);
	//player->runAction(runAnimate);

	auto level = Sprite::createWithSpriteFrameName("lobby_level.png");
	level->setPosition(404, 412);
	this->addChild(level);

	auto gold = Sprite::createWithSpriteFrameName("lobby_gold.png");
	gold->setPosition(638, 412);
	this->addChild(gold);

	auto goldNum = ResultGold::getInstance();
	ResultGold::getInstance()->refreshPropNum();
	this->addChild(goldNum, 2);

	auto superBg = Sprite::createWithSpriteFrameName("lobby_prop_bg.png");
	superBg->setPosition(576, 340);
	this->addChild(superBg);

	auto superProgressBg = Sprite::createWithSpriteFrameName("lobby_progress_bg.png");
	superProgressBg->setPosition(516, 340);
	this->addChild(superProgressBg);

	auto superTxt = Sprite::createWithSpriteFrameName("lobby_super_time_txt.png");
	superTxt->setPosition(495, 355);
	this->addChild(superTxt);

	superIcon = Sprite::createWithSpriteFrameName("lobby_prop_super.png");
	superIcon->setPosition(416.5, 340);
	this->addChild(superIcon);

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = CC_CALLBACK_2(MenuLayer::upgradeSuper, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, superBg);

	auto magneticBg = Sprite::createWithSpriteFrameName("lobby_prop_bg.png");
	magneticBg->setPosition(576, 255);
	this->addChild(magneticBg);

	auto magneticProgressBg = Sprite::createWithSpriteFrameName("lobby_progress_bg.png");
	magneticProgressBg->setPosition(516, 255);
	this->addChild(magneticProgressBg);

	auto magneticTxt = Sprite::createWithSpriteFrameName("lobby_magnetic_time_txt.png");
	magneticTxt->setPosition(495, 270);
	this->addChild(magneticTxt);

	magneticIcon = Sprite::createWithSpriteFrameName("lobby_prop_magnetic.png");
	magneticIcon->setPosition(416.5, 255);
	this->addChild(magneticIcon);

	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = CC_CALLBACK_2(MenuLayer::upgradeMagnetic, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, magneticBg);


	auto potentialBg = Sprite::createWithSpriteFrameName("lobby_prop_bg.png");
	potentialBg->setPosition(576, 170);
	this->addChild(potentialBg);

	auto potentialProgressBg = Sprite::createWithSpriteFrameName("lobby_progress_bg.png");
	potentialProgressBg->setPosition(516, 170);
	this->addChild(potentialProgressBg);

	auto potentialTxt = Sprite::createWithSpriteFrameName("lobby_potential_time_txt.png");
	potentialTxt->setPosition(495, 185);
	this->addChild(potentialTxt);

	potentialIcon = Sprite::createWithSpriteFrameName("lobby_prop_potential.png");
	potentialIcon->setPosition(416.5, 170);
	this->addChild(potentialIcon);

	auto listener3 = EventListenerTouchOneByOne::create();
	listener3->onTouchBegan = CC_CALLBACK_2(MenuLayer::upgradePotential, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener3, potentialBg);

	auto startGameBtn = MenuItemImage::create(
		"lobby_start_game_bg_normal.png",
		"lobby_start_game_bg_click.png",
		CC_CALLBACK_0(MenuLayer::startGame, this));
	auto startGameMenu = Menu::create(startGameBtn, NULL);
	startGameMenu->setPosition(580, 70);
	this->addChild(startGameMenu);

	auto startGameTxt = MenuItemImage::create(
		"lobby_start_game_normal.png",
		"lobby_start_game_click.png",
		CC_CALLBACK_0(MenuLayer::startGame, this));
	auto startGameTxtMenu = Menu::create(startGameTxt, NULL);
	startGameTxtMenu->setPosition(580, 70);
	this->addChild(startGameTxtMenu);

	Sprite* super_not_select = Sprite::create("prop_not_select.png");
	super_not_select->setPosition(ccp(432, 320));
	this->addChild(super_not_select);

	Sprite* magnetic_not_select = Sprite::create("prop_not_select.png");
	magnetic_not_select->setPosition(ccp(432, 236));
	this->addChild(magnetic_not_select);

	Sprite* potential_not_select = Sprite::create("prop_not_select.png");
	potential_not_select->setPosition(ccp(432, 150));
	this->addChild(potential_not_select);

	prop_select_icon = Sprite::create("prop_select.png");
	prop_select_icon->setVisible(false);
	this->addChild(prop_select_icon, 2);

	if (GAMEDATA::getInstance()->isSuperSelect()){
		prop_select_icon->setPosition(ccp(432, 320));
		prop_select_icon->setVisible(true);
	}
	else if (GAMEDATA::getInstance()->isMagneticSelect()){
		prop_select_icon->setPosition(ccp(432, 236));
		prop_select_icon->setVisible(true);
	}
	else if (GAMEDATA::getInstance()->isPotentialSelect()){
		prop_select_icon->setPosition(ccp(432, 150));
		prop_select_icon->setVisible(true);
	}

	auto quitLayer = QuitLayer::create();
	quitLayer->setTag(1008);
	quitLayer->setVisible(false);
	this->addChild(quitLayer, 30);


	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			showQuit();
			break;
		default:
			break;
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	signIn = SignIn::create();
	signIn->setVisible(false);
	this->addChild(signIn, 100);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	canStartGame = true;
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	
	if(GAMEDATA::getInstance()->isHasPaySignIn()){
		if(CallAndroidMethod::getInstance()->isSignToday()){
			canStartGame = true;
		}else{
			Audio::getInstance()->playSound("Music/sign_in.ogg");
			signIn->setVisible(true);
			canStartGame = true;
		}
	}else{
		if(!GAMEDATA::getInstance()->getHasShowSignInPay() && !CallAndroidMethod::getInstance()->isHasShowSignInPay()){
			CallAndroidMethod::getInstance()->pay(8);
			GAMEDATA::getInstance()->setHasShowSignInPay(true);
		}else{
			canStartGame = true;
		}
	}
#endif

	auto moreGameBtn = MenuItemImage::create(
		"more_game_btn_normal.png", "more_game_btn_click.png", CC_CALLBACK_0(MenuLayer::showMoreGame, this)
		);
	moreGameMenu = Menu::create(moreGameBtn, NULL);
	moreGameMenu->setPosition(740, 65);
	moreGameMenu->setAnchorPoint(Point(0.5, 0.5));
	moreGameMenu->setVisible(false);
	this->addChild(moreGameMenu);

	Audio::getInstance()->playBGM("Music/lobby_bg.ogg");

	MenuItemImage* musicBtnOn = MenuItemImage::create("bg_music_open.png", "bg_music_open.png");
	MenuItemImage* musicBtnOff = MenuItemImage::create("bg_music_close.png", "bg_music_close.png");
	MenuItemToggle* musicTog = MenuItemToggle::createWithTarget(this, menu_selector(MenuLayer::getMusicState), musicBtnOn, musicBtnOff, NULL);
	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		musicTog->setSelectedIndex(0);
	}
	else
	{
		musicTog->setSelectedIndex(1);
	}
	auto musicMenu = Menu::create(musicTog, NULL);
	musicMenu->setPosition(60, 65);
	MenuItemImage* soundEffectOn = MenuItemImage::create("sound_effect_open.png", "sound_effect_open.png");
	MenuItemImage* soundEffectOff = MenuItemImage::create("sound_effect_close.png", "sound_effect_close.png");
	MenuItemToggle* soundEffectTog = MenuItemToggle::createWithTarget(this, menu_selector(MenuLayer::getSoudState), soundEffectOn, soundEffectOff, NULL);
	if (GAMEDATA::getInstance()->getSoundState())
	{
		soundEffectTog->setSelectedIndex(0);
	}
	else
	{
		soundEffectTog->setSelectedIndex(1);
	}
	auto soundEffectMenu = Menu::create(soundEffectTog, NULL);
	soundEffectMenu->setPosition(130, 65);
	this->addChild(musicMenu);
	this->addChild(soundEffectMenu);

	signInPrize = SignInPrize::create();
	this->addChild(signInPrize, 200);
	signInPrize->setVisible(false);

	//if (GAMEDATA::getInstance()->isFirstLogin() && Player::skillState <= 4){
		//GAMEDATA::getInstance()->setFirstLogin(false);
		//GameStateInfo::getInstance()->setGameState(Game_Pause);
		//CallAndroidMethod::getInstance()->pay(1);
	//}

	this->scheduleUpdate();
	return true;
}
void MenuLayer::startGame(){
	if (signIn->isVisible() || !canStartGame || signInPrize->isVisible()){
		return;
	}
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	chcekPropUse();
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	goToGameScene();
#endif
}

void MenuLayer::goToGameScene(){
	Audio::getInstance()->playSound("Music/game_start.mp3");
	Director::getInstance()->replaceScene(TransitionFade::create(1, TollgateScene::scene()));
}

void MenuLayer::chcekPropUse(){
	if (GAMEDATA::getInstance()->isSuperSelect()){
		int superPropNum = GAMEDATA::getInstance()->getSuperPropNum();
		if (superPropNum > 0){
			GAMEDATA::getInstance()->setUsePropType(PROP_SUPER);
			goToGameScene();
		}
		else{
			CallAndroidMethod::getInstance()->pay(15);
		}
	}
	else if (GAMEDATA::getInstance()->isMagneticSelect()){
		int magneticPropNum = GAMEDATA::getInstance()->getMagneticPropNum();
		if (magneticPropNum > 0){
			GAMEDATA::getInstance()->setUsePropType(PROP_MAGNETIC);
			goToGameScene();
		}
		else{
			CallAndroidMethod::getInstance()->pay(16);
		}
	}
	else if (GAMEDATA::getInstance()->isPotentialSelect()){
		int potentialPropNum = GAMEDATA::getInstance()->getPotentialPropNum();
		if (potentialPropNum > 0){
			GAMEDATA::getInstance()->setUsePropType(PROP_POTENTIAL);
			goToGameScene();
		}
		else{
			CallAndroidMethod::getInstance()->pay(17);
		}
	}
	else{
		goToGameScene();
	}
}

bool MenuLayer::upgradeSuper(Touch* touch, Event* event){
	if (signIn->isVisible() || !canStartGame || signInPrize->isVisible()){
		return false;
	}
	int level = GAMEDATA::getInstance()->getSuperLevel();
	if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())){
		//�����ֻ��һ��ѡ����ߵĲ���
		if (!GAMEDATA::getInstance()->isSuperSelect()){
			prop_select_icon->setVisible(true);
			prop_select_icon->setPosition(ccp(432, 320));
			GAMEDATA::getInstance()->setMagneticSelect(false);
			GAMEDATA::getInstance()->setSuperSelect(true);
			GAMEDATA::getInstance()->setPotentialSelect(false);
		}
		else{
			prop_select_icon->setVisible(false);
			GAMEDATA::getInstance()->setSuperSelect(false);
		}
		return true;
	}
	return false;
}

bool MenuLayer::upgradeMagnetic(Touch* touch, Event* event){
	if (signIn->isVisible() || !canStartGame || signInPrize->isVisible()){
		return false;
	}
	int level = GAMEDATA::getInstance()->getMagneticLevel();
	if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())){
		if (!GAMEDATA::getInstance()->isMagneticSelect()){
			prop_select_icon->setVisible(true);
			prop_select_icon->setPosition(ccp(432, 236));
			GAMEDATA::getInstance()->setMagneticSelect(true);
			GAMEDATA::getInstance()->setSuperSelect(false);
			GAMEDATA::getInstance()->setPotentialSelect(false);
		}
		else{
			prop_select_icon->setVisible(false);
			GAMEDATA::getInstance()->setMagneticSelect(false);
		}
		return true;
	}
	return false;
}

bool MenuLayer::upgradePotential(Touch* touch, Event* event){
	if (signIn->isVisible() || !canStartGame || signInPrize->isVisible()){
		return false;
	}
	int level = GAMEDATA::getInstance()->getPotentialLevel();

	if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())){

		if (!GAMEDATA::getInstance()->isPotentialSelect()){
			prop_select_icon->setVisible(true);
			prop_select_icon->setPosition(ccp(432, 150));
			GAMEDATA::getInstance()->setMagneticSelect(false);
			GAMEDATA::getInstance()->setSuperSelect(false);
			GAMEDATA::getInstance()->setPotentialSelect(true);
		}
		else{
			prop_select_icon->setVisible(false);
			GAMEDATA::getInstance()->setPotentialSelect(false);
		}
		return true;
	}
	return false;
}

void MenuLayer::showQuit(){
	if (signIn->isVisible() || !canStartGame || signInPrize->isVisible()){
		return;
	}
	Audio::getInstance()->playSound("Music/sign_in.ogg");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CallAndroidMethod::getInstance()->quit();
#endif
}

void MenuLayer::showMoreGame(){
	if (signIn->isVisible() || !canStartGame || signInPrize->isVisible()){
		return;
	}
	Audio::getInstance()->playSound("Music/paddle_hit.wav");
	if (moreGameMenu->isVisible()){
		CallAndroidMethod::getInstance()->showMoreGame();
	}
}


void MenuLayer::update(float dt){
	if (passPropCheck){
		goToGameScene();
		passPropCheck = false;
	}
	if (this->isVisible()){
		m_backgroundLayer->setBackGroudSpeed(1);
		m_backgroundLayer->logic(dt);
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (MenuLayer::needShowMoreGame){
		moreGameMenu->setVisible(true);
	}else{
		moreGameMenu->setVisible(false);
	}
#endif
	if (showSignInPrize){
		Audio::getInstance()->playSound("Music/sign_in_success.mp3");
		showSignInPrize = false;
		signInPrize->setVisible(true);
	}
	//�������Ƿ�����δ������ʾ����
	if (NULL != superIcon&&!isShowSuper&&GAMEDATA::getInstance()->getSuperLevel() <= 10){
		showLightAnim(superIcon);
		isShowSuper = true;
	}
	if (NULL != magneticIcon&&!isShowMagnetic&&GAMEDATA::getInstance()->getMagneticLevel() < +10){
		showLightAnim(magneticIcon);
		isShowMagnetic = true;
	}
	if (NULL != potentialIcon&&!isShowPotential&&GAMEDATA::getInstance()->getPotentialLevel() <= 10){
		showLightAnim(potentialIcon);
		isShowPotential = true;
	}
}


void MenuLayer::showLightAnim(Sprite* sprite){
	auto animation = Animation::create();
	for (int i = 1; i < 17; i++)
	{
		std::string szName = "prop_light_" + cocos2d::String::createWithFormat("%d", i)->_string + ".png";
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
	}
	animation->setDelayPerUnit(1 / 24.0f);
	animation->setRestoreOriginalFrame(false);
	auto action = Animate::create(animation);
	auto seq = Sequence::create(action, NULL);
	Sprite* posSprite = Sprite::create();
	posSprite->setPosition(sprite->getPosition());
	this->addChild(posSprite);
	posSprite->runAction(RepeatForever::create(seq));
}

void MenuLayer::getSoudState(CCObject* pSender){
	if (signIn->isVisible() || !canStartGame || signInPrize->isVisible()){
		return;
	}
	Audio::getInstance()->playSound("Music/paddle_hit.wav");

	CCMenuItemToggle* temp = (CCMenuItemToggle*)pSender;

	if (temp->getSelectedIndex() == 1)
	{

		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		GAMEDATA::getInstance()->setSoundState(false);
	}
	if (temp->getSelectedIndex() == 0)
	{

		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		GAMEDATA::getInstance()->setSoundState(true);
	}
}

void MenuLayer::getMusicState(CCObject* pSender){
	if (signIn->isVisible() || !canStartGame || signInPrize->isVisible()){
		return;
	}
	Audio::getInstance()->playSound("Music/paddle_hit.wav");

	CCMenuItemToggle* temp = (CCMenuItemToggle*)pSender;

	if (temp->getSelectedIndex() == 1)
	{

		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		GAMEDATA::getInstance()->setMusicState(false);
	}
	if (temp->getSelectedIndex() == 0)
	{

		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		GAMEDATA::getInstance()->setMusicState(true);
	}
}
