package org.cocos2dx.cpp;

import com.tallbigup.android.cloud.TbuCloud;

import android.app.Activity;


public class NetWorkService {
	
	private static GameInfoUtil gameInfo;
	
	public static void init(Activity activity){
		gameInfo = GameInfoUtil.getInstance();
		gameInfo.init(activity);
	}
	
	public void markUserType(int type){
		gameInfo.setData(GameInfoUtil.USER_TYPE, type);
	}
	
	public static void updatePlayerInfo(int level,int goldNum,int highScore){
		TbuCloud.updatePlayerInfo(GameApplication.getInstance().getPlayerId(), level+"", goldNum, gameInfo.getData(GameInfoUtil.PAY_MONEY), highScore);
	}
}
