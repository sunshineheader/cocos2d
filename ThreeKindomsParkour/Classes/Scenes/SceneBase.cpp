#include "SceneBase.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

bool SceneBase::init()
{
	if (!Scene::init())
	{
		return false;
	}

	addKeyBackReleasedListener();
	initCallbackMap();

	return true;
}

void SceneBase::addKeyBackReleasedListener()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
		{
			onKeyBackReleased();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void SceneBase::registerCallback(const std::string &name, cocos2d::ui::Widget::ccWidgetTouchCallback callback)
{
	_callbackMap[name] = callback;
}

Widget::ccWidgetTouchCallback SceneBase::onLocateTouchCallback(const string &callbackName)
{
	auto result = _callbackMap.find(callbackName);
	return result != _callbackMap.end() ? result->second : nullptr;
}

void SceneBase::initCallbackMap()
{
}

void SceneBase::onKeyBackReleased()
{
}

void SceneBase::initAfterCreate()
{
}