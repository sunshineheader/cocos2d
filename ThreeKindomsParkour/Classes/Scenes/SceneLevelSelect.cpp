#include "SceneLevelSelect.h"
#include "ScenePropSelect.h"
#include "SceneMain.h"

#include "Utils/SceneHelper.h"
#include "Utils/UserData.h"
#include "UI/ScrollController.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_TIMELINE;
using namespace cocostudio;
using namespace ui;
using namespace std;


SceneLevelSelect::SceneLevelSelect()
{
}

SceneLevelSelect::~SceneLevelSelect()
{
}

bool SceneLevelSelect::init()
{
	if (!SceneBase::init())
	{
		return false;
	}

	scheduleUpdate();

	return true;
}

void SceneLevelSelect::initAfterCreate()
{
	//initScroll();
	//initQuest();
}

void SceneLevelSelect::initScroll()
{
	auto scroll = getChildByName("Container")->getChildByName("Scroll");
	auto scrollController = ScrollController::create(scroll);
	scrollController->selectLevel(UserData::getInstance()->getCurrentLevel());
	addChild(scrollController);
}

void SceneLevelSelect::initQuest()
{

}

void SceneLevelSelect::initCallbackMap()
{
	registerCallback("onBackMain", CC_CALLBACK_2(SceneLevelSelect::onBackMain, this));
	registerCallback("onForwardQuest", CC_CALLBACK_2(SceneLevelSelect::onForwardQuest, this));

	registerCallback("onStartGoldCopy", CC_CALLBACK_2(SceneLevelSelect::onStartGoldCopy, this));

	registerCallback("onShowWenChenSelect", CC_CALLBACK_2(SceneLevelSelect::onShowWenChenSelect, this));
	registerCallback("onShowZhuGongSelect", CC_CALLBACK_2(SceneLevelSelect::onShowZhuGongSelect, this));
	registerCallback("onShowWuJiangSelect", CC_CALLBACK_2(SceneLevelSelect::onShowWuJiangSelect, this));
}

void SceneLevelSelect::onKeyBackReleased()
{
	onBackMain(nullptr, Widget::TouchEventType::ENDED);
}

void SceneLevelSelect::update(float delta)
{
}

void SceneLevelSelect::onBackMain(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) 
	{
		auto scene = SceneHelper::createScene(SceneType::Main);
		Director::getInstance()->replaceScene(scene);
	}
}

void SceneLevelSelect::onForwardQuest(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto scene = SceneHelper::createScene(SceneType::PropSelect);
		Director::getInstance()->replaceScene(scene);
	}
}

void SceneLevelSelect::onStartGoldCopy(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	CCLOG("onStartGoldCopy");
}

void SceneLevelSelect::onShowWenChenSelect(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto scene = SceneHelper::createScene(SceneType::CharacterSelect);
		Director::getInstance()->pushScene(scene);
	}
}

void SceneLevelSelect::onShowZhuGongSelect(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto scene = SceneHelper::createScene(SceneType::CharacterSelect);
		Director::getInstance()->pushScene(scene);
	}
}

void SceneLevelSelect::onShowWuJiangSelect(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto scene = SceneHelper::createScene(SceneType::CharacterSelect);
		Director::getInstance()->pushScene(scene);
	}
}