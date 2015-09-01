package org.cocos2dx.cpp;

public class JniPayCallbackHelper {	
	public static native void payCallback(int requestId, int resultId);
	public static native void showMoreGameNative(Boolean show);
}
