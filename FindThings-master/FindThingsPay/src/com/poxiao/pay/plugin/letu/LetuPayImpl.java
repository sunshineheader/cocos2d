package com.poxiao.pay.plugin.letu;

import java.util.HashMap;
import java.util.Map;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.lyhtgh.pay.SdkPayServer;
import com.lyhtgh.pay.application.PayApplication;
import com.poxiao.pay.GamePay;
import com.tallbigup.buffett.OrderInfo;
import com.tallbigup.buffett.OrderResultInfo;
import com.tallbigup.buffett.PayCallback;
import com.tallbigup.buffett.PayInterface;
import com.tallbigup.buffett.plugin.deviceinfo.DeviceInfo;

public class LetuPayImpl implements PayInterface{
	
	private static payhandle mPayHandler = null;
	
	private OrderResultInfo result;
	private OrderInfo orderInfo;
	private PayCallback callback;

	private PayApplication payApplicaton = new PayApplication();
	
	private static boolean hasInitSuccess = false;
	private static boolean hasInit = false;

	@Override
	public void OnActivityCreate(Activity activity) {		
	}

	@Override
	public void OnActivityDestory(Activity activity) {
		SdkPayServer.getInstance().unInitSdkPayServer();
	}

	@Override
	public void OnActivityPause(Activity activity) {
	}

	@Override
	public void OnActivityResume(Activity activity) {
	}

	@Override
	public void initPayApplication(Context context) {
		Log.i("MCH","hasInit=" + hasInit);
		if(hasInit){
			return;
		}
		hasInit = true;
		payApplicaton.a(context);
		if(!hasInitSuccess){
			int initRet = SdkPayServer.getInstance().initSdkPayServer();
			Log.i("MCH","application on create >>>>initRet=" + initRet);
			if(initRet == 0){
				hasInitSuccess = true;
			}
		}
	}

	@Override
	public void pay(final Activity activity, final OrderInfo orderInfo, final PayCallback callback) {
		this.orderInfo = orderInfo;
		this.callback = callback;
		
		result = new OrderResultInfo();
		mPayHandler = new payhandle();
		SdkPayServer mPayServer = SdkPayServer.getInstance();

		if(!hasInitSuccess){
			int initRet = SdkPayServer.getInstance().initSdkPayServer();
			Log.e("MCH","initRet="+initRet);
			if (initRet == 0) {
				//乐途付费实例初始化成功！
				hasInitSuccess = true;
			} else {
				//服务正处于付费状态	 或	传入参数为空
				Log.i("MCH","initRet=" + initRet);
				result.setErrorCode(String.valueOf(initRet));
				result.setErrorMsg("支付初始化失败");
				result.setResultCode(1);
				result.setSequence(orderInfo.getSequence());
				callback.result(result);
				return;
			}
		}
		
		String merchantKey = "H@P6*1$Z#nkL9*X&";
		String orderId = orderInfo.getOrderId();
		String merchantId = "HZPXPAY1001";
		String appId = "3030009";
		String appVer = DeviceInfo.version;
		String appName = GamePay.getInstance().getAppName();
		String pointNum = String.valueOf(orderInfo.getPayPointNum());
		String payPrice = String.valueOf(orderInfo.getPrice());
		String productName = orderInfo.getProductName();
		String orderDesc = orderInfo.getOrderDesc();
		String channelId = DeviceInfo.entrance;
		String channelName = "1000";
		String payType = getPayType(orderInfo.getPayPointNum());
		String gameType = "0";
		
		Log.e("MCH","payPrice = "+payPrice);
		if(appName == null || appName.equals("")){
			appName = "找你妹2015";
		}

		String sig =  mPayServer.getSignature(merchantKey, 
				SdkPayServer.ORDER_INFO_ORDER_ID, orderId, 
				SdkPayServer.ORDER_INFO_MERCHANT_ID, merchantId, 
				SdkPayServer.ORDER_INFO_APP_ID, appId, 
                SdkPayServer.ORDER_INFO_APP_VER, appVer, 
                SdkPayServer.ORDER_INFO_APP_NAME, appName, 
                SdkPayServer.ORDER_INFO_PAYPOINT, pointNum, 
                SdkPayServer.ORDER_INFO_PAY_PRICE, payPrice, 
                SdkPayServer.ORDER_INFO_PRODUCT_NAME, productName, 
                SdkPayServer.ORDER_INFO_ORDER_DESC, orderDesc, 
                SdkPayServer.ORDER_INFO_CP_CHANNELID, channelId, 
                SdkPayServer.ORDER_INFO_SDK_CHANNELID, channelName, 
                SdkPayServer.ORDER_INFO_PAY_TYPE, payType, 
                SdkPayServer.ORDER_INFO_GAME_TYPE, gameType
        );


		String mOrderInfo = 
				SdkPayServer.ORDER_INFO_ORDER_ID + "=" + orderId + "&" +
				SdkPayServer.ORDER_INFO_MERCHANT_ID + "=" + merchantId + "&" +
				SdkPayServer.ORDER_INFO_APP_ID + "=" + appId + "&" +
                SdkPayServer.ORDER_INFO_APP_VER + "=" + appVer + "&" +
                SdkPayServer.ORDER_INFO_APP_NAME + "=" + appName + "&" +
                SdkPayServer.ORDER_INFO_PAYPOINT + "=" + pointNum + "&" +
                SdkPayServer.ORDER_INFO_PAY_PRICE + "=" + payPrice + "&" +
                SdkPayServer.ORDER_INFO_PRODUCT_NAME + "=" + productName + "&" +
                SdkPayServer.ORDER_INFO_ORDER_DESC + "=" + orderDesc + "&" +
                SdkPayServer.ORDER_INFO_CP_CHANNELID + "=" + channelId + "&" +
                SdkPayServer.ORDER_INFO_SDK_CHANNELID + "=" + channelName + "&" +
                SdkPayServer.ORDER_INFO_PAY_TYPE + "=" + payType + "&" +
                SdkPayServer.ORDER_INFO_GAME_TYPE + "=" + gameType + "&" +
                SdkPayServer.ORDER_INFO_MERCHANT_SIGN + "=" + sig + "&" +
                SdkPayServer.ORDER_INFO_SHOW_PAYUIKEY + "=" + "5f96e93a5096d14e900cd1b1b84a939e";
		
		Log.i("MCH","mOrerInfo = " + mOrderInfo);
    	GamePay.getInstance().setLetuPayOrderInfo(mOrderInfo);
    	mPayServer.startSdkServerPay(activity, mPayHandler, mOrderInfo);
	}
	
	private String getPayType(int payPoint){
		if(payPoint <= 3){
			return "0";
		}else{
			return "1";
		}
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

			if (msg.what == SdkPayServer.MSG_WHAT_TO_APP) {
				String retInfo = (String) msg.obj;
				 Log.e("MCH", "插件返回的内容为:" + retInfo);
				Map<String, String> map = new HashMap<String, String>();
				
				String[] keyValues = retInfo.split("&|=");
				for (int i = 0; i < keyValues.length; i = i + 2) {
					map.put(keyValues[i], keyValues[i + 1]);
				}
				Log.d("MCH", "消息MAP数量为:" + map.size());
				String msgCode = map.get(SdkPayServer.PAYRET_KEY_RESULT_STATUS);
				// 解析付费状态和已付费价格
				// 使用其中一种方式请删掉另外一种
				if (msgCode != null && Integer.valueOf(msgCode) == SdkPayServer.PAY_RESULT_SUCCESS) {
					result.setErrorCode("0");
					result.setErrorMsg("支付成功");
					result.setResultCode(0);
					result.setSequence(orderInfo.getSequence());
					callback.result(result);

				} else {
						result.setErrorCode(String.valueOf(SdkPayServer.PAYRET_KEY_FAILED_CODE));
						result.setErrorMsg("付费失败：" + map.get(SdkPayServer.PAYRET_KEY_FAILED_CODE));
						Log.i("MCH","String.valueOf(SdkPayServer.PAYRET_KEY_FAILED_CODE)=" + String.valueOf(SdkPayServer.PAYRET_KEY_FAILED_CODE));
						Log.i("MCH","map.get(SdkPayServer.PAYRET_KEY_FAILED_CODE)=" + map.get(SdkPayServer.PAYRET_KEY_FAILED_CODE));
						result.setResultCode(1);
						result.setSequence(orderInfo.getSequence());
						callback.result(result);
				}
			}
		}
	}

	@Override
	public String getPayPluginName() {
		return "letu";
	}

	@Override
	public int getPayVersionId() {
		return 1;
	}

	@Override
	public void OnActivityResult(int arg0, int arg1, Intent arg2) {
		
	}

}
