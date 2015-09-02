#include "GameResultLayer.h"
#include "GameData.h"
#include "LobbyScene.h"
#include "GameScene.h"

bool GameResultLayer::init(){
	if ( !Layer::init() )
	{
		return false;
	}
	//add sprite to this layer
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* result_bg = Sprite::create("pause_bg.png");
	result_bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(result_bg);
	//add result title
	Sprite* result_title =  Sprite::create("game_result_curr_round_score.png");
	result_title->setPosition(240,600);
	this->addChild(result_title);
	//get score from gamedata
	int score = GAMEDATA::getInstance()->getScore();
	//add btn
	MenuItemImage* continue_game = MenuItemImage::create("game_start_another.png","game_start_another.png",CC_CALLBACK_0(GameResultLayer::continueGame,this));
	continue_game->setPosition(240,200);
	
	MenuItemImage* quit_game = MenuItemImage::create("game_result_back.png","game_result_back.png",CC_CALLBACK_0(GameResultLayer::quitGame,this));
	quit_game->setPosition(140,100);

	MenuItemImage* more_game = MenuItemImage::create("game_more_game.png","game_more_game.png",CC_CALLBACK_0(GameResultLayer::showMoreGame,this));
	more_game->setPosition(340,100);

	Menu* result_gui = Menu::create(quit_game,continue_game,more_game,NULL);
	result_gui->setAnchorPoint(ccp(0,0));
	result_gui->setPosition(ccp(0,0));
	this->addChild(result_gui);

	return true;
}

void GameResultLayer::continueGame(){
Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}
void GameResultLayer::quitGame(){
	Director::getInstance()->replaceScene(TransitionFade::create(1,LobbyScene::createScene()));
}
void GameResultLayer::showMoreGame(){

}