package org.cocos2dx.cpp;


import android.app.Activity;

public class NetWorkService {

	private static GameInfoUtil gameInfo;

	public static boolean isMoreGame = false;
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
//		TbuCloud.updatePlayerInfo(GameApplication.getInstance().getPlayerId(),
//				level + "", goldNum, gameInfo.getData(GameInfoUtil.PAY_MONEY),
//				highScore);
	}

//	public static void getOpenMoreGame() {
//		SwitchUtil.getMoreGameSwitch(context, new SwitchCallback() {
//			@Override
//			public void result(boolean open, int errorCode) {
//				Log.e("QZ", "isShowMoreGame = " + open);
//				NetWorkService.isMoreGame = open;
//				if (open) {
//					TbuCloud.markPersonInfo(context, "get_switch_success", "");
//				} else {
//					if (errorCode == 1) {
//						TbuCloud.markPersonInfo(context, "get_switch_success",
//								"");
//					} else {
//						TbuCloud.markPersonInfo(context, "get_switch_fail", ""
//								+ errorCode);
//					}
//				}
//				JniMoreGameCallbackHelper.switchCallback(open);
//			}
//		});
//	}

	public static void showMoreGame() {
		
	}
	

	public static void quit() {
		
	}

}
