#include "GameStartScene.h"
#include"GameLayerScene.h"
#include "GameDefinition.h"
#include "PayForGame.h"
#include "GameData.h"
#include <jni.h>
#include "cocos2d.h"
#include "platform\android\jni\JniHelper.h"
using namespace cocos2d;



Scene*GameStart::createScene()
{
	auto scene = Scene::create();

	auto layer = GameStart::create();

	scene->addChild(layer);

	return scene;
}


bool GameStart::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			//quitDialog->setVisible(true);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

			CCLog("android platform");
						JniMethodInfo methodInfo;
						bool isHave = JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "quitGame", "()V");
						if (isHave){
							JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
						}
#endif
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	if (GameData::getInstance()->get_is_first_login()==true)
	{
		GameData::getInstance()->set_is_first_login(false);
		PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_1);
	}



	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("background.png");
	background->setScale(0.67, 0.63);
	background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	addChild(background);

	auto begin = MenuItemImage::create("begin.png","begin.png",CC_CALLBACK_1(GameStart::game_layer_scene_callback,this));
	begin->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	auto menu = Menu::create(begin,nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);

	return true;
}


void GameStart::game_layer_scene_callback(Ref* psender)
{
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(GameLayer::createScene());

}
