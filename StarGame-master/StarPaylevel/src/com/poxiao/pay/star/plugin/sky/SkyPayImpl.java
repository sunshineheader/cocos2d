package com.poxiao.pay.star.plugin.sky;

import java.util.HashMap;
import java.util.Map;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.poxiao.pay.star.GamePay;
import com.skymobi.pay.app.PayApplication;
import com.skymobi.pay.sdk.SkyPayServer;
import com.skymobi.pay.sdk.SkyPaySignerInfo;
import com.tallbigup.buffett.OrderInfo;
import com.tallbigup.buffett.OrderResultInfo;
import com.tallbigup.buffett.PayCallback;
import com.tallbigup.buffett.PayInterface;
import com.tallbigup.buffett.plugin.configuration.Configuration;
import com.tallbigup.buffett.plugin.deviceinfo.DeviceInfo;

public class SkyPayImpl implements PayInterface{
	
	
	//订单参数
	private static final String ORDER_INFO_PAY_METHOD = "payMethod";
	private static final String ORDER_INFO_SYSTEM_ID = "systemId";
	private static final String ORDER_INFO_CHANNEL_ID = "channelId";
	private static final String ORDER_INFO_PAY_POINT_NUM = "payPointNum";
	private static final String ORDER_INFO_ORDER_DESC = "orderDesc";
	private static final String ORDER_INFO_GAME_TYPE = "gameType";

	private static String mOrderInfo = null;
	private static payhandle mPayHandler = null;
	private static SkyPayServer mSkyPayServer = null;
	
	private OrderResultInfo result;
	private OrderInfo orderInfo;
	private PayCallback callback;
	private Activity activity;

	private PayApplication payApplicaton = new PayApplication();

	@Override
	public void OnActivityCreate(Activity activity) {		
	}

	@Override
	public void OnActivityDestory(Activity activity) {
	}

	@Override
	public void OnActivityPause(Activity activity) {
	}

	@Override
	public void OnActivityResume(Activity activity) {
	}

	@Override
	public void initPayApplication(Context context) {
		payApplicaton.applicationOnCreat(context);
	}

	@Override
	public void pay(final Activity activity, final OrderInfo orderInfo, final PayCallback callback) {
		this.orderInfo = orderInfo;
		this.callback = callback;
		this.activity = activity;
		
		result = new OrderResultInfo();
		mPayHandler = new payhandle();
		mSkyPayServer = SkyPayServer.getInstance();
		
		int initRet = mSkyPayServer.init(mPayHandler);

		if (SkyPayServer.PAY_RETURN_SUCCESS == initRet) {
			//斯凯付费实例初始化成功！
		} else {
			//服务正处于付费状态	 或	传入参数为空
			result.setErrorCode(String.valueOf(initRet));
			result.setErrorMsg("服务正处于付费状态或传入参数为空");
			result.setResultCode(1);
			result.setSequence(orderInfo.getSequence());
			callback.result(result);
		}
		
		SkyPaySignerInfo skyPaySignerInfo = new SkyPaySignerInfo();

		skyPaySignerInfo.setMerchantPasswd("hyu^&5(&122");
		skyPaySignerInfo.setMerchantId("10642");
		skyPaySignerInfo.setAppId(String.valueOf(GamePay.getInstance().getAppId()));
		skyPaySignerInfo.setAppName(GamePay.getInstance().getAppName());
		skyPaySignerInfo.setAppVersion(DeviceInfo.version);
		skyPaySignerInfo.setPayType("3");
		skyPaySignerInfo.setPrice(String.valueOf(orderInfo.getPrice()));
		skyPaySignerInfo.setOrderId(orderInfo.getOrderId());

		String reserved1 = "1";
		String reserved2 = "2";
		String reserved3 = "1|=2/3";

		skyPaySignerInfo.setReserved1(reserved1, false);
		skyPaySignerInfo.setReserved2(reserved2, false);
		skyPaySignerInfo.setReserved3(reserved3, true);


		/*
		*  调用getOrderString函数生成签名相关信息
		*/
		String signOrderInfo =  mSkyPayServer.getSignOrderString(skyPaySignerInfo);

		mOrderInfo = 
		ORDER_INFO_PAY_METHOD + "=" + "sms" + "&"
		+ ORDER_INFO_SYSTEM_ID + "=" + "300024" + "&"
		+ ORDER_INFO_CHANNEL_ID +  "=" + Configuration.enterId + "&"
		+ ORDER_INFO_PAY_POINT_NUM + "=" + orderInfo.getPayPointNum() + "&"
		+ ORDER_INFO_GAME_TYPE + "=" + "2" + "&"
		+ ORDER_INFO_ORDER_DESC + "=" + orderInfo.getOrderDesc() + "&"
		+ "useAppUI=true" + "&"
		+ signOrderInfo;
		
		Log.i("MCH","mOrerInfo = " + mOrderInfo);

		//开始计费
		activity.runOnUiThread(new Runnable(){

			@Override
			public void run() {
				int payRet = mSkyPayServer.startActivityAndPay(activity, mOrderInfo);

//		    	if (SkyPayServer.PAY_RETURN_SUCCESS == payRet) {
//		    		//初始化成功
//
//		    	} else {
//		    		//未初始化 \ 传入参数有误 \ 服务正处于付费状态
//		    		result.setErrorCode(String.valueOf(payRet));
//					result.setErrorMsg("服务正处于付费状态或传入参数为空");
//					result.setResultCode(1);
//					result.setSequence(orderInfo.getSequence());
//					callback.result(result);
//		    	}
			}});
	}
	
	class payhandle extends Handler {

		public static final String STRING_MSG_CODE = "msg_code";
		public static final String STRING_ERROR_CODE = "error_code";
		public static final String STRING_PAY_STATUS = "pay_status";
		public static final String STRING_PAY_PRICE = "pay_price";
		public static final String STRING_CHARGE_STATUS = "3rdpay_status";


		@Override
		public void handleMessage(Message msg) {
			super.handleMessage(msg);

			if (msg.what == SkyPayServer.MSG_WHAT_TO_APP) {
				String retInfo = (String) msg.obj;
				 Log.e("MCH", "插件返回的内容为:" + retInfo);
				Map<String, String> map = new HashMap<String, String>();
				
				String[] keyValues = retInfo.split("&|=");
				for (int i = 0; i < keyValues.length; i = i + 2) {
					map.put(keyValues[i], keyValues[i + 1]);
				}
				Log.d("MCH", "消息MAP数量为:" + map.size());
				int msgCode = Integer.parseInt(map.get(STRING_MSG_CODE));
				// 解析付费状态和已付费价格
				// 使用其中一种方式请删掉另外一种
				if (msgCode == 100) {

						//短信付费返回
						if (map.get(STRING_PAY_STATUS)!=null) {
								int payStatus = Integer.parseInt(map.get(STRING_PAY_STATUS));
								int errcrCode = 0;
								if (map.get(STRING_ERROR_CODE) != null) {
									errcrCode = Integer.parseInt(map.get(STRING_ERROR_CODE));
								}

								switch(payStatus) {
								case 102:
									//付费成功
									result.setErrorCode("0");
									result.setErrorMsg("支付成功");
									result.setResultCode(0);
									result.setSequence(orderInfo.getSequence());
									callback.result(result);
									break;
								case 101:
									//付费失败
									result.setErrorCode(String.valueOf(errcrCode));
									result.setErrorMsg("付费失败：" + errcrCode);
									result.setResultCode(1);
									result.setSequence(orderInfo.getSequence());
									callback.result(result);
									break;
								}
						}

				} else {
					// 解析错误码
					int errcrCode = Integer.parseInt(map.get(STRING_ERROR_CODE));
					//付费失败
					if(errcrCode == 503 || errcrCode == 805){
						Log.i("MCH","-----------------取消支付");
						result.setErrorCode(String.valueOf(errcrCode));
						result.setErrorMsg("取消支付");
						result.setResultCode(-3);
						result.setSequence(orderInfo.getSequence());
						callback.result(result);
					}else{
						result.setErrorCode(String.valueOf(errcrCode));
						result.setErrorMsg("付费失败：" + errcrCode);
						result.setResultCode(1);
						result.setSequence(orderInfo.getSequence());
						callback.result(result);
					}
				}
			}
		}
	}

	@Override
	public String getPayPluginName() {
		return "sky";
	}

	@Override
	public int getPayVersionId() {
		return 2;
	}

	@Override
	public void OnActivityResult(int arg0, int arg1, Intent arg2) {
		
	}

}
