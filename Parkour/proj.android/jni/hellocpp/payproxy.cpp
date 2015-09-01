#include "cocos2d.h"
#include "../../../Classes/PayHandler.h"
#include <jni.h>

using namespace cocos2d;

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_payCallback(JNIEnv* env,jclass jcl,jint requestId,jint resultId)
	{
		PayHandler::getInstance()->payCallback(requestId, resultId);
	}
























