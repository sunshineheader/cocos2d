#include "CallAndroidMethod.h"
#include "platform\android\jni\JniHelper.h"
#include "GameData.h"

CallAndroidMethod* CallAndroidMethod::_instance = 0;
CallAndroidMethod::CallAndroidMethod(){
}
CallAndroidMethod* CallAndroidMethod::getInstance(){
	if(_instance == 0){
		_instance = new CallAndroidMethod();
	}
	return _instance;
}

void CallAndroidMethod::showMoreGame(){
	CCLOG(">>>>>>>>>>>>>>showMoreGame");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	    CCLOG("android platform");
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/NetWorkService","showMoreGame","()V");
		if(isHave){
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
		}
	#endif
}

void CallAndroidMethod::quit(){
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CCLOG("android platform");
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/NetWorkService","quit","()V");
		if(isHave){
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
		}
	#endif
}

void CallAndroidMethod::pay(int payPoint){
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	    CCLOG("android platform");
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/PayService","pay","(II)V");
		jint pay_point = payPoint;
		jint reviveNum = GAMEDATA::getInstance()->getReviveNum();
		if(isHave){
			jobject jobj;
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,pay_point,reviveNum);
		}
	#endif	
}

void CallAndroidMethod::startNativeNotify(){
	CCLOG(">>>>>>>>>>>>>>startNativeNotify");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	    CCLOG("android platform");
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/NativeNotifyService","startNativeNotify","()V");
		if(isHave){
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
		}
	#endif
}

bool CallAndroidMethod::isSignToday(){
	CCLOG(">>>>>>>>>>>>>>isSignToday");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	    CCLOG("android platform");
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/SignInService","isSignToday","()Z");
		if(isHave){
			return JniHelper::getEnv()->CallStaticBooleanMethod(methodInfo.classID,methodInfo.methodID);
		}else{
			return false;
		}
	#endif
		return false;
}

bool CallAndroidMethod::notSignToday(){
	CCLOG(">>>>>>>>>>>>>>notSignToday");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	    CCLOG("android platform");
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/SignInService","notSignToday","()Z");
		if(isHave){
			return JniHelper::getEnv()->CallStaticBooleanMethod(methodInfo.classID,methodInfo.methodID);
		}else{
			return false;
		}
	#endif
		return false;
}

int CallAndroidMethod::getCurrentSignDayas(){
	CCLOG(">>>>>>>>>>>>>>getCurrentSignDayas");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	    CCLOG("android platform");
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/SignInService","getCurrentSignDays","()I");
		if(isHave){
			return JniHelper::getEnv()->CallStaticIntMethod(methodInfo.classID,methodInfo.methodID);
		}else{
			return 0;
		}
	#endif
		return 0;
}

void CallAndroidMethod::sign(){
	CCLOG(">>>>>>>>>>>>>>sign");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	    CCLOG("android platform");
		JniMethodInfo methodInfo;
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/SignInService","sign","()V");
		if(isHave){
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
		}
	#endif
}
