#include "GameCountLabel.h"
#include "cocos2d.h"
#include "GameLayerScene.h"
#include "GameData.h"
using namespace std;
using namespace cocos2d;
GameCountLabel*GameCountLabel::_instance = nullptr;

bool GameCountLabel::init()
{

	if (!Layer::init())
	{
		return false;
	}
	this->scheduleUpdate();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	std::string game_count_string = String::createWithFormat("%d", game_counts)->_string;
	count_label = Label::create();
	count_label->setTextColor(Color4B::RED);
	count_label->setString(game_count_string);
	count_label->setSystemFontSize(36);
	count_label->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y+350);
	this->addChild(count_label,100);
  
	return true;
}

GameCountLabel*GameCountLabel::getInstance()
{

	if (nullptr==_instance)
	{
		_instance = new GameCountLabel();

	}

	return _instance;
	delete _instance;
}
void GameCountLabel::update(float dt)
{

	game_counts = GameData::getInstance()->get_currcert_sorce();
	std::string game_count_strings = String::createWithFormat("%d", game_counts)->_string;
	count_label->setString(game_count_strings);

}

