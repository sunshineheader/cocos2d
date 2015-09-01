#include "GamePauseLayer.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"
#include "Audio.h"
#include "GameData.h"
#include "GameState.h"
#include "StartScene.h"


using namespace cocos2d;

GamePauseLayer* GamePauseLayer::create(){
	GamePauseLayer* ret = new GamePauseLayer();
	if(ret && ret->init()){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool GamePauseLayer::init(){
	if(!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* background = Sprite::create("game_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,0);
	
	MenuItemImage* musicBtnOn = MenuItemImage::create("bg_music_open.png","bg_music_open.png");
	MenuItemImage* musicBtnOff = MenuItemImage::create("bg_music_close.png","bg_music_close.png");
	MenuItemToggle* musicTog = MenuItemToggle::createWithTarget(this,menu_selector(GamePauseLayer::getMusicState),musicBtnOn,musicBtnOff,NULL);  
	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())  
	{  
	musicTog->setSelectedIndex(0);  
	}   
	else  
	{  
	musicTog->setSelectedIndex(1);  
	}  

	Menu* musicMenu = Menu::create(musicTog,NULL);
	musicMenu->setPosition(745,450);
	this->addChild(musicMenu);

	Sprite* help_boy = Sprite::create("help_boy.png");
	help_boy->setPosition(visibleSize.width/2+170,visibleSize.height/2+150);
	this->addChild(help_boy);

	Sprite* helpSprite = Sprite::create("help_text.png");
	helpSprite->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(helpSprite);

	MenuItemImage* exitBtn = MenuItemImage::create("exit.png","exit.png",CC_CALLBACK_0(GamePauseLayer::goBack,this));
	MenuItemImage* resumeBtn = MenuItemImage::create("continue.png","continue.png",CC_CALLBACK_0(GamePauseLayer::ResumeGame,this));
	auto scale1 = ScaleTo::create(2,1.1);
	auto scale2 = ScaleTo::create(2,1);
	auto seq =Sequence::create(scale1,scale2,nullptr);
	resumeBtn->runAction(RepeatForever::create(seq));

	Menu* resumeMenu = Menu::create(exitBtn,resumeBtn, NULL);
	resumeMenu ->alignItemsHorizontallyWithPadding(100);
	resumeMenu->setPosition(visibleSize.width/2,visibleSize.height/2-170);
	this->addChild(resumeMenu,2);
	return true;
}

void GamePauseLayer::payProps(){

}

void GamePauseLayer::goBack(){
	GAMEDATA::getInstance()->cleanDatas();
	GAMESTATE::getInstance()->reset();
	this->removeFromParentAndCleanup(true);
	Director::getInstance()->replaceScene(TransitionFade::create(1,StartScene::createScene()));	
}

void GamePauseLayer::ResumeGame(){
	this->removeFromParentAndCleanup(true);
	GAMESTATE::getInstance()->setGamePause(false);
}


void GamePauseLayer::getMusicState(CCObject* pSender){
	CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;  
	if (temp->getSelectedIndex()==1)  
	{   
		Audio::getInstance()->playSound(CLICK);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic(); 
		GAMEDATA::getInstance()->setMusicState(false);

	}  
	if (temp->getSelectedIndex()==0)  
	{  
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic(); 
		GAMEDATA::getInstance()->setMusicState(true);
	} 
}
