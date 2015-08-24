package org.cocos2dx.cpp;

import android.app.Activity;
import android.util.Log;


import com.tallbigup.android.gds.sign.SignManager;

public class SignInService {
	
	private static Activity activity;
	private static int signDay;
	
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
	
	public static boolean isHasShowSignInPay(){
		Log.e("MCH","isHasShowSignInPay=" + GameApplication.getInstance().getHasShowSignInPay());
		return GameApplication.getInstance().getHasShowSignInPay();
	}
	
	public static int getCurrentSignDays(){
		signDay = SignManager.getCurrentSignDays(activity);
		return signDay;
	}
	
	public static void sign(){
		SignManager.sign(activity);
		if(signDay == 10){
			SignManager.cleanSignDays(activity);
		}
	}
}
