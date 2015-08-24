#include "GameOverLabel.h"
#include "GameLayerScene.h"
#include "GameStartScene.h"
#include "cocos2d.h"
#include"ChineseWorld.h"
#include "GameData.h"
#include "PlayerRank.h"
using namespace cocos2d;
bool GameOverLabel::init()
{

	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//游戏结束
	std::string chinese_game_over = ChineseWord("title");
	auto game_over = Label::create();
	game_over->setString(chinese_game_over);
	game_over->setSystemFontSize(48);
	game_over->setPosition(visibleSize.width/2,visibleSize.height/2+300);
	addChild(game_over);

	 //当前分数
	currcert_sorce = GameData::getInstance()->get_currcert_sorce();
	std::string currcert_sorce_string = String::createWithFormat("%d",currcert_sorce)->_string;
	auto  currcert_sorce_label = Label::create();
	currcert_sorce_label->setString(currcert_sorce_string);
	currcert_sorce_label->setSystemFontSize(144);
	currcert_sorce_label->setPosition(visibleSize.width/2,visibleSize.height/2+150);
	addChild(currcert_sorce_label);

	//最佳分数
	if (currcert_sorce>GameData::getInstance()->getBestSorce()){
		GameData::getInstance()->setBestSorce(currcert_sorce);
	}

	std::string best_socre_string = ChineseWord("zuijia") + String::createWithFormat(" : %d", GameData::getInstance()->getBestSorce())->_string;
	auto best_socre_label = Label::create();
	best_socre_label->setString(best_socre_string);
	best_socre_label->setSystemFontSize(64);
	best_socre_label->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(best_socre_label);

	// 当前排名
	int currcert_sort = PLAYERRANK::getInstance()->getRankList(currcert_sorce);
	std::string my_sorce_sort = ChineseWord("pai") + String::createWithFormat("%d", currcert_sort)->_string + ChineseWord("ming");
	auto currcert_sort_label = Label::create();
	currcert_sort_label->setString(my_sorce_sort);
	currcert_sort_label->setSystemFontSize(48);
	currcert_sort_label->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 100);
	addChild(currcert_sort_label);


	//游戏返回
	string game_back_string = ChineseWord("back");
	auto my_game_back_label = Label::create();
	my_game_back_label->setString(game_back_string);
	my_game_back_label->setSystemFontSize(36);


	//游戏重来
	string game_again_string = ChineseWord("again");
	auto my_game_again_label = Label::create();
	my_game_again_label->setString(game_again_string);
	my_game_again_label->setSystemFontSize(36);


	auto game_back_item = MenuItemLabel::create(my_game_back_label, CC_CALLBACK_1(GameOverLabel::game_back_callback, this));
	game_back_item->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y - 200));

	auto game_again_item = MenuItemLabel::create(my_game_again_label, CC_CALLBACK_1(GameOverLabel::game_again_callback, this));
	game_again_item->setPosition(Vec2(3 * (visibleSize.width / 4) + origin.x, visibleSize.height / 2 + origin.y - 200));

	auto menu = Menu::create(game_again_item, game_back_item, nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);
	return true;
}

void GameOverLabel::game_again_callback(Ref* psender)
{
	GameData::getInstance()->set_currcert_sorce(0);
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(GameLayer::createScene());
}

void GameOverLabel::game_back_callback(Ref* psender)
{
	GameData::getInstance()->set_currcert_sorce(0);
	Director::getInstance()->replaceScene(GameStart::createScene());
}