#include "SceneSettlement.h"
#include "SceneLevelSelect.h"
#include "cocostudio/CocoStudio.h"
#include "Utils/SceneHelper.h"
#include "Utils/UserData.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;


SceneSettlement::SceneSettlement()
: _isFinished(false)
, _score(0)
{
}

SceneSettlement::~SceneSettlement()
{
}

bool SceneSettlement::init()
{
	if (!SceneBase::init())
	{
		return false;
	}

	_root = CSLoader::createNode("CsbRes/SceneSettlement.csb");
	addChild(_root);

	auto container = _root->getChildByName("Container");
	auto forward = dynamic_cast<Button*>(container->getChildByName("Btn_Forward"));
	forward->addTouchEventListener([=](Ref *sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED) 
		{
			if (UserData::getInstance()->getGameMode() == SceneGame::GameMode::StageMode) 
			{
				Director::getInstance()->replaceScene(SceneHelper::createScene(SceneType::LevelSelect));
			}
			else
			{
				Director::getInstance()->replaceScene(SceneHelper::createScene(SceneType::Game));
			}
		}
	});

	return true;
}

void SceneSettlement::setFinished(bool isFinished)
{
	auto title = _root->getChildByName("Container")->getChildByName("Title");
	title->getChildByName("Success")->setVisible(isFinished);
	title->getChildByName("Failure")->setVisible(!isFinished);
}

void SceneSettlement::setScore(int score)
{
	auto settlement = _root->getChildByName("Settlement");
	auto scoreNumber = dynamic_cast<Text*>(settlement->getChildByName("ScoreNumber"));
	scoreNumber->setString(String::createWithFormat("%d", score)->getCString());
}

void SceneSettlement::initAfterCreate()
{
}

void SceneSettlement::initCallbackMap()
{
}

void SceneSettlement::onKeyBackReleased()
{
	if (UserData::getInstance()->getGameMode() == SceneGame::GameMode::StageMode)
	{
		Director::getInstance()->replaceScene(SceneHelper::createScene(SceneType::LevelSelect));
	}
	else
	{
		Director::getInstance()->replaceScene(SceneHelper::createScene(SceneType::Main));
	}
}