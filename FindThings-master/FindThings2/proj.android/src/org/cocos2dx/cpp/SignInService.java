package org.cocos2dx.cpp;

import android.app.Activity;
import android.util.Log;

import com.tallbigup.android.gds.sign.SignManager;

public class SignInService {
	
	private static Activity activity;
	
	public static void init(Activity activity){
		SignInService.activity = activity;
	}

	public static boolean isSignToday(){
		Log.i("MCH","isSignToday=" + SignManager.isSignToday(activity));
		return SignManager.isSignToday(activity);
	}
	
	public static boolean notSignToday(){
		return !SignManager.isSignToday(activity);
	}
	
	public static int getCurrentSignDays(){
		return SignManager.getCurrentSignDays(activity);
	}
	
	public static void sign(){
		SignManager.sign(activity);
	}
}
