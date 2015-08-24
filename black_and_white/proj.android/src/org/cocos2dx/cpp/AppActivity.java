package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.util.Log;

import com.poxiao.pay.xbll.GamePay;

public class AppActivity extends Cocos2dxActivity {

	private GameInfoUtil gameInfo;
	private  static Activity activity;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		GamePay.getInstance().initOnFirstActivity(AppActivity.this);
		GameInfoUtil.getInstance();
		PayService.init(this);
		activity=this;
//		 if (TbuCloud.markUserType(getApplicationContext()) == 0) {
//		 TbuCloud.markUserPay(getApplicationContext(), 0);
//		 }
//		 TbuCloud.markAppOpened(AppActivity.this);
	}
	
	public static void quitGame(){

		Log.i("W_B","quit game");
		activity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				AlertDialog.Builder builder = new AlertDialog.Builder(activity);
				builder.setMessage("退出游戏?")
				       .setCancelable(false)
				       .setPositiveButton("确定", new DialogInterface.OnClickListener() {
				           public void onClick(DialogInterface dialog, int id) {
				        	   activity.finish();
				           }
				       })
				       .setNegativeButton("取消", new DialogInterface.OnClickListener() {
				           public void onClick(DialogInterface dialog, int id) {
				                dialog.cancel();
				           }
				       }).show();
			}
			
		});
		
	}
	

	
	

}
