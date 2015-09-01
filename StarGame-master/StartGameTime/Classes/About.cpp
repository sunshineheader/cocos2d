#include "About.h"
#include "Chinese.h"
#include "GameData.h"
#include "Audio.h"
#include "GameScene.h"

About::About(){
	this->init();
}

bool About::init(){
	if(!Node::init()){
		return false;
	}

	auto bg = Sprite::create("bg_mainscene.jpg");
	bg->setPosition(240,400);
	this->addChild(bg);

	auto smallTitle11 = Label::create(ChineseWord("abouttitle11"),"Arial",36);
	smallTitle11->setPosition(60,718);
	smallTitle11->setAnchorPoint(Point(0,0.5));
	this->addChild(smallTitle11);

	int totalScore = GAMEDATA::getInstance()->getTotalScore();

	auto smallTitle12 = Label::create(String::createWithFormat("%d",
			totalScore)->_string+ChineseWord("abouttitle12"),"Arial",36);
	smallTitle12->setPosition(60,668);
	smallTitle12->setAnchorPoint(Point(0,0.5));
	this->addChild(smallTitle12);

	auto smallTitle21 = Label::create(ChineseWord("abouttitle21"),"Arial",36);
	smallTitle21->setPosition(60,618);
	smallTitle21->setAnchorPoint(Point(0,0.5));
	this->addChild(smallTitle21);

	auto smallTitle22 = Label::create(String::createWithFormat("%d",
			totalScore/1000)->_string+"."+String::createWithFormat("%d",
					(totalScore%1000)/100)->_string+ChineseWord("abouttitle22"),"Arial",36);
	smallTitle22->setPosition(60,568);
	smallTitle22->setAnchorPoint(Point(0,0.5));
	this->addChild(smallTitle22);

	auto titleDesc1 = Label::create(ChineseWord("aboutdesc1"),"Arial",24);
	titleDesc1->setPosition(60,478);
	titleDesc1->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc1);

	auto titleDesc2 = Label::create(ChineseWord("aboutdesc2"),"Arial",24);
	titleDesc2->setPosition(60,438);
	titleDesc2->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc2);

	auto titleDesc3 = Label::create(ChineseWord("aboutdesc3"),"Arial",24);
	titleDesc3->setPosition(60,398);
	titleDesc3->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc3);

	auto titleDesc4 = Label::create(ChineseWord("aboutdesc4"),"Arial",24);
	titleDesc4->setPosition(60,358);
	titleDesc4->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc4);

	auto titleDesc5 = Label::create(ChineseWord("aboutdesc5"),"Arial",24);
	titleDesc5->setPosition(60,318);
	titleDesc5->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc5);

	auto titleDesc6 = Label::create(ChineseWord("aboutdesc6"),"Arial",24);
	titleDesc6->setPosition(60,278);
	titleDesc6->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc6);

	auto titleDesc7 = Label::create(ChineseWord("aboutdesc7"),"Arial",24);
	titleDesc7->setPosition(60,238);
	titleDesc7->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc7);

	auto titleDesc8 = Label::create(ChineseWord("aboutdesc8"),"Arial",24);
	titleDesc8->setPosition(60,198);
	titleDesc8->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc8);

	auto titleDesc9 = Label::create(ChineseWord("aboutdesc9"),"Arial",24);
	titleDesc9->setPosition(60,158);
	titleDesc9->setAnchorPoint(Point(0,0.5));
	this->addChild(titleDesc9);

	auto backBtn = MenuItemImage::create(
		"about_back_normal.png","about_back_click.png",CC_CALLBACK_0(About::hideSelf,this)
		);
	auto backMenu = Menu::create(backBtn, NULL);
	backMenu->setPosition(100,70);
	backMenu->setAnchorPoint(Point(0.5,0.5));
	this->addChild(backMenu);

	auto startBtn = MenuItemImage::create(
		"about_start_normal.png","about_start_click.png",CC_CALLBACK_0(About::startGame,this)
		);
	auto startMenu = Menu::create(startBtn, NULL);
	startMenu->setPosition(320,70);
	startMenu->setAnchorPoint(Point(0.5,0.5));
	this->addChild(startMenu);

	return true;
}

void About::hideSelf(){
	Audio::getInstance()->playClick();
	this->setVisible(false);
	this->removeFromParentAndCleanup(true);
}

void About::startGame(){
	Audio::getInstance()->playClick();
	GAMEDATA::getInstance();
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
}
