package org.cocos2dx.cpp;

import com.tallbigup.android.cloud.TbuCloud;
import com.tallbigup.buffett.OrderResultInfo;
import com.tallbigup.buffett.PayCallback;
import com.tbu.androidtools.Debug;

import android.app.Activity;

public class PayService {

	private static Activity activity;
	private static GameInfoUtil gameInfo;

	public static void init(Activity activity) {
		PayService.activity = activity;
		gameInfo = GameInfoUtil.getInstance();
		gameInfo.init(activity);
	}

	public static void pay(final int eventId) {
		boolean eventResult = GameApplication.getInstance().doPayEvent(
				activity, String.valueOf(eventId), new PayCallback() {
					@Override
					public void result(OrderResultInfo result) {
						if (result.getResultCode() == OrderResultInfo.PAY_SUCCESS) {
							JniPayCallbackHelper.payCallback(eventId, 0);
							TbuCloud.markUserPay(activity, 1);
						} else if (result.getResultCode() == OrderResultInfo.PAY_CANCEL) {
							JniPayCallbackHelper.payCallback(eventId, 1);
						} else {
							JniPayCallbackHelper.payCallback(eventId, 1);
						}
					}
				});
		if (!eventResult) {
			Debug.e("PayService->pay,event is close or null:eventId = "
					+ eventId);
			JniPayCallbackHelper.payCallback(eventId, 1);
		}
	}

	// private static void setPayInfo(String payState, int payPoint,
	// String playerId, int money, String levelId, String propName,
	// String desc, int payCount, String orderId, String errorCode,
	// String errorMsg) {
	// Debug.i("buffett=" + Buffett.getInstance());
	// TbuCloud.setPayInfo(payState, money, String.valueOf(payPoint),
	// playerId, desc, payCount, Configuration.enterId, orderId,
	// errorCode, errorMsg, AppInfo.version, String.valueOf(Buffett
	// .getInstance().getPayVersionId()), levelId + "",
	// DeviceInfo.imsi, DeviceInfo.carrier + "", Buffett.getInstance()
	// .getPayPluginName(), String.valueOf(gameInfo
	// .getData(GameInfoUtil.USER_TYPE) == 0 ? "new" : "old"),
	// new TbuCallback() {
	// @Override
	// public void result(boolean success) {
	// Debug.i("上传支付结果:" + success);
	// }
	// });
	// }
}
