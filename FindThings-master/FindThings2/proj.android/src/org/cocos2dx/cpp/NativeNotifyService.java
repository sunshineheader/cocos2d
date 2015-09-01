package org.cocos2dx.cpp;

import android.app.Activity;

import com.tallbigup.android.gds.nativenotify.NotifyManager;

public class NativeNotifyService {
	
	private static Activity activity;
	
	public static void init(Activity activity){
		NativeNotifyService.activity = activity;
	}
	
	public static void startNativeNotify(){
		NotifyManager.setNextNotification(activity, 1000*60*60*12, "找你妹2015", "休息时间到了，一起来愉快的玩耍吧!");
	}
}
