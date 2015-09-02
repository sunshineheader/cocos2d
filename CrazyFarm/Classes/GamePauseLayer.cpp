#include "GamePauseLayer.h"


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
if ( !Layer::init() )
	{
		return false;
	}
  //add sprite to this scene
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* pause_bg = Sprite::create("game_pause.jpg");
	this->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(pause_bg);
	//add resume btn to this layer
	MenuItemImage* resume_btn = MenuItemImage::create("game_resume.png","game_resume.png",CC_CALLBACK_0(GamePauseLayer::resumeGame,this));
	Menu* resume_game = Menu::create(resume_btn,NULL);
	resume_game->setPosition(0,0);
	this->addChild(resume_game);
	return true;
}
void GamePauseLayer::resumeGame(){
	//TODO resume game
	this->removeFromParentAndCleanup(true);
}