package org.cocos2dx.cpp;

import com.tallbigup.android.cloud.TbuCloud;
import com.tbu.getswitch.SwitchCallback;
import com.tbu.getswitch.SwitchUtil;
import android.app.Activity;
import android.util.Log;

public class NetWorkService {

	private static GameInfoUtil gameInfo;

	static boolean isMoreGame = false;
	static Activity context;

	public static void init(Activity activity) {
		context = activity;
		gameInfo = GameInfoUtil.getInstance();
		gameInfo.init(activity);
	}

	public void markUserType(int type) {
		gameInfo.setData(GameInfoUtil.USER_TYPE, type);
	}

	public static void updatePlayerInfo(int level, int goldNum, int highScore) {
		TbuCloud.updatePlayerInfo(GameApplication.getInstance().getPlayerId(),
				level + "", goldNum, gameInfo.getData(GameInfoUtil.PAY_MONEY),
				highScore);
	}

	public static void isShowMoreGame() {
		SwitchUtil.getMoreGameSwitch(context, new SwitchCallback() {
			@Override
			public void result(boolean arg0, int arg1) {
				Log.e("QZ", "isShowMoreGame = " + arg0);
				NetWorkService.isMoreGame = arg0;
				if (arg0) {
					TbuCloud.markPersonInfo(context, "get_switch_success", "");
				} else {
					if (arg1 == 1) {
						TbuCloud.markPersonInfo(context, "get_switch_success",
								"");
					} else {
						TbuCloud.markPersonInfo(context, "get_switch_fail", ""
								+ arg1);
					}
				}
			JniPayCallbackHelper.showMoreGameNative(isMoreGame);
			}
		});
	}

	public static void showMoreGame() {
		if (NetWorkService.isMoreGame) {
			TbuCloud.showMoreGame(context);
		}
	}

	public static void quit() {
		context.runOnUiThread(new Runnable() {
			public void run() {
				context.showDialog(AppActivity.SHOW_QUIT_GAME_DIALOG);
			}
		});

	}
}
