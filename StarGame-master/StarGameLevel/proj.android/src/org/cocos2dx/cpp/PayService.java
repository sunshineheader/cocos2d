package org.cocos2dx.cpp;

import java.util.Random;

import com.poxiao.pay.star.GamePay;
import com.poxiao.pay.star.PAY;
import com.poxiao.pay.star.GamePayCallback;
import com.poxiao.pay.star.widget.MarkClickOkInterface;
import com.tallbigup.android.cloud.TbuCallback;
import com.tallbigup.android.cloud.TbuCloud;
import com.tallbigup.buffett.Buffett;
import com.tallbigup.buffett.OrderResultInfo;
import com.tallbigup.buffett.plugin.deviceinfo.DeviceInfo;

import android.app.Activity;
import android.util.Log;

public class PayService {
	
	private static Activity activity;
	private static GameInfoUtil gameInfo;
	private static String playerId;
	
	public static void init(Activity activity){
		PayService.activity = activity;
		gameInfo = GameInfoUtil.getInstance();
		gameInfo.init(activity);
		playerId = GameApplication.getInstance().getPlayerId();
	}
	
	public static void pay(final int payPoint,final int reviveNum){
		if(payPoint < 9){
			final int tempPayPoint = 7;
			activity.runOnUiThread(new Runnable(){

				@Override
				public void run() {
					final String orderId = String.valueOf(System.currentTimeMillis())+new Random().nextInt(100);
					if(PAY.getMoney(tempPayPoint) > 0){
						final int payCount = gameInfo.getData(GameInfoUtil.PAY_COUNT) + 1;
						gameInfo.setData(GameInfoUtil.PAY_COUNT, payCount);
						setPayInfo("request", tempPayPoint, playerId, PAY.getMoney(tempPayPoint), "0", PAY.getDesc(tempPayPoint), 
								PAY.getDesc(tempPayPoint), payCount, orderId, "100", "请求支付");
						
						GamePay.getInstance().pay(activity, tempPayPoint, reviveNum, orderId, new GamePayCallback() {
							
							@Override
							public void result(OrderResultInfo result) {
								Log.e("MCH", "resultCode="+result.getResultCode());
								if(result.getResultCode() == 0){
									JniPayCallbackHelper.payCallback(payPoint, 0);
									TbuCloud.markUserPay(activity, 1);
									gameInfo.setData(GameInfoUtil.PAY_MONEY, gameInfo.getData(GameInfoUtil.PAY_MONEY)+PAY.getMoney(tempPayPoint));
									setPayInfo("success", tempPayPoint, playerId, PAY.getMoney(tempPayPoint), "0", 
											PAY.getName(tempPayPoint), PAY.getDesc(tempPayPoint), payCount, orderId, "0", "支付成功");
								}else if(result.getResultCode() == -3){
									JniPayCallbackHelper.payCallback(payPoint, 1);
									setPayInfo("cancel", tempPayPoint, playerId, PAY.getMoney(tempPayPoint), "0", 
											PAY.getName(tempPayPoint), PAY.getDesc(tempPayPoint), payCount, orderId, "-3", "取消支付");
								}else{
									JniPayCallbackHelper.payCallback(payPoint, 1);
									setPayInfo("fail", tempPayPoint, playerId, PAY.getMoney(tempPayPoint), "0", 
											PAY.getName(tempPayPoint), PAY.getDesc(tempPayPoint), payCount, orderId, result.getErrorCode(), result.getErrorMsg());
								}
							}
						}, new MarkClickOkInterface() {
							
							@Override
							public void clickOk() {
								setPayInfo("clickOk", tempPayPoint, playerId, PAY.getMoney(tempPayPoint), "0", 
										PAY.getName(tempPayPoint), PAY.getDesc(tempPayPoint), payCount, orderId, "101", "点击确定");
							}
						});
					}else{
						GamePay.getInstance().pay(activity, tempPayPoint, reviveNum, orderId, new GamePayCallback() {
							
							@Override
							public void result(OrderResultInfo result) {
								if(result.getResultCode() == 0){
									JniPayCallbackHelper.payCallback(payPoint, 0);
								}else if(result.getResultCode() == -3){
									JniPayCallbackHelper.payCallback(payPoint, 1);
								}else{
									JniPayCallbackHelper.payCallback(payPoint, 1);
								}
							}
						}, new MarkClickOkInterface() {
							
							@Override
							public void clickOk() {
							}
						});
					}
				}});
		}else if(payPoint < 11){
			activity.runOnUiThread(new Runnable(){

				@Override
				public void run() {
					final String orderId = String.valueOf(System.currentTimeMillis())+new Random().nextInt(100);
					if(PAY.getMoney(payPoint) > 0){
						final int payCount = gameInfo.getData(GameInfoUtil.PAY_COUNT) + 1;
						gameInfo.setData(GameInfoUtil.PAY_COUNT, payCount);
						setPayInfo("request", payPoint, playerId, PAY.getMoney(payPoint), "0", PAY.getDesc(payPoint), 
								PAY.getDesc(payPoint), payCount, orderId, "100", "请求支付");
						
						GamePay.getInstance().pay(activity, payPoint, reviveNum, orderId, new GamePayCallback() {
							
							@Override
							public void result(OrderResultInfo result) {
								Log.e("MCH", "resultCode="+result.getResultCode());
								if(result.getResultCode() == 0){
									JniPayCallbackHelper.payCallback(payPoint, 0);
									TbuCloud.markUserPay(activity, 1);
									gameInfo.setData(GameInfoUtil.PAY_MONEY, gameInfo.getData(GameInfoUtil.PAY_MONEY)+PAY.getMoney(payPoint));
									setPayInfo("success", payPoint, playerId, PAY.getMoney(payPoint), "0", 
											PAY.getName(payPoint), PAY.getDesc(payPoint), payCount, orderId, "0", "支付成功");
								}else if(result.getResultCode() == -3){
									JniPayCallbackHelper.payCallback(payPoint, 1);
									setPayInfo("cancel", payPoint, playerId, PAY.getMoney(payPoint), "0", 
											PAY.getName(payPoint), PAY.getDesc(payPoint), payCount, orderId, "-3", "取消支付");
								}else{
									JniPayCallbackHelper.payCallback(payPoint, 1);
									setPayInfo("fail", payPoint, playerId, PAY.getMoney(payPoint), "0", 
											PAY.getName(payPoint), PAY.getDesc(payPoint), payCount, orderId, result.getErrorCode(), result.getErrorMsg());
								}
							}
						}, new MarkClickOkInterface() {
							
							@Override
							public void clickOk() {
								setPayInfo("clickOk", payPoint, playerId, PAY.getMoney(payPoint), "0", 
										PAY.getName(payPoint), PAY.getDesc(payPoint), payCount, orderId, "101", "点击确定");
							}
						});
					}else{
						GamePay.getInstance().pay(activity, payPoint, reviveNum, orderId, new GamePayCallback() {
							
							@Override
							public void result(OrderResultInfo result) {
								if(result.getResultCode() == 0){
									JniPayCallbackHelper.payCallback(payPoint, 0);
								}else if(result.getResultCode() == -3){
									JniPayCallbackHelper.payCallback(payPoint, 1);
								}else{
									JniPayCallbackHelper.payCallback(payPoint, 1);
								}
							}
						}, new MarkClickOkInterface() {
							
							@Override
							public void clickOk() {
							}
						});
					}
				}});
		}else if(payPoint == 11){
			final int tempPayPoint = 9;
			activity.runOnUiThread(new Runnable(){

				@Override
				public void run() {
					final String orderId = String.valueOf(System.currentTimeMillis())+new Random().nextInt(100);
					if(PAY.getMoney(tempPayPoint) > 0){
						final int payCount = gameInfo.getData(GameInfoUtil.PAY_COUNT) + 1;
						gameInfo.setData(GameInfoUtil.PAY_COUNT, payCount);
						setPayInfo("request", tempPayPoint, playerId, PAY.getMoney(tempPayPoint), "0", PAY.getDesc(tempPayPoint), 
								PAY.getDesc(tempPayPoint), payCount, orderId, "100", "请求支付");
						
						GamePay.getInstance().pay(activity, tempPayPoint, reviveNum, orderId, new GamePayCallback() {
							
							@Override
							public void result(OrderResultInfo result) {
								Log.e("MCH", "resultCode="+result.getResultCode());
								if(result.getResultCode() == 0){
									JniPayCallbackHelper.payCallback(payPoint, 0);
									TbuCloud.markUserPay(activity, 1);
									gameInfo.setData(GameInfoUtil.PAY_MONEY, gameInfo.getData(GameInfoUtil.PAY_MONEY)+PAY.getMoney(tempPayPoint));
									setPayInfo("success", tempPayPoint, playerId, PAY.getMoney(tempPayPoint), "0", 
											PAY.getName(tempPayPoint), PAY.getDesc(tempPayPoint), payCount, orderId, "0", "支付成功");
								}else if(result.getResultCode() == -3){
									JniPayCallbackHelper.payCallback(payPoint, 1);
									setPayInfo("cancel", tempPayPoint, playerId, PAY.getMoney(tempPayPoint), "0", 
											PAY.getName(tempPayPoint), PAY.getDesc(tempPayPoint), payCount, orderId, "-3", "取消支付");
								}else{
									JniPayCallbackHelper.payCallback(payPoint, 1);
									setPayInfo("fail", tempPayPoint, playerId, PAY.getMoney(tempPayPoint), "0", 
											PAY.getName(tempPayPoint), PAY.getDesc(tempPayPoint), payCount, orderId, result.getErrorCode(), result.getErrorMsg());
								}
							}
						}, new MarkClickOkInterface() {
							
							@Override
							public void clickOk() {
								setPayInfo("clickOk", tempPayPoint, playerId, PAY.getMoney(tempPayPoint), "0", 
										PAY.getName(tempPayPoint), PAY.getDesc(tempPayPoint), payCount, orderId, "101", "点击确定");
							}
						});
					}else{
						GamePay.getInstance().pay(activity, tempPayPoint, reviveNum, orderId, new GamePayCallback() {
							
							@Override
							public void result(OrderResultInfo result) {
								if(result.getResultCode() == 0){
									JniPayCallbackHelper.payCallback(payPoint, 0);
								}else if(result.getResultCode() == -3){
									JniPayCallbackHelper.payCallback(payPoint, 1);
								}else{
									JniPayCallbackHelper.payCallback(payPoint, 1);
								}
							}
						}, new MarkClickOkInterface() {
							
							@Override
							public void clickOk() {
							}
						});
					}
				}});
		}
	}
	
	private static void setPayInfo(String payState,int payPoint,String playerId,int money,String levelId,String propName,
			String desc,int payCount,String orderId,String errorCode,String errorMsg){
		Log.e("MCH","buffett=" + Buffett.getInstance());
		TbuCloud.setPayInfo(
				payState, 
				money, 
				String.valueOf(payPoint),
				playerId, 
				desc, 
				payCount, 
				com.tallbigup.buffett.plugin.configuration.Configuration.enterId,
				orderId,
				errorCode,
				errorMsg,
				DeviceInfo.version,
				String.valueOf(Buffett.getInstance().getPayVersionId()),
				levelId+"",
				DeviceInfo.imsi,
				DeviceInfo.carrier+"",
				Buffett.getInstance().getPayPluginName(),
				String.valueOf(gameInfo.getData(GameInfoUtil.USER_TYPE)==0 ? "new" : "old"),
				new TbuCallback() {							
					@Override
					public void result(boolean success) {
						Log.i("MCH","上传支付结果：" + success);								
					}
				});
	}
}
