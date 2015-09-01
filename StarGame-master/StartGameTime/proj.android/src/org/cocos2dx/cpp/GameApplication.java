package org.cocos2dx.cpp;

import com.poxiao.pay.star.GamePay;
import com.tallbigup.android.cloud.CreatePlayerCallback;
import com.tallbigup.android.cloud.LayoutUtil;
import com.tallbigup.android.cloud.TbuCallback;
import com.tallbigup.android.cloud.TbuCloud;
import com.tallbigup.buffett.plugin.configuration.Configuration;
import com.tallbigup.buffett.plugin.deviceinfo.DeviceInfo;
import com.tallbigup.star.R;

import android.app.ActivityManager;
import android.app.Application;
import android.content.ComponentName;
import android.content.Context;
import android.util.Log;

public class GameApplication extends Application{
	
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
	
	public void init(){		
		GamePay.getInstance().init(getApplicationContext(), GamePay.MM_POJIE_PAY_TYPE, false, GamePay.SKY_PAY_TYPE, 7005194, 9970, "羊年消星星");
		
		TbuCloud.initCloud(getApplicationContext(), new TbuCallback() {
			
			@Override
			public void result(boolean success) {
				if(success){
					if(gameInfo.getData(GameInfoUtil.CREATE_PLAYER_SUCCESS) == 1){
						Log.i(TAG,"已成功创建用户");
						playerId = gameInfo.getPlayerId();
						return;
					}
					TbuCloud.createPlayer(gameInfo.getNickName(), DeviceInfo.imsi, DeviceInfo.version,
							"1", 0,
							 Configuration.enterId, gameInfo.getData(GameInfoUtil.PAY_MONEY),
							 0, new CreatePlayerCallback() {
						
						@Override
						public void result(boolean success, String playerId) {
							Log.i(TAG,"success="+success);
							if(success){
								gameInfo.setData(GameInfoUtil.CREATE_PLAYER_SUCCESS, 1);
								GameApplication.this.playerId = playerId;
								gameInfo.setPlayerId(playerId);
							}
						}
					});
				}else{
					Log.e(TAG, "avos init fail ...");
				}
			}
		}, "fi68r9jrdpvgboosoduw367409zze6wx96at1la0p6tawvuq", "rvx72drfn7o3um1meevpzgss1k2i8jwyejigr7e7uxgtl0i4", DeviceInfo.version, AppActivity.class);
	}
	
	private void setLayout() {
		LayoutUtil.setMoreGamedialogStyleResId(R.style.dialog_game_style);
		LayoutUtil.setPushIconResId(R.drawable.push_logo);
		LayoutUtil.setNotifyLayoutResId(R.layout.push_notification);
		LayoutUtil.setNotifyContentResId(R.id.push_content);
		LayoutUtil.setNotifyIconResId(R.id.push_icon);
		LayoutUtil.setNotifyTitleResId(R.id.push_title);
		LayoutUtil.setTipDialogStyleId(R.style.dialog_tip_style);
	}
	
	public static GameApplication getInstance(){
		return instance;
	}
	
	public String getPlayerId(){
		return playerId;
	}
	
	public boolean isAppVisible(Context activity) {
        ActivityManager am = (ActivityManager) activity.getSystemService(Context.ACTIVITY_SERVICE);
        ComponentName cn = am.getRunningTasks(1).get(0).topActivity;
        if (cn.getPackageName().equals(activity.getPackageName())) {
            return true;
        }
        return false;
	}
}
