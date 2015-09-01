package org.cocos2dx.cpp;

import com.tallbigup.android.AppApplication;
import com.tallbigup.android.cloud.TbuCloud;
import com.tallbigup.android.extend.quitgame.ExitGameInterface;
import com.tbu.android.moreapp.MoreGameManager;
import com.tbu.android.moreapp.domain.MoreAppCallback;
import com.tbu.getswitch.SwitchCallback;
import com.tbu.getswitch.SwitchUtil;

import android.app.Activity;
import android.util.Log;

public class NetWorkService {

	private static GameInfoUtil gameInfo;
	private static Activity activity;
	public static boolean openMoreGame = false;

	public static void init(final Activity activity) {
		NetWorkService.activity = activity;
		gameInfo = GameInfoUtil.getInstance();
		gameInfo.init(activity);
		MoreGameManager.init(activity, new MoreAppCallback() {
			@Override
			public void result(boolean changed) {
				if (MoreGameManager.allowShowMoreApps(activity)) {
					openMoreGame = true;
				} else {
					openMoreGame = false;
				}
			}
		});
	}

	public void markUserType(int type) {
		gameInfo.setData(GameInfoUtil.USER_TYPE, type);
	}

	public static void updatePlayerInfo(int level, int goldNum, int highScore) {
		TbuCloud.updatePlayerInfo(GameApplication.getInstance().getPlayerId(),
				level + "", goldNum, gameInfo.getData(GameInfoUtil.PAY_MONEY),
				highScore);
	}

	public static void quit() {
	}

	public static void showMoreGame() {
		AppApplication.showMoreGame(activity);
	}

	public static void showQuitDialog() {
		AppApplication.quitGame(activity, new ExitGameInterface() {

			@Override
			public void quitGame() {
				GameApplication.getInstance().fullExitApplication();
			}
		});
		GameApplication.getInstance().doInstallOnQuit();
	}

	public static void getOpenMoreGame() {
		// JniPayCallbackHelper.showMoreGameNative(openMoreGame);
	}
}
