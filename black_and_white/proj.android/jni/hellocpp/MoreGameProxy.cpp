#include "cocos2d.h"
#include "../../../Classes/PayHandler.h"
#include <jni.h>

using namespace cocos2d;

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniMoreGameCallbackHelper_switchCallback(JNIEnv* env,jclass jcl,jboolean open)
	{
		PayHandler::getInstance()->moreGameCallback(open);
	}
























