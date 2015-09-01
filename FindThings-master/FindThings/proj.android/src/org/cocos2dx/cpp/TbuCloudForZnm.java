package org.cocos2dx.cpp;

import android.app.Activity;
import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import com.skymobi.pay.newsdk.EpsEntry;
import com.skymobi.pay.newsdk.event.RecordEvent;
import com.tallbigup.android.cloud.TbuCloud;

public class TbuCloudForZnm {


	public static void zimonStartApp(Activity activity) {
		TbuCloud.markAppOpened(activity);
		RecordEvent event = new RecordEvent(RecordEvent.Type_Start_Exit);
		event.put(RecordEvent.KEY_Action, RecordEvent.Action_Start);
		event.upload(activity);
	}

	/**
	 * 
	 * @param context
	 */
	public static void zimonExitApp(Context context) {
		RecordEvent event = new RecordEvent(RecordEvent.Type_Start_Exit);
		event.put(RecordEvent.KEY_Action, RecordEvent.Action_Exit);
		event.upload(context);
	}

	/**
	 * 
	 * @param activity
	 */
	public static void zimonShowAdv(Activity activity) {
		EpsEntry mEpsEntry = EpsEntry.getInstance();
		mEpsEntry.showSpotAdv(activity, new Handler() {
			@Override
			public void handleMessage(Message msg) {
				super.handleMessage(msg);
				if (msg.what == EpsEntry.ADVER_SUCCESS_SHOW) {
					Log.e("findthings","adv success");
				} else if (msg.what == EpsEntry.ADVER_ERROR_NOAVAILABLESHOW) {
					Log.e("findthings","adv fail");
				} else if (msg.what == EpsEntry.ADVERT_NO_CAP) {
					Log.e("findthings","no adv");
				}
			}
		});
	}
}
