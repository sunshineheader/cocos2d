package com.poxiao.pay.plugin.sky;

import java.util.HashMap;
import java.util.Map;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.poxiao.pay.GamePay;
import com.skymobi.pay.newsdk.EpsApplication;
import com.skymobi.pay.newsdk.EpsEntry;
import com.skymobi.pay.newsdk.util.SkyPaySignerInfo;
import com.tallbigup.buffett.OrderInfo;
import com.tallbigup.buffett.OrderResultInfo;
import com.tallbigup.buffett.PayCallback;
import com.tallbigup.buffett.PayInterface;
import com.tallbigup.buffett.plugin.configuration.Configuration;
import com.tallbigup.buffett.plugin.deviceinfo.DeviceInfo;

public class SkyPayImpl implements PayInterface {

	private static final String tag = "[StartSmsPay]";

	// 订单参数
	private static final String ORDER_INFO_PAY_METHOD = "payMethod";
	private static final String ORDER_INFO_SYSTEM_ID = "systemId";
	private static final String ORDER_INFO_CHANNEL_ID = "channelId";
	private static final String ORDER_INFO_PAY_POINT_NUM = "payPointNum";
	private static final String ORDER_INFO_ORDER_DESC = "orderDesc";
	private static final String ORDER_INFO_GAME_TYPE = "gameType";

	private static final String STRING_MSG_CODE = "msg_code";
	private static final String STRING_ERROR_CODE = "error_code";
	private static final String STRING_PAY_STATUS = "pay_status";
	private static final String ORDER_INFO_PRICENOTIFYADDRESS = "priceNotifyAddress";
	// 商户秘钥
	private static final String SKYMOBI_MERCHANT_PASSWORD = "hyu^&5(&122";
	// 是否使用定制界面
	private static final boolean SKY_USE_APPUI = true;
	// 请CP替换成在斯凯申请的商户密钥
	private String MerchantPasswd = SKYMOBI_MERCHANT_PASSWORD;

	private EpsApplication payApplicaton = new EpsApplication();
	private EpsEntry mEpsEntry = null;
	private OrderResultInfo result;
	private OrderInfo orderInfo;
	private PayCallback callback;

	@Override
	public void OnActivityCreate(Activity arg0) {

	}

	@Override
	public void OnActivityDestory(Activity arg0) {

	}

	@Override
	public void OnActivityPause(Activity arg0) {

	}

	@Override
	public void OnActivityResult(int arg0, int arg1, Intent arg2) {

	}

	@Override
	public void OnActivityResume(Activity arg0) {

	}

	@Override
	public String getPayPluginName() {
		return "zimon";
	}

	@Override
	public int getPayVersionId() {
		return 2;
	}

	@Override
	public void initPayApplication(Context context) {
		payApplicaton.onStart(context);
	}

	@Override
	public void pay(Activity activity, OrderInfo order, PayCallback callback) {
		Log.i(tag, "startPay start");
		result = new OrderResultInfo();
		this.callback = callback;
		this.orderInfo = order;
		// 1.获取付费实例并初始化
		mEpsEntry = EpsEntry.getInstance();
		// 2.付费方式 sms 短代
		String paymethod = "sms";
		// 3.订单号 CP需保存，订单有疑问需通过orderId进行检查
		String merchantId = "10642";
		String merchantPasswd = MerchantPasswd;
		String orderId = order.getOrderId();
		String appId = String.valueOf(GamePay.getInstance().getAppId());
		String appName = GamePay.getInstance().getAppName(); // 游戏名称
		String appVersion = DeviceInfo.version; // 游戏版本号
		// 4.系统号 在斯凯申请systemId
		String systemId = "300024";
		String channelId = Configuration.enterId;
		/*
		 * 5.价格 短信付费定价（日限75元，月限150元，单次请求上限20元） 第三方付费定价
		 * 目前第三方不支持指定价格，传进来的price会被忽略，实际付费金额跟用户选择充值卡面额有关，以服务端通知为准。
		 */
		String price = String.valueOf(order.getPrice());

		// 6.计费类型： 0=注册 1=道具 2=积分 3=充值，50=网游小额支付（如果不填，默认是道具）
		String payType = "1";

		/*
		 * 注解A 如果配置服务端，由取消下面注解 notifyAddress设置CP的回调地址 reserved1 reserved2
		 * reserved3 扩展字段，会随地址一起同步到CP的服务端 以http get的方式同步给CP端，具体回调参数看文档
		 */

		String notifyAddress = "http://www.notify.com";
		String reserved1 = "reserved1";
		String reserved2 = "reserved2";
		String reserved3 = "reserved3|=2/3";

		// 10.自动生成订单签名
		SkyPaySignerInfo skyPaySignerInfo = new SkyPaySignerInfo();

		skyPaySignerInfo.setMerchantPasswd(merchantPasswd);
		skyPaySignerInfo.setMerchantId(merchantId);
		skyPaySignerInfo.setAppId(appId);
		skyPaySignerInfo.setAppName(appName);
		skyPaySignerInfo.setAppVersion(appVersion);
		skyPaySignerInfo.setPayType(payType);
		skyPaySignerInfo.setPrice(price);
		skyPaySignerInfo.setOrderId(orderId);

		// 注解B 如果配置了服务端，则取消如下四条注解

		skyPaySignerInfo.setNotifyAddress(notifyAddress);
		skyPaySignerInfo.setReserved1(reserved1, false);
		skyPaySignerInfo.setReserved2(reserved2, false);
		skyPaySignerInfo.setReserved3(reserved3, true);

		String payPointNum = String.valueOf(order.getPayPointNum());
		String gameType = "2"; // 0-单机、1-联网、2-弱联网
		String signOrderInfo = skyPaySignerInfo.getOrderString();

		String orderInfo = ORDER_INFO_PAY_METHOD + "=" + paymethod + "&"
				+ ORDER_INFO_SYSTEM_ID + "=" + systemId + "&"
				+ ORDER_INFO_CHANNEL_ID + "=" + channelId + "&"
				+ ORDER_INFO_PAY_POINT_NUM + "=" + payPointNum + "&"
				+ ORDER_INFO_GAME_TYPE + "=" + gameType + "&"
				// 注解C 如果配置了服务端，则取消该条注解
				+ ORDER_INFO_PRICENOTIFYADDRESS + "=" + notifyAddress + "&"
				+ "useAppUI=" + SKY_USE_APPUI + "&" + signOrderInfo;

		String orderDesc = order.getOrderDesc();

		orderInfo += "&" + ORDER_INFO_ORDER_DESC + "=" + orderDesc;

		// 开始计费
		int payRet = mEpsEntry.startPay(activity, orderInfo, mPayHandler);
		if (EpsEntry.PAY_RETURN_SUCCESS == payRet) {
			// 初始化成功
		} else {
			// 未初始化 \ 传入参数有误 \ 服务正处于付费状态
			result.setErrorCode(String.valueOf(payRet));
			result.setErrorMsg("服务正处于付费状态或传入参数为空");
			result.setResultCode(1);
			result.setSequence(order.getSequence());
			callback.result(result);
		}

	}

	private Handler mPayHandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			super.handleMessage(msg);

			if (msg.what == EpsEntry.MSG_WHAT_TO_APP) {
				String retInfo = (String) msg.obj;
				Map<String, String> map = new HashMap<String, String>();
				String[] keyValues = retInfo.split("&|=");
				for (int i = 0; i < keyValues.length; i = i + 2) {
					map.put(keyValues[i], keyValues[i + 1]);
				}

				int msgCode = Integer.parseInt(map.get(STRING_MSG_CODE));
				// 解析付费状态和已付费价格
				// 使用其中一种方式请删掉另外一种
				if (msgCode == 100) {

					// 短信付费返回
					if (map.get(STRING_PAY_STATUS) != null) {
						int payStatus = Integer.parseInt(map
								.get(STRING_PAY_STATUS));
						int errcrCode = 0;
						if (map.get(STRING_ERROR_CODE) != null) {
							errcrCode = Integer.parseInt(map
									.get(STRING_ERROR_CODE));
						}

						switch (payStatus) {
						case 102:
							// 付费成功
							result.setErrorCode("0");
							result.setErrorMsg("支付成功");
							result.setResultCode(0);
							result.setSequence(orderInfo.getSequence());
							callback.result(result);
						case 101:
							// 付费失败
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
					int errcrCode = Integer
							.parseInt(map.get(STRING_ERROR_CODE));
					if (errcrCode == 503 || errcrCode == 805) {
						Log.i("MCH", "-----------------取消支付");
						result.setErrorCode(String.valueOf(errcrCode));
						result.setErrorMsg("取消支付");
						result.setResultCode(-3);
						result.setSequence(orderInfo.getSequence());
						callback.result(result);
					} else {
						result.setErrorCode(String.valueOf(errcrCode));
						result.setErrorMsg("付费失败：" + errcrCode);
						result.setResultCode(1);
						result.setSequence(orderInfo.getSequence());
						callback.result(result);
					}
				}
			}
		}
	};

}
