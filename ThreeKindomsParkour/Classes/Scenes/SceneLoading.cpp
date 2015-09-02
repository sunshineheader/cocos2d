#include "SceneLoading.h"
#include "SceneGame.h"
#include "Utils/SceneHelper.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;


static float s_loadingTime;
static float s_totalTime = 1.0f;

SceneLoading::SceneLoading()
: _progressbar(nullptr)
, _light(nullptr)
, _percent(nullptr)
, _length(0.0f)
{
}

SceneLoading::~SceneLoading()
{
}

bool SceneLoading::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto root = CSLoader::createNode("CsbRes/SceneLoading.csb");
	auto logo = root->getChildByName("Container")->getChildByName("Logo");
	auto progressbar = root->getChildByName("Container")->getChildByName("Progressbar");

	_progressbar = dynamic_cast<LoadingBar*>(progressbar->getChildByName("Progressbar"));
	_light = progressbar->getChildByName("Light");
	_percent = dynamic_cast<Text*>(progressbar->getChildByName("ProgressPercent"));
	_length = _progressbar->getContentSize().width;

	updateProgress(0.0f);

	addChild(root);
	scheduleUpdate();
	s_loadingTime = 0.0f;

	return true;
}

void SceneLoading::initAfterCreate()
{

}

void SceneLoading::initCallbackMap()
{

}

void SceneLoading::onKeyBackReleased()
{

}

void SceneLoading::updateProgress(float percent)
{
	if (percent > 1.0f)
		percent = 1.0f;

	_progressbar->setPercent(percent * 100);
	_light->setPositionX(_length * percent);
	_percent->setString(percentString(percent * 100));
}

void SceneLoading::update(float delta)
{
	s_loadingTime += delta;
	float percent = s_loadingTime / s_totalTime;
	updateProgress(percent);

	if (percent > 0.95f && _light->getNumberOfRunningActions() == 0)
	{
		_light->runAction(ScaleTo::create(s_totalTime * 0.05f, 0.0f));
	}

	if (s_loadingTime > s_totalTime + 0.15f)
	{
		auto scene = SceneHelper::createScene(SceneType::Game);
		Director::getInstance()->replaceScene(scene);
	}
}

string SceneLoading::percentString(float percent) const
{
	return String::createWithFormat("(%%%d)", static_cast<int>(percent))->getCString();
}