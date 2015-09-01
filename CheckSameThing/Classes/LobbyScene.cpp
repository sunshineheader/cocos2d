#include "LobbyScene.h"
#include "GameScene.h"
#include"Audio.h"
#include"GameData.h"
#include "SimpleAudioEngine.h"
#include"SignInLayer.h"


Scene* LobbyScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LobbyScene::create();
	scene->addChild(layer);

	return scene;
}

bool LobbyScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//add game bg to layer
	Sprite* lobby_bg = Sprite::create("lobby_bg.jpg");
	lobby_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(lobby_bg, -1);

	//add start menu to layer
	//CCLOG("time %f", GAMEDATA::getInstance()->getCurrentTime());

	GAMEDATA::getInstance()->setDay(GAMEDATA::getInstance()->getCurrentTime());
	GAMEDATA::getInstance()->savaDay();
	int a =  GAMEDATA::getInstance()->getDay();
	int n =  GAMEDATA::getInstance()->getCurrentTime();
	int m= GAMEDATA::getInstance()->getLoginTimes();
	//CCLog(" a= %d n= %d",a,n);

	if (a == n&&m==0){
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Node* pause_layer1 = SignInLayer::create();
		pause_layer1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		this->addChild(pause_layer1, 2);
		

	}
	if (n == a + 1){
		GAMEDATA::getInstance()->setTimes(GAMEDATA::getInstance()->getTimes() + 1);
		GAMEDATA::getInstance()->setLoginTimes(0);
		if(m==0){
			GAMEDATA::getInstance()->setDay(GAMEDATA::getInstance()->getCurrentTime());
			GAMEDATA::getInstance()->setLoginTimes(GAMEDATA::getInstance()->getLoginTimes() + 1);
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Node* pause_layer1 = SignInLayer::create();
			pause_layer1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			this->addChild(pause_layer1, 2);
		}
	}
		if (n-a>1)
		{
			GAMEDATA::getInstance()->setLoginTimes(0);
			if(m==0){
			GAMEDATA::getInstance()->setTimes(0);
			GAMEDATA::getInstance()->setLoginTimes(GAMEDATA::getInstance()->getLoginTimes() + 1);
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Node* pause_layer1 = SignInLayer::create();
			pause_layer1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			this->addChild(pause_layer1, 2);
			GAMEDATA::getInstance()->setDay(GAMEDATA::getInstance()->getCurrentTime());
			}
	}
	
	MenuItemImage* start_btn = MenuItemImage::create("start_game_btn_normal.png", "start_game_btn_clicked.png", CC_CALLBACK_0(LobbyScene::startGame, this));
	Menu* start_game = Menu::create(start_btn, NULL);
	start_game->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 95);
	this->addChild(start_game,1);
	//add music
	MenuItemImage* start_btn1 = MenuItemImage::create("btn_bg_normal.png", "btn_bg_click.png", CC_CALLBACK_0(LobbyScene::music, this));
	Menu* start_game1 = Menu::create(start_btn1, NULL);

	start_game1->setPosition(420, 750);

	this->addChild(start_game1);

	CCMenuItemImage *open = CCMenuItemImage::create("open.png", "open.png");
	CCMenuItemImage *close = CCMenuItemImage::create("close.png", "close.png");
	CCMenuItemToggle *close1 = CCMenuItemToggle::createWithTarget(this, menu_selector(LobbyScene::musicCallback), open, close, NULL);
	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		close1->setSelectedIndex(0);
	}
	else
	{
		close1->setSelectedIndex(1);
	}
	close1->setPosition(ccp(182, 353));
	CCMenu* itemToggleMenu = CCMenu::create(close1, NULL);

	this->addChild(itemToggleMenu, 1);


	/*if (GAMEDATA::getInstance()->isFirstLogin() == 0){
		CCLOG("HHJHJHJH");
		);
	}*/
	

	
	return true;


}



void LobbyScene::startGame(){

	//CCLOG("jhdabjsghdkjashcfkj");
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::create()));
	Audio::getInstance()->playBtnEffect();

}


void LobbyScene::music(){



}

void LobbyScene::musicCallback(CCObject* pSender)
{
	//music
	Audio::getInstance()->playBtnEffect();
	Audio::getInstance()->playBGM();
	MenuItemToggle* temp = (MenuItemToggle*)pSender;

	if (temp->getSelectedIndex() == 1)
	{


		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		GAMEDATA::getInstance()->setMusicState(false);
		GAMEDATA::getInstance()->saveMusicState();
	}
	if (temp->getSelectedIndex() == 0)
	{

		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		GAMEDATA::getInstance()->setMusicState(true);
		GAMEDATA::getInstance()->saveMusicState();
	}
}

