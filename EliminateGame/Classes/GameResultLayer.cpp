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
	Sprite* result_bg = Sprite::create("game_over_bg.png");
	result_bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(result_bg);
	//get score from gamedata
	int score = GAMEDATA::getInstance()->getScore();
	//add btn
	MenuItemImage* continue_game = MenuItemImage::create("btn_restart01.png","btn_restart02.png",CC_CALLBACK_0(GameResultLayer::continueGame,this));
	continue_game->setPosition(360,100);
	
	MenuItemImage* quit_game = MenuItemImage::create("btn_back01.png","btn_back01.png",CC_CALLBACK_0(GameResultLayer::quitGame,this));
	quit_game->setPosition(140,100);

	Menu* result_gui = Menu::create(quit_game,continue_game,NULL);
	result_gui->setAnchorPoint(ccp(0,0));
	result_gui->setPosition(ccp(0,0));
	this->addChild(result_gui);

	LabelAtlas* playerScore = LabelAtlas::create(
		cocos2d::String::createWithFormat("%d", GAMEDATA::getInstance()->getScore())->_string, "game_result_rank_num.png", 25, 35, '0');
	playerScore->setAnchorPoint(ccp(0.5, 0.5));
	playerScore->setPosition(ccp(240, 560));
	this->addChild(playerScore);

	int currentscore = GAMEDATA::getInstance()->getScore();
	int record = GAMEDATA::getInstance()->getRecord();
	if (currentscore > record){
	GAMEDATA::getInstance()->setRecord(currentscore);
		//show new record
		Sprite* new_record = Sprite::create("sprite_newrecord.png");
		new_record->setPosition(ccp(155,653));
		this->addChild(new_record);
	}

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
