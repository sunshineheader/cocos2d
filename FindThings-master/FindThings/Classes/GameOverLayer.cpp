#include "GameOverLayer.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "StartScene.h"
#include "GameData.h"
#include "PlayerRank.h"

using namespace cocos2d;

bool GameOverLayer::init(){
	if(!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//set background image
	Sprite* background =Sprite::create("game_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,-1);

	Sprite* title = Sprite::create("game_score_title.png");
	title->setPosition(visibleSize.width/2,visibleSize.height/2+120);
	this->addChild(title,2);


	Sprite* score_bg = Sprite::create("game_start_bg.png");
	score_bg->setPosition(visibleSize.width/2,visibleSize.height/2-40);
	this->addChild(score_bg,2);

	Sprite* game_boy = Sprite::create("game_end_boy.png");
	game_boy->setPosition(visibleSize.width/2+260,visibleSize.height/2);
	this->addChild(game_boy,1);

	//玩家获得的称号，暂时不显示
	/*auto type = getSalTypeByScore(GAMEDATA::getInstance()->getScore());
	std::string imageName = getSalutationByType(type);
	salutation= Sprite::create(imageName);
	salutation->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(salutation,2);*/

	LabelAtlas* game_score = LabelAtlas::create(cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getScore())->_string, "game_score_num.png", 70, 123, '0');
	game_score->setAnchorPoint(Point::ANCHOR_MIDDLE);
	game_score->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(game_score,2);

	Sprite* rank1 =  Sprite::create("rank_1.png");
	int rank1_width = rank1->getBoundingBox().size.width;//获取宽度
	rank1->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	this->addChild(rank1,2);

	LabelAtlas* rank_num = LabelAtlas::create(cocos2d::String::createWithFormat("%d",PLAYERRANK::getInstance()->getRankList(GAMEDATA::getInstance()->getScore()))->_string,"rank_num.png",20,34,'0');
	int num_width = rank_num->getBoundingBox().size.width;
	rank_num->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	this->addChild(rank_num,2);

	Sprite* rank2 =  Sprite::create("rank_2.png");
	int rank2_width = rank2->getBoundingBox().size.width;
	rank2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	this->addChild(rank2,2);

	//根据游戏内容重新安排position
	rank1->setPosition((visibleSize.width-rank1_width-num_width-rank2_width)/2,visibleSize.height/2-65);
	rank_num->setPosition((visibleSize.width+rank1_width-num_width-rank2_width)/2,visibleSize.height/2-62);
	rank2->setPosition((visibleSize.width+rank1_width+num_width-rank2_width)/2,visibleSize.height/2-65);

	Sprite* per =  Sprite::create("rank_per_1.png");
	per->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
	per->setPosition(visibleSize.width/2-20,visibleSize.height/2-105);
	this->addChild(per,2);

	LabelAtlas* rank_per_num = LabelAtlas::create(cocos2d::String::createWithFormat("%d",PLAYERRANK::getInstance()->getRankPer(GAMEDATA::getInstance()->getScore()))->_string,"rank_num.png",20,34,'0');
	rank_per_num->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	rank_per_num->setPosition(visibleSize.width/2,visibleSize.height/2-105);
	this->addChild(rank_per_num,2);

	Sprite* per2 =  Sprite::create("rank_per_2.png");
	per2->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	per2->setPosition(visibleSize.width/2+20,visibleSize.height/2-105);
	this->addChild(per2,2);

	//add goback button
	auto goback = MenuItemImage::create("exit.png","exit.png",CC_CALLBACK_0(GameOverLayer::goBack,this));
	auto continueBtn = MenuItemImage::create("retry.png","retry.png",CC_CALLBACK_0(GameOverLayer::continueGame,this));
	Menu* menu = Menu::create(goback,continueBtn,NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(visibleSize.width/2,visibleSize.height/2-160);
	this->addChild(menu,2); 
	return true;
}

//exit
void GameOverLayer::goBack(){
	Director::getInstance()->replaceScene(TransitionFade::create(1,StartScene::createScene()));	
}


//continue game
void GameOverLayer::continueGame(){
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}


int  GameOverLayer:: getSalTypeByScore(int score){
	if(score<5){
		return 0;
	}else if(score<10){
		return 1;
	}else if(score<20){
		return 2;
	}else if(score<30){
		return 3;
	}else if(score<40){
		return 4;
	}else if(score<50){
		return 5;
	}else{
		return 6;
	}
}


std::string GameOverLayer::getSalutationByType(int type){
	switch(type){
	case 0:
		return "level_1.png";
	case 1:
		return "level_2.png";
	case 2:
		return "level_3.png";
	case 3:
		return "level_4.png";
	case 4:
		return "level_5.png";
	case 5:
		return "level_6.png";
	case 6:
		return "level_7.png";
	default:
		return "level_1.png";
	}
}