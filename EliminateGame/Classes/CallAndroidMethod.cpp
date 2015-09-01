#include "CallAndroidMethod.h"
#include "platform\android\jni\JniHelper.h"
#include "GameData.h"
#include "Audio.h"

CallAndroidMethod* CallAndroidMethod::_instance = 0;
CallAndroidMethod::CallAndroidMethod(){
}
CallAndroidMethod* CallAndroidMethod::getInstance(){
	if(_instance == 0){
		_instance = new CallAndroidMethod();
	}
	return _instance;
}





void CallAndroidMethod::eventToPay(int eventPoint){
	//Audio::getInstance()->playSound(SHOWPAYPOINT);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	    CCLOG("android platform");
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/PayService","eventToPay","(I)V");
		jint event_point = eventPoint;
		if(isHave){
			jobject jobj;
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,event_point);
		}
	#endif	
}


