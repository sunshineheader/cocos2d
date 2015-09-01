package org.cocos2dx.cpp;


import com.lyhtgh.pay.application.PayApplication;
import com.poxiao.pay.GamePay;
import com.tallbigup.android.cloud.CreatePlayerCallback;
import com.tallbigup.android.cloud.LayoutUtil;
import com.tallbigup.android.cloud.TbuCallback;
import com.tallbigup.android.cloud.TbuCloud;
import com.tallbigup.buffett.plugin.configuration.Configuration;
import com.tallbigup.buffett.plugin.deviceinfo.DeviceInfo;
import com.poxiao.findthings.R;

import android.app.ActivityManager;
import android.app.Application;
import android.content.ComponentName;
import android.content.Context;
import android.util.Log;

public class GameApplication extends PayApplication {

	public static final String TAG = GameApplication.class.getCanonicalName();

	private GameInfoUtil gameInfo;
	private String playerId;

	private static GameApplication instance;

	@Override
	public void onCreate() {
		super.onCreate();
		instance = this;
		gameInfo = GameInfoUtil.getInstance();
		gameInfo.init(this);
		setLayout();
		init();
	}

	public void init() {
		GamePay.getInstance().init(getApplicationContext(),
				GamePay.MM_POJIE_PAY_TYPE, "2", GamePay.SKY_PAY_TYPE,
				7010606, 9966, "’“ƒ„√√2015");
		TbuCloud.initCloud(
				getApplicationContext(),
				new TbuCallback() {

					@Override
					public void result(boolean success) {
						if (success) {
							if (gameInfo
									.getData(GameInfoUtil.CREATE_PLAYER_SUCCESS) == 1) {
								playerId = gameInfo.getPlayerId();
								return;
							}
							TbuCloud.createPlayer(gameInfo.getNickName(),
									DeviceInfo.imsi, DeviceInfo.version, "1",
									0, Configuration.enterId,
									gameInfo.getData(GameInfoUtil.PAY_MONEY),
									0, new CreatePlayerCallback() {

										@Override
										public void result(boolean success,
												String playerId) {
											Log.i(TAG, "success=" + success);
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
				}, "c1i2cqhe26ir7ypmk9ne26577fxrkzyn73v6cpjb7hnxneby",
				"8jvadfjedohure6nc6fwaz2ffdy7ntsn3boy5wkhr70uc3fu",
				DeviceInfo.version, AppActivity.class);
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
		// LayoutUtil.setTipDialogStyleId(R.style.dialog_tip_style);
		LayoutUtil.setTipDialogTxtResId(R.id.tip_text);
	}

	public static GameApplication getInstance() {
		return instance;
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
	public void fullExitApplication(){
		System.exit(0);
		android.os.Process.killProcess(android.os.Process.myPid());
	}
}
