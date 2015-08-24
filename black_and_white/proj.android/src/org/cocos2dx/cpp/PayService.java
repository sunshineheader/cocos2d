package org.cocos2dx.cpp;

import java.util.Random;

import android.app.Activity;
import android.content.res.Configuration;
import android.util.Log;

import com.poxiao.pay.xbll.GamePay;
import com.tallbigup.android.cloud.TbuCallback;
import com.tallbigup.android.cloud.TbuCloud;
import com.tallbigup.buffett.Buffett;
import com.tallbigup.buffett.OrderResultInfo;
import com.tallbigup.buffett.PayCallback;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.app.configuration.plugin.PayPoint;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.util.EventPoint;
import com.tbu.androidtools.util.EventPointToPayPoint;

public class PayService {
    // currcert activity
	private static Activity activity;
	//currcert gameInfo
	private static GameInfoUtil gameInfo;
	private static String playerId;

	public static void init(Activity activity) {
		PayService.activity = activity;
		gameInfo = GameInfoUtil.getInstance();
		gameInfo.init(activity);
		playerId = GameApplication.getInstance().getPlayerId();
	}
	

	
	

	public static void pay(final int id) {
		final EventPoint event = EventPointToPayPoint.getPaypointByEventpoint(
				activity, id);
		String payId = null;
		Log.i("W_B", "pay event="+event.getEventid());
		Log.i("W_B", "pay paypoint="+event.getPaypoint());
		if (null != event) {
			if (event.getEventState()) {
				payId = String.valueOf(event.getPaypoint());
				if (null != payId) {
					final PayPoint myPayPoint = AppInfo
							.getPayPointByPointId(Integer.valueOf(payId));
					final String orderId = String.valueOf(System
							.currentTimeMillis()) + new Random().nextInt(100);
					
					activity.runOnUiThread(new Runnable() {
						@Override
						public void run() {
							doPayEvent(activity, event.getPaypoint(),
									myPayPoint, orderId, 1,
									new PayCallback(){

								@Override
								public void result(OrderResultInfo arg0) {
									Log.i("W_B", "pay OrderResultInfo="+arg0.getResultCode());
									// TODO Auto-generated method stub
									if(arg0.getResultCode()==0){
										JniPayCallbackHelper.payCallback(id, 0);
									}else{
										JniPayCallbackHelper.payCallback(id, 1);
									}
								}
						
							});
						}
					});
				}
			} else {
				JniPayCallbackHelper.payCallback(id, 2);
			}
		} else {
			JniPayCallbackHelper.payCallback(id, 2);
		}
	}
	

	
	private  static void doPayEvent(final Activity activity, final int payid,
			final PayPoint payPoint, final String orderId, final int payCount,
			final PayCallback callback) {		
//		 TbuCloud.setPayInfo(payState, money, String.valueOf(payPoint),
//		 playerId, desc, payCount, Configuration.enterId, orderId,
//		 errorCode, errorMsg, AppInfo.version, String.valueOf(Buffett
//		 .getInstance().getPayVersionId()), levelId + "",
//		 DeviceInfo.imsi, DeviceInfo.carrier + "", Buffett.getInstance()
//		 .getPayPluginName(), String.valueOf(gameInfo
//		 .getData(GameInfoUtil.USER_TYPE) == 0 ? "new" : "old"),
//		 new TbuCallback() {
//		 @Override
//		 public void result(boolean success) {
//		 Debug.i("�ϴ�֧�����:" + success);
//		 }
//		 });
		GamePay.getInstance().pay(activity, payid, callback);
	}
	
}
