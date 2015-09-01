package com.poxiao.pay.receiver;

import java.util.Timer;
import java.util.TimerTask;

import com.poxiao.pay.GamePay;
import com.poxiao.smspay.http.PayHttpClient;
import com.poxiao.smspay.http.SwitchCallback;

import android.app.ActivityManager;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;

public class NetChangeReceiver extends BroadcastReceiver {
	
	private Context context;
	private int conn = 0;

	@Override
	public void onReceive(Context context, Intent intent) {

		doTimer(true);
		Log.e("MCH", "网络状态变化了。。。。。。。");
		this.context = context;
		String action = intent.getAction();
		if (action.equals(ConnectivityManager.CONNECTIVITY_ACTION)) {
			if(!isAppVisible(context)){
				conn = 0;
				return;
			}
			if(!GamePay.isSuccessInit() || conn >= 5){
				return;
			}
	        //获取系统服务
	        ConnectivityManager connectivityManager = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
	  		//获取状态
	  		NetworkInfo info = connectivityManager.getActiveNetworkInfo();
	  		//判断wifi已连接的条件
	  		if(info != null && info.isAvailable()){
		  		conn++;
		  		doTimer(true);
		  		Log.e("POXIAO",">>>>>>start timer");
	  		}
		}		
	}
	
	private Timer timer;
	private TimerTask task;

	public void doTimer(boolean isStart) {
		if (!isStart) {
			if (task != null) {
				task.cancel();
			}
		} else {
			// 启动计时
			timer = new Timer();
			task = new TimerTask() {
				@Override
				public void run() {
					Log.e("POXIAO",">>>>>>get switch");
					PayHttpClient.getSmsPaySwitch(context, new SwitchCallback(){

						@Override
						public void result(String open) {
		  					GamePay.getInstance().changeWifiInit(open);
							doTimer(false);
						}
		  			});
				}
			};
			timer.schedule(task, 6000, 1 * 60000);
		}
	}
		
	private boolean isAppVisible(Context activity) {
		ActivityManager am = (ActivityManager) activity
				.getSystemService(Context.ACTIVITY_SERVICE);
		ComponentName cn = am.getRunningTasks(1).get(0).topActivity;
		if (cn.getPackageName().equals(activity.getPackageName())) {
			return true;
		}
		return false;
	}
}
