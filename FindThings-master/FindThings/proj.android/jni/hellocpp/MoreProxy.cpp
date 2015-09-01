#include "cocos2d.h"
#include "../../../Classes/GamePayHandler.h"
#include <jni.h>

using namespace cocos2d;

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_showMoreGameNative(JNIEnv* env,jclass jcl,jboolean show)
	{
		GamePayHandler::getInstance()->showMoreGameNative(show);
	}






















