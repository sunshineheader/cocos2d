package org.cocos2dx.cpp;

import com.tallbigup.buffett.plugin.deviceinfo.DeviceInfo;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class GameInfoUtil{
	
	public static final String USER_TYPE = "userType";
	public static final String PLAYER_ID = "playerId";
	public static final String PAY_COUNT = "payCount";
	public static final String PAY_MONEY = "payMoney";
	public static final String NICK_NAME = "nickName";
	public static final String CREATE_PLAYER_SUCCESS = "creatPlayerSuccess";
	public static final String NAME = "jbxxl_game_info";
	
	private static GameInfoUtil instance;
	private static SharedPreferences sp;
	
	private boolean successInit = false;
	
	private GameInfoUtil(){}
	
	public static GameInfoUtil getInstance(){
		if(instance == null){
			instance = new GameInfoUtil();
		}
		return instance;
	}
	
	public boolean init(Context context){
		if(!successInit){
			sp = context.getSharedPreferences(NAME, Context.MODE_PRIVATE);
			successInit = true;
		}
		return successInit;
	}
	
	public int getData(String key){
		return sp.getInt(key, 0);
	}
	
	public boolean setData(String key, int value){
		Editor editor = sp.edit();
		editor.putInt(key, value);
		return editor.commit();		
	}
	
	public long getTime(String key){
		return sp.getLong(key, 0);
	}
	
	public boolean setTime(String key, long value){
		Editor editor = sp.edit();
		editor.putLong(key, value);
		return editor.commit();		
	}
	
	public boolean setPlayerId(String playerId){
		Editor editor = sp.edit();
		editor.putString(GameInfoUtil.PLAYER_ID, playerId);
		return editor.commit();
	}
	
	public String getPlayerId(){
		if(sp == null){
			return DeviceInfo.imsi;
		}else{
			return sp.getString(GameInfoUtil.PLAYER_ID, DeviceInfo.imsi);
		}
	}
	
	public boolean setNickName(String nickName){
		Editor editor = sp.edit();
		editor.putString(GameInfoUtil.NICK_NAME, nickName);
		return editor.commit();
	}
	
	public String getNickName(){
		if(sp == null){
			return DeviceInfo.product + DeviceInfo.imei.substring(DeviceInfo.imei.length()-4, DeviceInfo.imei.length());
		}else{
			return sp.getString(GameInfoUtil.NICK_NAME, DeviceInfo.product + DeviceInfo.imei.substring(DeviceInfo.imei.length()-4, DeviceInfo.imei.length()));
		}
	}
}
