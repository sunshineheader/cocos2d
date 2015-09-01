#include "cocos2d.h"
#include "../../../Classes/GamePayHandler.h"
#include <jni.h>

using namespace cocos2d;

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_payCallback(JNIEnv* env,jclass jcl,jint requestId,jint resultId)
	{
		GamePayHandler::getInstance()->payCallback(requestId, resultId);
	}






















