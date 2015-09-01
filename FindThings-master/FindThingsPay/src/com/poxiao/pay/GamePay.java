package com.poxiao.pay;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.ViewGroup.LayoutParams;
import android.view.Window;
import android.view.WindowManager;

import com.poxiao.pay.plugin.letu.LetuPayImpl;
import com.poxiao.pay.plugin.mm.SmsPayImpl;
import com.poxiao.pay.plugin.sky.SkyPayImpl;
import com.poxiao.pay.widget.MarkClickOkInterface;
import com.poxiao.pay.widget.PayDialog;
import com.poxiao.pay.widget.PayDialog.DIALOGTYPE;
import com.poxiao.smspay.device.PhoneDeviceInfo;
import com.poxiao.smspay.http.PayHttpClient;
import com.poxiao.smspay.http.SwitchCallback;
import com.tallbigup.buffett.Buffett;
import com.tallbigup.buffett.OrderResultInfo;
import com.tallbigup.buffett.PayCallback;

public class GamePay {

	public static final int SKY_PAY_TYPE = 1;
	public static final int MM_POJIE_PAY_TYPE = 2;
	public static final int MOBILE_MM_PAY_TYPE = 3;
	public static final int UUCUN_PAY_TYPE = 4;
	public static final int XYH_PAY_TYPE = 5;
	public static final int LEYIFU_PAY_TYPE = 6;
	public static final int MILI_PAY_TYPE = 7;

	public static boolean OPEN_SECOND_CONFIRM_PAY = false;
	public static boolean BlACK_LIST = false;
	public static boolean WHITE_LIST = false;

	private static GamePay instance;

	private static boolean successInit = false;
	public static String open;
	private long appId;
	private int gameId;
	private String appName;

	private Buffett buffett;
	private Context context;

	private String letuPayOrderInfo;

	private GamePay() {

	}

	public static GamePay getInstance() {
		if (instance == null) {
			instance = new GamePay();
		}
		return instance;
	}

	public void init(final Context context, final int switchPayType,
			final String open, final int otherPayType, final int appId,
			final int gameId, final String appName) {
		// DeviceInfo
		Buffett.initDeviceInfo(context);
		PhoneDeviceInfo.getIntance(context).setAppId(appId);
		PhoneDeviceInfo.getIntance(context).setGameId(gameId);

		GamePay.open = open;// 默认值是2，3（即SKY和LETU）
		this.appId = appId;
		this.gameId = gameId;
		this.appName = appName;
		this.context = context;

		if (switchPayType == GamePay.MM_POJIE_PAY_TYPE) {
			PayHttpClient.getSmsPaySwitch(context, new SwitchCallback() {

				public void result(String open) {
					GamePay.open = open;
					Log.e("MCH", "open=" + open);
					if (open.length() == 0 || open.equals("0")) {
						Log.e("DLJ",
								"OPEN_SECOND_CONFIRM_PAY>>>>>>>>>>>SmsPayImpl");
						Buffett.init(new SmsPayImpl());
						buffett = Buffett.getInstance();
						buffett.initPayApplication(context);
						successInit = true;
					} else if (open.equals("2")) {
						Log.e("DLJ",
								"OPEN_SECOND_CONFIRM_PAY>>>>>>>>>>>SkyPayImpl");
						// 此处使用的是sky支付，若是其他支付可进行相应修改
						Buffett.init(new SkyPayImpl());
						buffett = Buffett.getInstance();
						buffett.initPayApplication(context);
						successInit = true;
					} else if (open.equals("3")) {
						Log.e("DLJ",
								"OPEN_SECOND_CONFIRM_PAY>>>>>>>>>>>LetuPayImpl");
						Buffett.init(new LetuPayImpl());
						buffett = Buffett.getInstance();
						buffett.initPayApplication(context);
						successInit = true;
					} else {
						Log.e("DLJ",
								"OPEN_SECOND_CONFIRM_PAY>>>>>>>>>>>SkyPayImpl");
						// 此处使用的是sky支付，若是其他支付可进行相应修改
						Buffett.init(new SkyPayImpl());
						buffett = Buffett.getInstance();
						buffett.initPayApplication(context);
						successInit = true;
					}
				}

			});
		} else {
			successInit = true;
		}
	}

	public void changeWifiInit(String open) {
		GamePay.open = open;
		if (open.length() == 0 || open.equals("0")) {
			Log.e("DLJ", "OPEN_SECOND_CONFIRM_PAY>>>>>>>>>>>SmsPayImpl");
			Buffett.init(new SmsPayImpl());
			buffett = Buffett.getInstance();
			buffett.initPayApplication(context);
			successInit = true;
		} else if (open.equals("2")) {
			Log.e("DLJ", "OPEN_SECOND_CONFIRM_PAY>>>>>>>>>>>SkyPayImpl");
			// 此处使用的是sky支付，若是其他支付可进行相应修改
			Buffett.init(new SkyPayImpl());
			buffett = Buffett.getInstance();
			buffett.initPayApplication(context);
			successInit = true;
		} else if (open.equals("3")) {
			Log.e("DLJ", "OPEN_SECOND_CONFIRM_PAY>>>>>>>>>>>LetuPayImpl");
			Buffett.init(new LetuPayImpl());
			buffett = Buffett.getInstance();
			buffett.initPayApplication(context);
			successInit = true;
		} else {
			Log.e("DLJ", "OPEN_SECOND_CONFIRM_PAY>>>>>>>>>>>SkyPayImpl");
			// 此处使用的是sky支付，若是其他支付可进行相应修改
			Buffett.init(new SkyPayImpl());
			buffett = Buffett.getInstance();
			buffett.initPayApplication(context);
			successInit = true;
		}
	}

	public void onCreateInit(Activity activity, int pluginType) {
		// 此处使用的是sky支付，若是其他支付可进行相应修改
		if (successInit) {
			return;
		}
		if (pluginType == GamePay.SKY_PAY_TYPE) {
			Buffett.init(new SkyPayImpl());
			buffett = Buffett.getInstance();
			buffett.initPayApplication(activity.getApplicationContext());
			buffett.OnActivityCreate(activity);
		}
	}

	private boolean getPayResult = false;

	public void pay(final Activity activity, final int payPoint,
			final String orderId, final GamePayCallback callback,
			final MarkClickOkInterface clickOk) {
		if (!isSuccessInit()) {
			return;
		}
		PhoneDeviceInfo phoneDeviceInfo = PhoneDeviceInfo.getIntance(activity
				.getApplication());
		phoneDeviceInfo.setPayPoint(payPoint);
		if (PAY.getMoney(payPoint) > 0) {
			if (open.length() == 0 || open.equals("0")) {
				Log.e("MCH", "MM支付");
				activity.runOnUiThread(new Runnable() {

					@Override
					public void run() {
						final PayDialog d = new PayDialog(activity, buffett,
								payPoint, "123456", orderId,
								DIALOGTYPE.DIALOG_TYPE_MM, clickOk,
								new PayCallback() {

									@Override
									public void result(OrderResultInfo result) {
										if (result.getResultCode() != 0) {
											Log.e("MCH",
													"result.getErrorMsg()+"
															+ result.getErrorMsg());
											if (result.getErrorMsg().contains(
													"无此通道")) {
												activity.runOnUiThread(new Runnable() {

													@Override
													public void run() {
														// 此处使用的是sky支付，若是其他支付可进行相应修改
														setOpen(open);
														buffett.pay(
																activity,
																PayInfo.getInstance()
																		.getOrderInfo(
																				payPoint,
																				"123456",
																				orderId),
																new PayCallback() {

																	@Override
																	public void result(
																			OrderResultInfo result) {
																		callback.result(result);
																	}
																});
													}
												});
											} else {
												callback.result(result);
											}
										} else {
											callback.result(result);
										}
									}
								});
						d.requestWindowFeature(Window.FEATURE_NO_TITLE);
						d.getWindow().setFlags(
								WindowManager.LayoutParams.FLAG_FULLSCREEN,
								WindowManager.LayoutParams.FLAG_FULLSCREEN);
						d.show();
						d.getWindow().setLayout(LayoutParams.MATCH_PARENT,
								LayoutParams.MATCH_PARENT);
					}
				});
			} else if (open.equals("3")) {
				// letu pay
				Log.e("MCH", "letu支付");
				activity.runOnUiThread(new Runnable() {

					@Override
					public void run() {
						final PayDialog d = new PayDialog(activity, buffett,
								payPoint, "123456", orderId,
								DIALOGTYPE.DIALOG_TYPE_LT, clickOk,
								new PayCallback() {

									@Override
									public void result(OrderResultInfo result) {
										getPayResult = true;
										Log.e("MCH",
												"result="
														+ result.getErrorMsg());
										callback.result(result);
									}
								});
						d.requestWindowFeature(Window.FEATURE_NO_TITLE);
						d.getWindow().setFlags(
								WindowManager.LayoutParams.FLAG_FULLSCREEN,
								WindowManager.LayoutParams.FLAG_FULLSCREEN);
						d.show();
						d.getWindow().setLayout(LayoutParams.MATCH_PARENT,
								LayoutParams.MATCH_PARENT);
					}
				});
			} else {
				Log.e("MCH", "sky支付支付");
				Log.e("MCH", ">>>>>>>>>>>>>>>>>>>");
				getPayResult = false;
				activity.runOnUiThread(new Runnable() {

					@Override
					public void run() {
						Log.i("MCH", "start sky pay ... ");
						buffett.pay(activity, PayInfo.getInstance()
								.getOrderInfo(payPoint, "123456", orderId),
								new PayCallback() {

									@Override
									public void result(OrderResultInfo result) {
										Log.i("MCH",
												"-----sky pay get pay result,result.getErrorMsg()="
														+ result.getErrorMsg());
										if (!getPayResult) {
											Log.i("MCH",
													"-------------------------");
											getPayResult = true;
											callback.result(result);
										}
									}
								});
					}
				});

			}
		} else {
			activity.runOnUiThread(new Runnable() {

				@Override
				public void run() {
					final PayDialog d = new PayDialog(activity, buffett,
							payPoint, "123456", orderId,
							DIALOGTYPE.DIALOG_TYPE_MM, clickOk,
							new PayCallback() {

								@Override
								public void result(OrderResultInfo result) {
									callback.result(result);
								}
							});
					d.requestWindowFeature(Window.FEATURE_NO_TITLE);
					d.getWindow().setFlags(
							WindowManager.LayoutParams.FLAG_FULLSCREEN,
							WindowManager.LayoutParams.FLAG_FULLSCREEN);
					d.show();
					d.getWindow().setLayout(LayoutParams.MATCH_PARENT,
							LayoutParams.MATCH_PARENT);
				}
			});
		}
	}

	public void onActivityDestroy(Activity activity) {
		buffett.OnActivityDestory(activity);
	}

	public void setOpen(String open) {
		if (null == open || open.equals("0")) {
			Log.e("DLJ", "OPEN_SECOND_CONFIRM_PAY>>>>>>>>>>>SkyPayImpl");
			// 此处使用的是sky支付，若是其他支付可进行相应修改
			Buffett.init(new SkyPayImpl());
			buffett = Buffett.getInstance();
			buffett.initPayApplication(context);
		} else {
			Log.e("DLJ", "OPEN_SECOND_CONFIRM_PAY>>>>>>>>>>>SmsPayImpl");
			Buffett.init(new SmsPayImpl());
			buffett = Buffett.getInstance();
			buffett.initPayApplication(context);
		}
	}

	public static boolean isSuccessInit() {
		return successInit;
	}

	public long getAppId() {
		return appId;
	}

	public int getGameId() {
		return gameId;
	}

	public String getAppName() {
		return appName;
	}

	public String getLetuPayOrderInfo() {
		return letuPayOrderInfo;
	}

	public void setLetuPayOrderInfo(String letuPayOrderInfo) {
		this.letuPayOrderInfo = letuPayOrderInfo;
	}
}
