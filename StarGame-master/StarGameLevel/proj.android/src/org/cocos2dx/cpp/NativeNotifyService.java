package org.cocos2dx.cpp;

import android.app.Activity;

import com.tallbigup.android.gds.nativenotify.NotifyManager;

public class NativeNotifyService {
	
	private static Activity activity;
	
	public static void init(Activity activity){
		NativeNotifyService.activity = activity;
	}
	
	public static void startNativeNotify(){
		NotifyManager.setNextNotification(activity, 
				1000*60*60*12, "羊年消星星", "消灭星星，收集愿望，让生活更开心！");
	}
}
