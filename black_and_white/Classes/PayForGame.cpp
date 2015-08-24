#include "PayForGame.h"
#include "GameDefinition.h"
#include "platform\android\jni\JniHelper.h"
#include "Payhandler.h"

PayForGame* PayForGame::_instance = nullptr;
PayForGame::PayForGame()
{


}


PayForGame::~PayForGame()
{

}
PayForGame*PayForGame::getInstance()
{

	if (nullptr == _instance)
	{
		_instance = new PayForGame();
	};
	return _instance;
	delete _instance;
	_instance = nullptr;
}

void PayForGame::payformoney_callback(int payforgame_event_id)
{
	switch (payforgame_event_id)
	{
	case PAYFORGAME_EVENT_1:
		payforGame(PAYFORGAME_EVENT_1);
		break;

	case PAYFORGAME_EVENT_2:
		payforGame(PAYFORGAME_EVENT_2);
		break;

	case PAYFORGAME_EVENT_3:
		payforGame(PAYFORGAME_EVENT_3);
		break;

	case PAYFORGAME_EVENT_4:
		payforGame(PAYFORGAME_EVENT_4);
		break;

	case PAYFORGAME_EVENT_5:
		payforGame(PAYFORGAME_EVENT_5);
		break;

	case PAYFORGAME_EVENT_6:
		payforGame(PAYFORGAME_EVENT_6);

		break;
	case PAYFORGAME_EVENT_7:
		payforGame(PAYFORGAME_EVENT_7);
		break;

	case PAYFORGAME_EVENT_8:
		payforGame(PAYFORGAME_EVENT_8);
		break;
	default:
		break;
	}
}
void PayForGame::payforGame(int id)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("android platform");
	JniMethodInfo methodInfo;
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/PayService", "pay", "(I)V");
	if (isHave){
		jint pay_point = id;
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, id);
	}
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	CCLOG("win platform");
	PayHandler::getInstance()->payCallback(id,0);

#endif
	

}
