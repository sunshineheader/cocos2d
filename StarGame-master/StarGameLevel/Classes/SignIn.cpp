#include "SignIn.h"
#include "Chinese.h"
#include "CallAndroidMethod.h"
#include "GameData.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Chinese.h"
#include "Audio.h"
#include "Gold.h"

SignIn* SignIn::_instance = nullptr;
SignIn::SignIn(){
	this->init();
}

SignIn* SignIn::getInstance(){
	if(_instance == 0){
		_instance = new SignIn();
	}
	return _instance;
}

bool SignIn::init(){
	if(!Node::init()){
		return false;
	}

	auto bg = Sprite::create("bg_mainscene.jpg");
	bg->setPosition(240,400);
	this->addChild(bg);

	int level = GAMEDATA::getInstance()->getUserLevel();

	int per = (int)((float)GAMEDATA::getInstance()->getCurExpNum()/GAMEDATA::getInstance()->getFullExpNum(level)*100);

	auto levelTxt = Sprite::create("level.png");
	levelTxt->setAnchorPoint(Point(0,0.5));
	levelTxt->setPosition(30,40);
	this->addChild(levelTxt);

	auto levelNum = LabelAtlas::create(String::createWithFormat("%d",level)->_string,"level_num.png",15,22,48);
	levelNum->setAnchorPoint(Point(0,0.5));
	levelNum->setPosition(64,40);
	this->addChild(levelNum);

	auto line = Sprite::create("line.png");
	line->setAnchorPoint(Point(0,0.5));
	auto perNum = LabelAtlas::create(String::createWithFormat("%d",per)->_string,"level_num.png",15,22,48);
	perNum->setAnchorPoint(Point(0,0.5));
	auto perTxt = Sprite::create("per.png");
	perTxt->setAnchorPoint(Point(0,0.5));
	this->addChild(line);
	this->addChild(perNum);
	this->addChild(perTxt);
	if(level < 10){
		line->setPosition(81,40);
		perNum->setPosition(90,40);
		if(per < 10){
			perTxt->setPosition(105,40);
		}else{
			perTxt->setPosition(120,40);
		}
	}else if(level < 100){
		line->setPosition(96,40);
		perNum->setPosition(105,40);
		if(per < 10){
			perTxt->setPosition(120,40);
		}else{
			perTxt->setPosition(135,40);
		}
	}else{
		line->setPosition(111,40);
		perNum->setPosition(120,40);
		if(per < 10){
			perTxt->setPosition(135,40);
		}else{
			perTxt->setPosition(150,40);
		}
	}

	auto goldBuyBtn = MenuItemImage::create(
		"gold_buy_normal.png","gold_buy_click.png",CC_CALLBACK_0(SignIn::pay,this)
		);
	auto goldBuyMenu = Menu::create(goldBuyBtn, NULL);
	goldBuyMenu->setPosition(447,760);
	goldBuyMenu->setAnchorPoint(Point(1,0));
	this->addChild(goldBuyMenu);

	gold = Gold::getInstance();
	this->addChild(gold);

	MenuItemImage* musicBtnOn = MenuItemImage::create("bg_music_open.png","bg_music_open.png");
	MenuItemImage* musicBtnOff = MenuItemImage::create("bg_music_close.png","bg_music_close.png");
	MenuItemToggle* musicTog = MenuItemToggle::createWithTarget(this,menu_selector(SignIn::getMusicState),musicBtnOn,musicBtnOff,NULL);
	 if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			musicTog->setSelectedIndex(0);
		}
		else
		{
			musicTog->setSelectedIndex(1);
		}
	auto musicMenu = Menu::create(musicTog,NULL);
	musicMenu->setPosition(53,760);
	MenuItemImage* soundEffectOn = MenuItemImage::create("sound_effect_on.png","sound_effect_on.png");
	MenuItemImage* soundEffectOff = MenuItemImage::create("sound_effect_close.png","sound_effect_close.png");
	MenuItemToggle* soundEffectTog = MenuItemToggle::createWithTarget(this,menu_selector(SignIn::getSoudState),soundEffectOn,soundEffectOff,NULL);
	 if (GAMEDATA::getInstance()->getSoundEffect())
		{
			soundEffectTog->setSelectedIndex(0);
		}
		else
		{
			soundEffectTog->setSelectedIndex(1);
		}
	auto soundEffectMenu = Menu::create(soundEffectTog,NULL);
	soundEffectMenu->setPosition(124,760);
	this->addChild(musicMenu);
	this->addChild(soundEffectMenu);

	auto signInbg = Sprite::create("sign_in_bg.png");
	signInbg->setPosition(240,400);
	this->addChild(signInbg);

	auto title = Sprite::create("sign_in_title.png");
	title->setPosition(240,542);
	this->addChild(title);

	auto itemBg1 = Sprite::create("sign_in_item_bg_1.png");
	itemBg1->setPosition(70,442);
	this->addChild(itemBg1);

	auto day1 = LabelAtlas::create("1","game_result_gold_num.png",15,27,48);
	day1->setPosition(60.5,480.5);
	day1->setAnchorPoint(Point(0.5,0.5));
	this->addChild(day1);

	auto dayTxt1 = Sprite::create("sign_in_day.png");
	dayTxt1->setPosition(77.5,480.5);
	this->addChild(dayTxt1);

	auto goldPack1 = Sprite::create("sign_in_gold_pack.png");
	goldPack1->setPosition(70,442);
	this->addChild(goldPack1);

	auto itemGoldNum1 = LabelAtlas::create("15","game_result_gold_num.png",15,27,48);
	itemGoldNum1->setPosition(70,403.5);
	itemGoldNum1->setAnchorPoint(Point(0.5,0.5));
	this->addChild(itemGoldNum1);

	auto itemBg2 = Sprite::create("sign_in_item_bg_1.png");
	itemBg2->setPosition(155,442);
	this->addChild(itemBg2);

	auto day2 = LabelAtlas::create("2","game_result_gold_num.png",15,27,48);
	day2->setPosition(155-9.5,480.5);
	day2->setAnchorPoint(Point(0.5,0.5));
	this->addChild(day2);

	auto dayTxt2 = Sprite::create("sign_in_day.png");
	dayTxt2->setPosition(155+7.5,480.5);
	this->addChild(dayTxt2);

	auto goldPack2 = Sprite::create("sign_in_gold_pack.png");
	goldPack2->setPosition(155,442);
	this->addChild(goldPack2);

	auto itemGoldNum2 = LabelAtlas::create("20","game_result_gold_num.png",15,27,48);
	itemGoldNum2->setPosition(155,403.5);
	itemGoldNum2->setAnchorPoint(Point(0.5,0.5));
	this->addChild(itemGoldNum2);

	auto itemBg3 = Sprite::create("sign_in_item_bg_1.png");
	itemBg3->setPosition(240,442);
	this->addChild(itemBg3);

	auto day3 = LabelAtlas::create("3","game_result_gold_num.png",15,27,48);
	day3->setPosition(240-9.5,480.5);
	day3->setAnchorPoint(Point(0.5,0.5));
	this->addChild(day3);

	auto dayTxt3 = Sprite::create("sign_in_day.png");
	dayTxt3->setPosition(240+7.5,480.5);
	this->addChild(dayTxt3);

	auto goldPack3 = Sprite::create("sign_in_gold_pack.png");
	goldPack3->setPosition(240,442);
	this->addChild(goldPack3);

	auto itemGoldNum3 = LabelAtlas::create("25","game_result_gold_num.png",15,27,48);
	itemGoldNum3->setPosition(240,403.5);
	itemGoldNum3->setAnchorPoint(Point(0.5,0.5));
	this->addChild(itemGoldNum3);

	auto itemBg4 = Sprite::create("sign_in_item_bg_1.png");
	itemBg4->setPosition(325,442);
	this->addChild(itemBg4);

	auto day4 = LabelAtlas::create("4","game_result_gold_num.png",15,27,48);
	day4->setPosition(325-9.5,480.5);
	day4->setAnchorPoint(Point(0.5,0.5));
	this->addChild(day4);

	auto dayTxt4 = Sprite::create("sign_in_day.png");
	dayTxt4->setPosition(325+7.5,480.5);
	this->addChild(dayTxt4);

	auto goldPack4 = Sprite::create("sign_in_gold_pack.png");
	goldPack4->setPosition(325,442);
	this->addChild(goldPack4);

	auto itemGoldNum4 = LabelAtlas::create("30","game_result_gold_num.png",15,27,48);
	itemGoldNum4->setPosition(325,403.5);
	itemGoldNum4->setAnchorPoint(Point(0.5,0.5));
	this->addChild(itemGoldNum4);

	auto itemBg5 = Sprite::create("sign_in_item_bg_1.png");
	itemBg5->setPosition(410,442);
	this->addChild(itemBg5);

	auto day5 = LabelAtlas::create("5","game_result_gold_num.png",15,27,48);
	day5->setPosition(410-9.5,480.5);
	day5->setAnchorPoint(Point(0.5,0.5));
	this->addChild(day5);

	auto dayTxt5 = Sprite::create("sign_in_day.png");
	dayTxt5->setPosition(410+7.5,480.5);
	this->addChild(dayTxt5);

	auto goldPack5 = Sprite::create("sign_in_gold_pack.png");
	goldPack5->setPosition(410,442);
	this->addChild(goldPack5);

	auto itemGoldNum5 = LabelAtlas::create("35","game_result_gold_num.png",15,27,48);
	itemGoldNum5->setPosition(410,403.5);
	itemGoldNum5->setAnchorPoint(Point(0.5,0.5));
	this->addChild(itemGoldNum5);

	auto signedBg = Sprite::create("sign_in_item_bg_2.png");
	auto hasSignMark = Sprite::create("sign_in_has_sign.png");
	this->addChild(signedBg);
	this->addChild(hasSignMark);

	auto desc1 = Sprite::create("sign_in_desc_1.png");
	desc1->setPosition(205.5,346);
	this->addChild(desc1);

	auto desc2 = Sprite::create("sign_in_gold_pack.png");
	desc2->setPosition(286.5,346);
	this->addChild(desc2);

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		signDay = CallAndroidMethod::getInstance()->getCurrentSignDayas();
		if(signDay == 0){
			prizeGoldNum = 15;
			signedBg->setPosition(70,442);
			hasSignMark->setPosition(102,496);
		}else if(signDay == 1){
			prizeGoldNum = 20;
			signedBg->setPosition(155,442);
			hasSignMark->setPosition(187,496);
		}else if(signDay == 2){
			prizeGoldNum = 25;
			signedBg->setPosition(240,442);
			hasSignMark->setPosition(272,496);
		}else if(signDay == 3){
			prizeGoldNum = 30;
			signedBg->setPosition(325,442);
			hasSignMark->setPosition(357,496);
		}else if(signDay >= 4){
			prizeGoldNum = 35;
			signedBg->setPosition(410,442);
			hasSignMark->setPosition(442,496);
		}
    #endif

	auto prizeGold = LabelAtlas::create(String::createWithFormat("%d",prizeGoldNum)->_string,"game_result_gold_num.png",15,27,48);
	prizeGold->setAnchorPoint(Point(0.5,0.5));
	prizeGold->setPosition(321,346);
	this->addChild(prizeGold);

	MenuItemImage* confirmBtn = MenuItemImage::create(
			"sign_in_confirm_up.png","sign_in_confirm_down.png",CC_CALLBACK_0(SignIn::hideSelf,this)
			);
	auto confirmMenu = Menu::create(confirmBtn, NULL);
	confirmMenu->setPosition(240,276);
	this->addChild(confirmMenu);

	auto aboutBtn = MenuItemImage::create(
		"about_btn_normal.png","about_btn_click.png",CC_CALLBACK_0(SignIn::showAbout,this)
		);
	auto aboutMenu = Menu::create(aboutBtn, NULL);
	aboutMenu->setPosition(427,50);
	this->addChild(aboutMenu);

	aboutBg = Sprite::create("bg_mainscene.jpg");
	aboutBg->setPosition(240,400);
	this->addChild(aboutBg);

	smallTitle11 = Label::create(ChineseWord("abouttitle11"),"Arial",36);
	smallTitle11->setPosition(60,718);
	smallTitle11->setAnchorPoint(Point(0,0.5));
	this->addChild(smallTitle11);

	int totalScore = GAMEDATA::getInstance()->getTotalScore();

	smallTitle12 = Label::create(String::createWithFormat("%d",
			totalScore)->_string+ChineseWord("abouttitle12"),"Arial",36);
	smallTitle12->setPosition(60,668);
	smallTitle12->setAnchorPoint(Point(0,0.5));
	this->addChild(smallTitle12);

	smallTitle21 = Label::create(ChineseWord("abouttitle21"),"Arial",36);
	smallTitle21->setPosition(60,618);
	smallTitle21->setAnchorPoint(Point(0,0.5));
	this->addChild(smallTitle21);

	smallTitle22 = Label::create(String::createWithFormat("%d",
			totalScore/1000)->_string+"."+String::createWithFormat("%d",
					(totalScore%1000)/100)->_string+ChineseWord("abouttitle22"),"Arial",36);
	smallTitle22->setPosition(60,568);
	smallTitle22->setAnchorPoint(Point(0,0.5));
	this->addChild(smallTitle22);

	titleDesc1 = Label::create(ChineseWord("aboutdesc1"),"Arial",24);
	titleDesc1->setPosition(60,478);
	titleDesc1->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc1);

	titleDesc2 = Label::create(ChineseWord("aboutdesc2"),"Arial",24);
	titleDesc2->setPosition(60,438);
	titleDesc2->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc2);

	titleDesc3 = Label::create(ChineseWord("aboutdesc3"),"Arial",24);
	titleDesc3->setPosition(60,398);
	titleDesc3->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc3);

	titleDesc4 = Label::create(ChineseWord("aboutdesc4"),"Arial",24);
	titleDesc4->setPosition(60,358);
	titleDesc4->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc4);

	titleDesc5 = Label::create(ChineseWord("aboutdesc5"),"Arial",24);
	titleDesc5->setPosition(60,318);
	titleDesc5->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc5);

	titleDesc6 = Label::create(ChineseWord("aboutdesc6"),"Arial",24);
	titleDesc6->setPosition(60,278);
	titleDesc6->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc6);

	titleDesc7 = Label::create(ChineseWord("aboutdesc7"),"Arial",24);
	titleDesc7->setPosition(60,238);
	titleDesc7->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc7);

	titleDesc8 = Label::create(ChineseWord("aboutdesc8"),"Arial",24);
	titleDesc8->setPosition(60,198);
	titleDesc8->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc8);

	titleDesc9 = Label::create(ChineseWord("aboutdesc9"),"Arial",24);
	titleDesc9->setPosition(60,158);
	titleDesc9->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc9);

	auto backBtn = MenuItemImage::create(
		"about_back_normal.png","about_back_click.png",CC_CALLBACK_0(SignIn::hideAbout,this)
		);
	backMenu = Menu::create(backBtn, NULL);
	backMenu->setPosition(100,70);
	backMenu->setAnchorPoint(Point(0.5,0.5));
	this->addChild(backMenu);

	auto startBtn = MenuItemImage::create(
		"about_start_normal.png","about_start_click.png",CC_CALLBACK_0(SignIn::startGameT,this)
		);
	startMenu = Menu::create(startBtn, NULL);
	startMenu->setPosition(320,70);
	startMenu->setAnchorPoint(Point(0.5,0.5));
	this->addChild(startMenu);
	setAboutVisible(false);

	return true;
}

void SignIn::showAbout(){
	setAboutVisible(true);
}

void SignIn::hideAbout(){
	setAboutVisible(false);
}

void SignIn::startGameT(){
	hideSelf();
}

void SignIn::setAboutVisible(bool visible){
	aboutBg->setVisible(visible);
	smallTitle11->setVisible(visible);
	smallTitle12->setVisible(visible);
	smallTitle21->setVisible(visible);
	smallTitle22->setVisible(visible);
	titleDesc1->setVisible(visible);
	titleDesc2->setVisible(visible);
	titleDesc3->setVisible(visible);
	titleDesc4->setVisible(visible);
	titleDesc5->setVisible(visible);
	titleDesc6->setVisible(visible);
	titleDesc7->setVisible(visible);
	titleDesc8->setVisible(visible);
	titleDesc9->setVisible(visible);
	backMenu->setVisible(visible);
	startMenu->setVisible(visible);
}

void SignIn::hideSelf(){
	Audio::getInstance()->playClick();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->sign();
		GAMEDATA::getInstance()->setPrizeGoldNum(15+signDay*5);
    #endif

	if(GAMEDATA::getInstance()->isFirstLogin() && GAMEDATA::getInstance()->getUserLevel() <=1){
		GAMEDATA::getInstance()->setFirstLogin(false);
		GAMEDATA::getInstance()->init();
		Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
	}else{
		this->setVisible(false);
		this->removeFromParentAndCleanup(true);
	}
}

void SignIn::pay(){
	Audio::getInstance()->playClick();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CallAndroidMethod::getInstance()->pay(10);
    #endif
}

void SignIn::getSoudState(CCObject* pSender){
	Audio::getInstance()->playClick();
	 //������ʱCCMenuItemToggle
    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;
    //����CCMenuItemToggle��ѡ�����������ֵĿ���
    if (temp->getSelectedIndex()==1)
    {
        //��ͣ��������
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		GAMEDATA::getInstance()->setSoundEffect(false);
	    GAMEDATA::getInstance()->saveSoundEffect();
    }
    if (temp->getSelectedIndex()==0)
    {
        //������������
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		GAMEDATA::getInstance()->setSoundEffect(true);
	    GAMEDATA::getInstance()->saveSoundEffect();
    }
}

void SignIn::getMusicState(CCObject* pSender){
	Audio::getInstance()->playClick();
	 //������ʱCCMenuItemToggle
    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;
    //����CCMenuItemToggle��ѡ�����������ֵĿ���
    if (temp->getSelectedIndex()==1)
    {
        //��ͣ��������
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        GAMEDATA::getInstance()->setMusicState(false);
        GAMEDATA::getInstance()->saveMusicState();
    }
    if (temp->getSelectedIndex()==0)
    {
        //������������
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        GAMEDATA::getInstance()->setMusicState(true);
        GAMEDATA::getInstance()->saveMusicState();
    }
}

