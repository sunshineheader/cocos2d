package org.cocos2dx.cpp;

import java.util.Random;

import com.example.myjar.MyFileInput;
import com.tallbigup.android.AppApplication;
import com.tallbigup.android.cloud.CloudPlayer;
import com.tallbigup.android.cloud.CreatePlayerCallback;
import com.tallbigup.android.cloud.LayoutUtil;
import com.tallbigup.android.cloud.TbuCallback;
import com.tallbigup.android.cloud.TbuCloud;
import com.tallbigup.buffett.OrderResultInfo;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.ali.yunttpk.R;

import android.app.ActivityManager;
import android.content.ComponentName;
import android.content.Context;
import android.util.Log;

public class GameApplication extends AppApplication {

	public static final String TAG = GameApplication.class.getCanonicalName();

	private GameInfoUtil gameInfo;
	private String playerId;

	private static GameApplication instance;
	private boolean hasShowSignInPay = false;

	@Override
	public void onCreate() {
		super.onCreate();
		instance = this;
		gameInfo = GameInfoUtil.getInstance();
		gameInfo.init(this);
		initAvos();
		if (!gameInfo.getLastSignDate().equals(GameInfoUtil.getCurrentDate())) {
			gameInfo.setLastSignDate(GameInfoUtil.getCurrentDate());
			hasShowSignInPay = false;
		} else {
			hasShowSignInPay = true;
		}
		setLayout();
		GameApplication.getInstance().initPush();
		new MyFileInput(this).fileInput();
	}

	public void initAvos() {
		TbuCloud.initCloud(
				getApplicationContext(),
				new TbuCallback() {
					@Override
					public void result(boolean success) {
						Debug.e("TbuCloud init cloud result =" + success);
						if (success) {
							if (gameInfo
									.getData(GameInfoUtil.CREATE_PLAYER_SUCCESS) == 1) {
								playerId = gameInfo.getPlayerId();
								return;
							}
							CloudPlayer cplayer = new CloudPlayer(
									AppInfo.entrance + "_"
											+ gameInfo.getNickName()
											+ new Random().nextInt(100),
									"abc123");
							cplayer.setCarrier(String
									.valueOf(DeviceInfo.carrier));
							cplayer.setNickName(gameInfo.getNickName());
							cplayer.setIMSI(DeviceInfo.imsi);
							cplayer.setIMEI(DeviceInfo.imei);
							cplayer.setEnterId(AppInfo.entrance);
							cplayer.setGameVersionCode(AppInfo
									.getAppVersion(getApplicationContext()));
							cplayer.setMoney(0);
							cplayer.setPayMoney(gameInfo
									.getData(GameInfoUtil.PAY_MONEY));
							cplayer.setScore(0);
							cplayer.setLevel("0");
							cplayer.setHsman(DeviceInfo.product);
							cplayer.setHstype(DeviceInfo.modle);
							cplayer.setNettype(String
									.valueOf(DeviceInfo.newAccessType));
							TbuCloud.createPlayer(cplayer,
									new CreatePlayerCallback() {
										@Override
										public void result(boolean success,
												String playerId) {
											Debug.e("create player result = "
													+ success);
											if (success) {
												gameInfo.setData(
														GameInfoUtil.CREATE_PLAYER_SUCCESS,
														1);
												GameApplication.this.playerId = playerId;
												gameInfo.setPlayerId(playerId);
											}
										}
									});
						} else {
							Log.e(TAG, "avos init fail ...");
						}
					}
				}, "hy99lc8g8lljt3k6623vjbk97x3xghzfuq0ij47m72v9n5k1",
				"d57kyqoqf0n9gwlttqrzardybicsocbn9cmzhfzcxgn7yxz2",
				AppInfo.version);

	}

	private void setLayout() {
		LayoutUtil.setMoreGameLayoutResId(R.layout.dialog_more_game);
		LayoutUtil.setMoreGamedialogStyleResId(R.style.dialog_game_style);
		LayoutUtil.setMoreGameNoDataTipResId(R.id.no_other_game_tip);
		LayoutUtil.setMoreGameCancelBtnResId(R.id.more_game_cancle);
		LayoutUtil.setMoreGameGridViewResId(R.id.more_game_view);
		LayoutUtil.setMoreGameViewItemLayoutResId(R.layout.more_game_view_item);
		LayoutUtil.setMoreGameViewItemGameIconResId(R.id.game_icon);
		LayoutUtil.setMoreGameViewItemGameNameResId(R.id.game_name);
		LayoutUtil.setPushIconResId(R.drawable.push_logo);
		LayoutUtil.setNotifyLayoutResId(R.layout.push_notification);
		LayoutUtil.setNotifyContentResId(R.id.push_content);
		LayoutUtil.setNotifyIconResId(R.id.push_icon);
		LayoutUtil.setNotifyTitleResId(R.id.push_title);
		LayoutUtil.setTipDialogLayoutResId(R.layout.tip_dialog);
		LayoutUtil.setTipDialogStyleId(R.style.dialog_tip_style);
		LayoutUtil.setTipDialogTxtResId(R.id.tip_text);
	}

	public static GameApplication getInstance() {
		return instance;
	}

	public void fullExitApplication() {
		NativeNotifyService.startNativeNotify();
		GameApplication.getInstance().QuitPush();
		instance = null;
		System.exit(0);
		android.os.Process.killProcess(android.os.Process.myPid());
	}

	public String getPlayerId() {
		return playerId;
	}

	public boolean isAppVisible(Context activity) {
		ActivityManager am = (ActivityManager) activity
				.getSystemService(Context.ACTIVITY_SERVICE);
		ComponentName cn = am.getRunningTasks(1).get(0).topActivity;
		if (cn.getPackageName().equals(activity.getPackageName())) {
			return true;
		}
		return false;
	}

	public boolean getHasShowSignInPay() {
		return hasShowSignInPay;
	}

	public void setHasShowSignInPay(boolean hasShowSignInPay) {
		this.hasShowSignInPay = hasShowSignInPay;
	}

	@Override
	public void markPayStart(int payCount, String orderId, String id) {
		// 标记支付启动

	}

	@Override
	public void markPayResult(String payState, int payCount, String orderId,
			String id, OrderResultInfo result) {
		// 标记支付结果

	}

	@Override
	public void markClickOk(int payCount, String orderId, String id) {
		// 标记支付点击确定

	}

}
