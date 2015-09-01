#include "GameOverLayer.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "GameData.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "PlayerRank.h"
#include "SimpleAudioEngine.h"
#include "Audio.h"
#include "Upgrade.h"
#include "Chinese.h"
#include "Gold.h"

using namespace cocos2d;

bool GameOverLayer::init(){
	if(!Layer::init()){
		return false;
	}
	curScore = GAMEDATA::getInstance()->getCurScore();
	float addScorePer = GAMEDATA::getInstance()->getScoreAddPer(GAMEDATA::getInstance()->getUserLevel());
	scoreNum = 0;
	animTime = 0;
	canClick = false;
	hasShowUpgrade = false;
	hasShowBeat = false;
	hasShowHappy = false;
	hasShowPrizeGold = false;
	hasPlaySound = false;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* background = Sprite::create("bg_mainscene.jpg");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	Sprite* title = Sprite::create("title.png");
	title->setPosition(135,680);
	title->setScale(0.5);
	this->addChild(title);

	addScoreNum = (int)(curScore*addScorePer);
	addScoreTxt = Sprite::create("game_result_add_score.png");
	addScore = LabelAtlas::create(String::createWithFormat("%d",addScoreNum)->_string,"add_score_per_num.png",25,44,48);
	addScore->setAnchorPoint(Point(0.5,0.5));
	if(addScoreNum < 10){
		addScoreTxt->setPosition(227.5+480,542);
		addScore->setPosition(311+480,546);
	}else if(addScoreNum < 100){
		addScoreTxt->setPosition(227.5-12.5+480,542);
		addScore->setPosition(311+480,546);
	}else if(addScoreNum < 1000){
		addScoreTxt->setPosition(227.5-12.5*2+480,542);
		addScore->setPosition(311+480,546);
	}else if(addScoreNum < 10000){
		addScoreTxt->setPosition(227.5-12.5*3+480,542);
		addScore->setPosition(311+480,546);
	}else if(addScoreNum < 100000){
		addScoreTxt->setPosition(227.5-12.5*4+480,542);
		addScore->setPosition(311+480,546);
	}
	this->addChild(addScoreTxt);
	this->addChild(addScore);

	curScore = curScore + addScoreNum;
	labelScore = LabelAtlas::create("0","game_result_score_num.png",39.0f,69.0f,'0');
	labelScore->setPosition(240+480,493);
	labelScore->setAnchorPoint(Point(0.5,0.5));
	this->addChild(labelScore);

	goldIcon = Sprite::create("gold_pack.png");
	goldIcon->setPosition(229+480,400);
	this->addChild(goldIcon);

	prizeGold = LabelAtlas::create(String::createWithFormat("%d",GAMEDATA::getInstance()->getPrizeGoldNum())->_string,
			"game_result_gold_num.png",15,27,48);
	prizeGold->setPosition(272.5+480,400);
	prizeGold->setAnchorPoint(Point(0.5,0.5));
	this->addChild(prizeGold);

	happy1 = Sprite::create("game_result_happy_1.png");
	happy2 = Sprite::create("game_result_happy_2.png");
	happyPoint = Sprite::create("game_result_happy_point.png");
	happyNum1 = LabelAtlas::create(String::createWithFormat("%d",curScore/1000)->_string,"add_score_per_num.png",25,44,48);
	happyNum1->setAnchorPoint(Point(0.5,0.5));
	happyNum2 = LabelAtlas::create(String::createWithFormat("%d",(curScore%1000)/100)->_string,"add_score_per_num.png",25,44,48);
	happyNum2->setAnchorPoint(Point(0.5,0.5));
	if(curScore/1000 < 10){
		happy1->setPosition(177.5+480,309);
		happy2->setPosition(380+480,309);
		happyPoint->setPosition(317.5+480,300);
		happyNum1->setPosition(301+480,309);
		happyNum2->setPosition(334+480,309);
	}else{
		happy1->setPosition(165+480,309);
		happy2->setPosition(392.5+480,309);
		happyPoint->setPosition(330+480,300);
		happyNum1->setPosition(301+480,309);
		happyNum2->setPosition(346.5+480,309);
	}
	this->addChild(happy1);
	this->addChild(happy2);
	this->addChild(happyPoint);
	this->addChild(happyNum1);
	this->addChild(happyNum2);

	beatDesc1 = Sprite::create("game_result_beat_txt_1.png");
	beatDesc1->setPosition(174.5+480,256);
	this->addChild(beatDesc1);

	beatDesc2 = Sprite::create("game_result_beat_txt_2.png");
	beatDesc2->setPosition(313+480,256);
	this->addChild(beatDesc2);

	beatPerTxt = Sprite::create("game_result_per.png");
	beatPerTxt->setPosition(262.5+480,256);
	this->addChild(beatPerTxt);

	beatNum = LabelAtlas::create(String::createWithFormat("%d",PLAYERRANK::getInstance()->getRankPer(curScore))->_string,"game_result_gold_num.png",15,27,48);
	beatNum->setPosition(234.5+480,256);
	beatNum->setAnchorPoint(Point(0.5,0.5));
	this->addChild(beatNum);

	MenuItemImage* backBtn = MenuItemImage::create(
		"exit_normal.png","exit_click.png",CC_CALLBACK_0(GameOverLayer::back,this)
		);
	backMenu = Menu::create(backBtn,NULL);
	backMenu->setPosition(408,150);
	backMenu->setOpacity(0);
	this->addChild(backMenu,2);

	startBtn = MenuItemImage::create(
		"retry_normal.png","retry_click.png",CC_CALLBACK_0(GameOverLayer::continueGame,this)
		);
	startBtn->setScale(1.2);
	startMenu = Menu::create(startBtn,NULL);
	startMenu->setPosition(72,150);
	startMenu->setOpacity(0);
	this->addChild(startMenu,2);

	musicBtnOn = MenuItemImage::create("bg_music_open.png","bg_music_open.png");
	musicBtnOff = MenuItemImage::create("bg_music_close.png","bg_music_close.png");
	auto musicTog = MenuItemToggle::createWithTarget(this,menu_selector(GameOverLayer::getMusicState),musicBtnOn,musicBtnOff,NULL);
	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		musicTog->setSelectedIndex(0);
	}
	else
	{
		musicTog->setSelectedIndex(1);
	}
	auto musicMenu = Menu::create(musicTog,NULL);
	musicBtnOn->setOpacity(0);
	musicBtnOff->setOpacity(0);
	musicMenu->setPosition(184,150);
	soundEffectOn = MenuItemImage::create("sound_effect_on.png","sound_effect_on.png");
	soundEffectOff = MenuItemImage::create("sound_effect_close.png","sound_effect_close.png");
	auto soundEffectTog = MenuItemToggle::createWithTarget(this,menu_selector(GameOverLayer::getSoudState),soundEffectOn,soundEffectOff,NULL);
	if (GAMEDATA::getInstance()->getSoundEffect())
	{
		soundEffectTog->setSelectedIndex(0);
	}
	else
	{
		soundEffectTog->setSelectedIndex(1);
	}
	auto soundEffectMenu = Menu::create(soundEffectTog,NULL);
	soundEffectMenu->setPosition(296,150);
	soundEffectOn->setOpacity(0);
	soundEffectOff->setOpacity(0);
	this->addChild(musicMenu,2);
	this->addChild(soundEffectMenu,2);
	this->scheduleUpdate();

	upgrade = 0;
	upgrade = Upgrade::getInstance();
	upgrade->setVisible(false);
	this->addChild(upgrade,3);
	return true;
}

void GameOverLayer::update(float delta){
	if(this->isVisible()){
		animTime += delta/0.05;
		if(animTime >= 60000000){
			animTime = 6000;
		}
		if(animTime > 5){
			if(!hasShowScore){
				hasShowScore = true;
				labelScore->runAction(MoveTo::create(0.3f,Point(240,493)));
				if(addScoreNum < 10){
					addScoreTxt->runAction(MoveTo::create(0.3f,Point(227.5,542)));
					addScore->runAction(MoveTo::create(0.3f,Point(311,546)));
				}else if(addScoreNum < 100){
					addScoreTxt->runAction(MoveTo::create(0.3f,Point(227.5-12.5,542)));
					addScore->runAction(MoveTo::create(0.3f,Point(311,546)));
				}else if(addScoreNum < 1000){
					addScoreTxt->runAction(MoveTo::create(0.3f,Point(227.5-12.5*2,542)));
					addScore->runAction(MoveTo::create(0.3f,Point(311,546)));
				}else if(addScoreNum < 10000){
					addScoreTxt->runAction(MoveTo::create(0.3f,Point(227.5-12.5*3,542)));
					addScore->runAction(MoveTo::create(0.3f,Point(311,546)));
				}else if(addScoreNum < 100000){
					addScoreTxt->runAction(MoveTo::create(0.3f,Point(227.5-12.5*4,542)));
					addScore->runAction(MoveTo::create(0.3f,Point(311,546)));
				}
			}
		}
		if(animTime >= 11){
			scoreNum = (animTime-11)/30 * curScore;
		}
		if(scoreNum > curScore){
			scoreNum = curScore;
		}
		labelScore->setString(cocos2d::String::createWithFormat("%d",(int)scoreNum)->_string);

		rotation = 360*animTime/60;
		startBtn->setRotation(rotation);

		if(animTime >= 41 && !hasShowBeat){
			hasShowBeat = true;
			beatDesc1->runAction(MoveTo::create(0.4f,Point(174.5,256)));
			beatDesc2->runAction(MoveTo::create(0.4f,Point(313,256)));
			beatNum->runAction(MoveTo::create(0.4f,Point(234.5,256)));
			beatPerTxt->runAction(MoveTo::create(0.4f,Point(262.5,256)));
		}

		if(animTime >= 53 && !hasShowPrizeGold){
			hasShowPrizeGold = true;
			goldIcon->runAction(MoveTo::create(0.4f,Point(229,400)));
			prizeGold->runAction(MoveTo::create(0.4f,Point(272.5,400)));
		}

		if(animTime >= 47 && !hasShowHappy){
			hasShowHappy = true;
			if(curScore/1000 < 10){
				happy1->runAction(MoveTo::create(0.4f,Point(177.5,309)));
				happy2->runAction(MoveTo::create(0.4f,Point(380,309)));
				happyPoint->runAction(MoveTo::create(0.4f,Point(317.5,300)));
				happyNum1->runAction(MoveTo::create(0.4f,Point(301,309)));
				happyNum2->runAction(MoveTo::create(0.4f,Point(334,309)));
			}else{
				happy1->runAction(MoveTo::create(0.4f,Point(165,309)));
				happy2->runAction(MoveTo::create(0.4f,Point(392.5,309)));
				happyPoint->runAction(MoveTo::create(0.4f,Point(330,300)));
				happyNum1->runAction(MoveTo::create(0.4f,Point(301,309)));
				happyNum2->runAction(MoveTo::create(0.4f,Point(346.5,309)));
			}
		}

		if(animTime >= 59 && !hasShowBtn){
			hasShowBtn = true;
			startMenu->runAction(FadeTo::create(2.2f,255));
			backMenu->runAction(FadeTo::create(2.2f,255));
			musicBtnOn->runAction(FadeTo::create(2.2f,255));
			musicBtnOff->runAction(FadeTo::create(2.2f,255));
			soundEffectOn->runAction(FadeTo::create(2.2f,255));
			soundEffectOff->runAction(FadeTo::create(2.2f,255));
		}

		if(animTime > 82){
			if(hasShowUpgrade){

			}else{
				hasShowUpgrade = true;
				int curExpNum = GAMEDATA::getInstance()->getCurExpNum();
				int level = GAMEDATA::getInstance()->getUserLevel();
				int upgradePrizeGoldNum = 0;
				if(curExpNum+1 == GAMEDATA::getInstance()->getFullExpNum(level)){
					upgradePrizeGoldNum = GAMEDATA::getInstance()->getUpgradePrizeNum(level);
					GAMEDATA::getInstance()->setUserLevel(level+1);
					GAMEDATA::getInstance()->saveUserLevel();
					GAMEDATA::getInstance()->setCurExpNum(0);

					Audio::getInstance()->playUpgrade();
					upgrade->setVisible(true);
				}else{
					GAMEDATA::getInstance()->setCurExpNum(curExpNum+1);
				}
				GAMEDATA::getInstance()->saveCurExpNum();
				GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+GAMEDATA::getInstance()->getPrizeGoldNum()+upgradePrizeGoldNum);
				GAMEDATA::getInstance()->saveGoldNum();

				GAMEDATA::getInstance()->setTotalScore(GAMEDATA::getInstance()->getTotalScore()+curScore);
				GAMEDATA::getInstance()->saveTotalScore();
			}
			canClick = true;
		}
	}
}

void GameOverLayer::continueGame(){
	if(upgrade->isVisible()){
		return;
	}
	if(canClick){
		Audio::getInstance()->playClick();
		GAMEDATA::getInstance()->init();
		Director::getInstance()->replaceScene(TransitionSlideInL::create(1,GameScene::create()));
	}
}

void GameOverLayer::back(){
	if(upgrade->isVisible()){
		return;
	}
	if(canClick){
		Audio::getInstance()->playClick();
		Gold::getInstance()->refreshGold();
		Director::getInstance()->replaceScene(TransitionFade::create(1,HelloWorld::createScene()));
	}
}

void GameOverLayer::getSoudState(CCObject* pSender){
	Audio::getInstance()->playClick();
	    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;
	    if (temp->getSelectedIndex()==1)
	    {
	        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
			GAMEDATA::getInstance()->setSoundEffect(false);
		    GAMEDATA::getInstance()->saveSoundEffect();
	    }
	    if (temp->getSelectedIndex()==0)
	    {
	        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
			GAMEDATA::getInstance()->setSoundEffect(true);
		    GAMEDATA::getInstance()->saveSoundEffect();
	    }
}

void GameOverLayer::getMusicState(CCObject* pSender){
	Audio::getInstance()->playClick();
	CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;
	if (temp->getSelectedIndex()==1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		GAMEDATA::getInstance()->setMusicState(false);
		GAMEDATA::getInstance()->saveMusicState();
	}
	if (temp->getSelectedIndex()==0)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		GAMEDATA::getInstance()->setMusicState(true);
		GAMEDATA::getInstance()->saveMusicState();
	}
}
