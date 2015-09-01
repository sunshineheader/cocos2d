#include "GameResultLayer.h"
#include "GameData.h"
#include "LobbyScene.h"
#include "GameScene.h"
#include"Audio.h"
#include"Matrix.h"
#include"GameLayer.h"

bool GameResultLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	//add sprite to this layer
	animTime = 0;
	scoreNum = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite* result_bg = Sprite::create("pause_bg.png");
	result_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(result_bg);
	//add result title
	Sprite* result_title = Sprite::create("game_result_curr_round_score.png");
	result_title->setPosition(240, 720);
	this->addChild(result_title);
	//get score from gamedata
	score = GAMEDATA::getInstance()->getAchievescore();
	//int count = 0;//´¢´æÎ»Êý
	//int i = 1;
	//do
	//{
	//	++count;
	//	i *= 10;
	//} while (i <= score);
	labelnumber = LabelAtlas::create("0", "resultNum.png", 49, 70, '0');
	labelnumber->setPosition(240, 650);
	labelnumber->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(labelnumber);

	//add flower

	auto flower = Sprite::create("flower.png");
	flower->setPosition(240, 600);
	flower->setScale(0.8);
	addChild(flower);

	//add tanzhaodeng left
	auto sprite0 = Sprite::create("w.png");
	auto action0 = Sequence::create(
		RotateTo::create(2.0f, -90),
		RotateTo::create(2.0f, 90),
		nullptr);
	auto rep0 = RepeatForever::create(action0->clone());
	sprite0->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite0->setAnchorPoint(Vec2(0.5, 0.0));
	sprite0->setScale(0.7);
	addChild(sprite0);
	sprite0->runAction(rep0);

	//add tanzhaodeng right
	auto sprite1 = Sprite::create("w.png");
	auto action1 = Sequence::create(
		RotateTo::create(2.0f, 90),
		RotateTo::create(2.0f, -90),
		nullptr);
	auto rep1 = RepeatForever::create(action1->clone());
	sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite1->setAnchorPoint(Vec2(0.5, 0.0));
	sprite1->setScale(0.7);
	addChild(sprite1);
	sprite1->runAction(rep1);

	//add touxiang
	auto touxiang = Sprite::create("chiken.png");
	touxiang->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	touxiang->setScale(0.8);
	addChild(touxiang);

	auto sprite4 = Sprite::create("game_result_shine.png");
	sprite4->setPosition(Vec2(visibleSize.width / 2 + origin.x + 90, visibleSize.height / 2 + origin.y));
	auto action4 = FadeIn::create(5.0f);
	auto action1Back = action4->reverse();
	auto action4_0 = FadeOut::create(1.0f);
	auto action2Back = action4_0->reverse();
	auto action4_1 = Sequence::create(action4, action1Back, action4_0, action2Back, nullptr);
	auto rep4 = RepeatForever::create(action4_1->clone());
	addChild(sprite4);
	sprite4->runAction(rep4);

	// add a label shows "number"
	CCLabelAtlas* labelnumber1 = LabelAtlas::create("2", "percent.png", 16, 22, '0');
	labelnumber1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 10,
		origin.y + visibleSize.height / 2 - 170));
	labelnumber1->setScale(2);
	auto act3 = Sequence::create(DelayTime::create(2), ScaleBy::create(1, 0.7), nullptr);
	labelnumber1->runAction(act3);
	auto director = Director::getInstance();
	director->getActionManager()->pauseTarget(labelnumber1);
	this->addChild(labelnumber1, 1);

	//add mingci big
	auto sprite = Sprite::create("di.png");
	sprite->setPosition(origin.x + visibleSize.width / 2 - 70, origin.y + visibleSize.height / 2 - 150);
	sprite->setScale(1.5);
	addChild(sprite);
	auto act1 = Sequence::create(DelayTime::create(2), ScaleBy::create(1, 0.7), nullptr);
	sprite->runAction(act1);

	auto spritem = Sprite::create("ming.png");
	spritem->setScale(1.5);
	spritem->setPosition(origin.x + visibleSize.width / 2 + 70, origin.y + visibleSize.height / 2 - 150);
	addChild(spritem);
	auto act2 = Sequence::create(DelayTime::create(2), ScaleBy::create(1, 0.7), nullptr);
	spritem->runAction(act2);

	//add defeat
	auto defeat = Sprite::create("defeat.png");
	defeat->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 200);

	addChild(defeat);


	//add btn
	auto menu = Menu::create();

	auto spriteNormal = Sprite::create("game_start_another.png");

	auto spriteSelected = Sprite::create("game_start_another.png");
	spriteNormal->setScale(0.9, 0.9);
	auto settingBtnOkItem = MenuItemSprite::create(spriteNormal, spriteSelected, nullptr, CC_CALLBACK_0(GameResultLayer::continueGame, this));
	settingBtnOkItem->setPosition(Point(250, 100));
	menu->addChild(settingBtnOkItem);

	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	//CCMenuItemImage *open1 = CCMenuItemImage::create("game_start_another.png", "game_start_another.png");
	//CCMenuItemImage *close1 = CCMenuItemImage::create("game_start_another.png", "game_start_another.png");
	//CCMenuItemToggle *continue_game = CCMenuItemToggle::createWithTarget(this, menu_selector(GameResultLayer::continueGame), open1, close1, NULL);
	//CCMenuItemImage* continue_game = CCMenuItemImage::create("game_start_another.png", "btn_quick_game_pre.png", CC_CALLBACK_0(GameResultLayer::continueGame, this));
	//CCMenu* itemToggleMenu = CCMenu::create(continue_game, NULL);
	//addChild(itemToggleMenu);


	auto menu1 = Menu::create();

	auto spriteNormal1 = Sprite::create("game_result_back.png");

	auto spriteSelected1 = Sprite::create("game_result_back.png");
	spriteNormal1->setScale(0.9, 0.9);
	auto settingBtnOkItem1 = MenuItemSprite::create(spriteNormal1, spriteSelected1, nullptr, CC_CALLBACK_0(GameResultLayer::quitGame, this));
	settingBtnOkItem1->setPosition(Point(70, 100));
	menu1->addChild(settingBtnOkItem1);

	menu1->setPosition(Point(0, 0));
	this->addChild(menu1);

	auto menu2 = Menu::create();

	auto spriteNormal2 = Sprite::create("game_more_game.png");

	auto spriteSelected2 = Sprite::create("game_more_game.png");
	spriteNormal2->setScale(0.9, 0.9);
	auto settingBtnOkItem2 = MenuItemSprite::create(spriteNormal2, spriteSelected2, nullptr, CC_CALLBACK_0(GameResultLayer::showMoreGame, this));
	settingBtnOkItem2->setPosition(Point(430, 100));
	menu2->addChild(settingBtnOkItem2);

	menu2->setPosition(Point(0, 0));
	this->addChild(menu2);



	this->scheduleUpdate();
	return true;
}

void GameResultLayer::update(float delta){
	if (this->isVisible()){
		animTime += delta / 0.05;


		if (animTime >= 60000000){
			animTime = 6000;
		}

		if (animTime >= 5){
			scoreNum = (animTime - 5) / 30 * score;
		}

		if (scoreNum > score){
			scoreNum = score;
		}
		labelnumber->setString(cocos2d::String::createWithFormat("%d", (int)scoreNum)->_string);
	}
	if (animTime >= 40){

	}
}

void GameResultLayer::continueGame(){


	//CCMenuItem* clickedItem = (CCMenuItem *)psender;

	//clickedItem->setScale(1.2f);

	//auto act3 = Sequence::create(DelayTime::create(0), ScaleBy::create(0.3, 0.83), nullptr);
	//clickedItem->runAction(act3);
	Audio::getInstance()->playBtnEffect();
	GAMEDATA::getInstance()->init();
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::create()));
	GAMEDATA::getInstance()->setAchievescore(0);
}
void GameResultLayer::quitGame(){
	Audio::getInstance()->playBtnEffect();
	Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::createScene()));
	GAMEDATA::getInstance()->setAchievescore(0);
}
void GameResultLayer::showMoreGame(){
	Audio::getInstance()->playBtnEffect();
}
