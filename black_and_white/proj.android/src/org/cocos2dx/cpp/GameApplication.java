package org.cocos2dx.cpp;


import com.avos.avoscloud.LogUtil.log;
import com.tallbigup.android.AppApplication;
import com.tallbigup.android.cloud.TbuCallback;
import com.tallbigup.android.cloud.TbuCloud;
import com.tallbigup.buffett.OrderResultInfo;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import android.app.ActivityManager;
import android.content.ComponentName;
import android.content.Context;

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
		setLayout();
	}

	public void initAvos() {

//		TbuCloud.initCloud(
//				getApplicationContext(),
//				new TbuCallback() {
//					@Override
//					public void result(boolean success) {
//						Debug.e("TbuCloud init cloud result ="+success);
//						
//					}
//				}, "3w8635fx9uw31mpj4z6y8cz9x15bo31bgsyc0juej4je3ngd",
//				"ukju7nkua4a6ua6qchd2vx4bsueviuz4jk4wq4jenm6rdmry",
//				AppInfo.version);
	}



	private void setLayout() {
		// LayoutUtil.setMoreGameLayoutResId(R.layout.dialog_more_game);
		// LayoutUtil.setMoreGamedialogStyleResId(R.style.dialog_game_style);
		// LayoutUtil.setMoreGameNoDataTipResId(R.id.no_other_game_tip);
		// //LayoutUtil.setMoreGameCancelBtnResId(R.id.more_game_cancle);
		// LayoutUtil.setMoreGameGridViewResId(R.id.more_game_view);
		// LayoutUtil.setMoreGameViewItemLayoutResId(R.layout.more_game_view_item);
		// LayoutUtil.setMoreGameViewItemGameIconResId(R.id.game_icon);
		// LayoutUtil.setMoreGameViewItemGameNameResId(R.id.game_name);
		// LayoutUtil.setPushIconResId(R.drawable.push_logo);
		// LayoutUtil.setNotifyLayoutResId(R.layout.push_notification);
		// LayoutUtil.setNotifyContentResId(R.id.push_content);
		// LayoutUtil.setNotifyIconResId(R.id.push_icon);
		// LayoutUtil.setNotifyTitleResId(R.id.push_title);
		// LayoutUtil.setTipDialogLayoutResId(R.layout.tip_dialog);
		// LayoutUtil.setTipDialogStyleId(R.style.dialog_tip_style);
		// LayoutUtil.setTipDialogTxtResId(R.id.tip_text);
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

	public void fullExitApplication() {
		instance = null;
		System.exit(0);
		android.os.Process.killProcess(android.os.Process.myPid());
	}

	public boolean getHasShowSignInPay() {
		return hasShowSignInPay;
	}

	public void setHasShowSignInPay(boolean hasShowSignInPay) {
		this.hasShowSignInPay = hasShowSignInPay;
	}

	@Override
	public void markPayStart(int payCount, String orderId, String id) {
		// TODO Auto-generated method stub

	}

	@Override
	public void markPayResult(String payState, int payCount, String orderId,
			String id, OrderResultInfo result) {
		// TODO Auto-generated method stub

	}

	@Override
	public void markClickOk(int payCount, String orderId, String id) {
		// TODO Auto-generated method stub

	}
}
