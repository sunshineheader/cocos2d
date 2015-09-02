#include "SceneMain.h"
#include "SceneGame.h"
#include "Utils/SceneHelper.h"
#include "Utils/UserData.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "json/document.h"
#include "json/rapidjson.h"

#include "Utils/TmxMapHelper.h"
#include "Math/Polygon.h"
#include "Math/Intersector.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;


SceneMain::SceneMain()
{
}

SceneMain::~SceneMain()
{
}

bool SceneMain::init()
{
	if (!SceneBase::init())
	{
		return false;
	}
	
	scheduleUpdate();

	return true;
}

void SceneMain::initAfterCreate()
{
}

void SceneMain::initCallbackMap()
{
	registerCallback("onExitConfirm", CC_CALLBACK_2(SceneMain::onExitConfirm, this));
	registerCallback("onExitCancel", CC_CALLBACK_2(SceneMain::onExitCancel, this));

	registerCallback("onShowSignDialog", CC_CALLBACK_2(SceneMain::onShowSignDialog, this));
	registerCallback("onShowActivityDialog", CC_CALLBACK_2(SceneMain::onShowActivityDialog, this));
	registerCallback("onStartStageMode", CC_CALLBACK_2(SceneMain::onStartStageMode, this));
	registerCallback("onStartClassicMode", CC_CALLBACK_2(SceneMain::onStartClassicMode, this));

	registerCallback("onShowWenChenSelect", CC_CALLBACK_2(SceneMain::onShowWenChenSelect, this));
	registerCallback("onShowZhuGongSelect", CC_CALLBACK_2(SceneMain::onShowZhuGongSelect, this));
	registerCallback("onShowWuJiangSelect", CC_CALLBACK_2(SceneMain::onShowWuJiangSelect, this));
}

void SceneMain::update(float delta)
{
}

void SceneMain::onKeyBackReleased()
{
	auto exitDialog = getChildByName("ExitDialog");
	if (exitDialog->isVisible())
	{
		onExitCancel(nullptr, Widget::TouchEventType::ENDED);
	}
	else
	{
		exitDialog->runAction(Sequence::createWithTwoActions(Show::create(), FadeIn::create(0.35f)));
	}
}

void SceneMain::onExitConfirm(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	Director::getInstance()->end();
}

void SceneMain::onExitCancel(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto exitDialog = getChildByName("ExitDialog");
		exitDialog->runAction(Sequence::createWithTwoActions(FadeOut::create(0.35f), Hide::create()));
	}
}

void SceneMain::onShowSignDialog(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
}

void SceneMain::onShowActivityDialog(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
}

void SceneMain::onStartStageMode(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		UserData::getInstance()->setGameMode(SceneGame::GameMode::StageMode);
		auto scene = SceneHelper::createScene(SceneType::LevelSelect);
		Director::getInstance()->replaceScene(scene);
	}
}

void SceneMain::onStartClassicMode(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		UserData::getInstance()->setGameMode(SceneGame::GameMode::ClassicMode);
		auto scene = SceneHelper::createScene(SceneType::Game);
		Director::getInstance()->replaceScene(scene);
	}
}

void SceneMain::onShowWenChenSelect(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto scene = SceneHelper::createScene(SceneType::CharacterSelect);
		Director::getInstance()->pushScene(scene);
	}
}

void SceneMain::onShowZhuGongSelect(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto scene = SceneHelper::createScene(SceneType::CharacterSelect);
		Director::getInstance()->pushScene(scene);
	}
}

void SceneMain::onShowWuJiangSelect(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto scene = SceneHelper::createScene(SceneType::CharacterSelect);
		Director::getInstance()->pushScene(scene);
	}
}
