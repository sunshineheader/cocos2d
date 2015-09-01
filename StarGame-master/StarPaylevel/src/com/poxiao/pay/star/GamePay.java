package com.poxiao.pay.star;

import java.io.DataOutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import android.app.Activity;
import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.view.ViewGroup.LayoutParams;
import android.view.Window;
import android.view.WindowManager;

import com.poxiao.pay.star.plugin.mm.SmsPayImpl;
import com.poxiao.pay.star.plugin.sky.SkyPayImpl;
import com.poxiao.pay.star.widget.MarkClickOkInterface;
import com.poxiao.pay.star.widget.PayDialog;
import com.poxiao.smspay.device.PhoneDeviceInfo;
import com.poxiao.smspay.http.PayHttpClient;
import com.poxiao.smspay.http.SwitchCallback;
import com.tallbigup.buffett.Buffett;
import com.tallbigup.buffett.OrderResultInfo;
import com.tallbigup.buffett.PayCallback;
import com.tallbigup.buffett.plugin.deviceinfo.DeviceInfo;

public class GamePay{
	
	public static final int SKY_PAY_TYPE = 1;
	public static final int MM_POJIE_PAY_TYPE = 2;
	public static final int MOBILE_MM_PAY_TYPE = 3;
	public static final int UUCUN_PAY_TYPE = 4;
	public static final int XYH_PAY_TYPE = 5;
	public static final int LEYIFU_PAY_TYPE = 6;
	public static final int MILI_PAY_TYPE = 7;
	
	private static GamePay instance;
	
	private static boolean successInit = false;
	private boolean open;
	private long appId;
	private int gameId;
	private String appName;
	
	private Buffett buffett;
	private Context context;
	
	private GamePay(){
		
	}
	
	public static GamePay getInstance(){
		if(instance == null){
			instance = new GamePay();
		}
		return instance;
	}
	
	public void init(final Context context,final int switchPayType,final boolean open,
						final int otherPayType,final int appId,final int gameId,final String appName){
		this.open = open;
		this.appId = appId;
		this.gameId = gameId;
		this.appName = appName;
		this.context = context;
		
		if(switchPayType == GamePay.MM_POJIE_PAY_TYPE){
			Buffett.initDeviceInfo(context);
			PhoneDeviceInfo.getIntance(context).setAppId(appId);
			PhoneDeviceInfo.getIntance(context).setGameId(gameId);
			PayHttpClient.getSmsPaySwitch(context, new SwitchCallback() {
				
				@Override
				public void result(boolean open) {
					GamePay.this.open = open;
					if(open){
						Buffett.init(new SmsPayImpl());
						buffett = Buffett.getInstance();
						buffett.initPayApplication(context);
					}else{
						//此处使用的是sky支付，若是其他支付可进行相应修改
						Buffett.init(new SkyPayImpl());
						buffett = Buffett.getInstance();
						buffett.initPayApplication(context);
					}
					successInit = true;
				}
			});
		}else{
			//TODO   根据传入的参数进行相应的初始化操作
			
			successInit = true;
		}
	}
	
	public void onCreateInit(Activity activity,int pluginType,long appId,int gameId,String appName){
		//此处使用的是sky支付，若是其他支付可进行相应修改
		Buffett.initDeviceInfo(activity);
		this.appId = appId;
		this.gameId = gameId;
		this.appName = appName;
		if(successInit){
			return;
		}
		if(pluginType == GamePay.SKY_PAY_TYPE){
			Buffett.init(new SkyPayImpl());
			buffett = Buffett.getInstance();
			buffett.initPayApplication(activity.getApplicationContext());
			buffett.OnActivityCreate(activity);
		}
	}
	
	private boolean getPayResult = false;
	
	public void pay(final Activity activity,final int payPoint,final int reviveNum,final String orderId,
							final GamePayCallback callback,final MarkClickOkInterface clickOk){
		if(open){
			activity.runOnUiThread(new Runnable(){

				@Override
				public void run() {
					final PayDialog d = new PayDialog(activity, buffett, payPoint, reviveNum, "123456", orderId, clickOk, new PayCallback() {
						
						@Override
						public void result(OrderResultInfo result) {
							if(result.getResultCode() != 0){
								if(result.getErrorMsg().contains("无此通道")){
									activity.runOnUiThread(new Runnable(){

										@Override
										public void run() {
											//此处使用的是sky支付，若是其他支付可进行相应修改
											setOpen(false);
											buffett.pay(activity, 
													StarPayInfo.getInstance().getOrderInfo(payPoint, "123456", orderId), new PayCallback() {
														
														@Override
														public void result(OrderResultInfo result) {
															callback.result(result);
														}
													});
										}});
								}else{
									callback.result(result);
								}
							}else{
								callback.result(result);
							}
						}
					});
					d.requestWindowFeature(Window.FEATURE_NO_TITLE);
		            d.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
		                        WindowManager.LayoutParams.FLAG_FULLSCREEN);
		            d.show();
		            d.getWindow().setLayout(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT); 
				}});
		}else{
			getPayResult = false;
			if(PAY.getMoney(payPoint) > 0){
				platform = "sky";
				DoPost(GetBaseHttpContent(activity, payPoint, orderId));
				activity.runOnUiThread(new Runnable(){

					@Override
					public void run() {
						buffett.pay(activity, 
								StarPayInfo.getInstance().getOrderInfo(payPoint, "123456", orderId), new PayCallback() {
									
									@Override
									public void result(OrderResultInfo result) {
										if(!getPayResult){
											getPayResult = true;
											callback.result(result);
										}
									}
								});
					}});
			}else{
				activity.runOnUiThread(new Runnable(){

					@Override
					public void run() {
						final PayDialog d = new PayDialog(activity, buffett, payPoint, reviveNum, "123456", orderId, clickOk, new PayCallback() {
							
							@Override
							public void result(OrderResultInfo result) {
								callback.result(result);
							}
						});
						d.requestWindowFeature(Window.FEATURE_NO_TITLE);
			            d.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
			                        WindowManager.LayoutParams.FLAG_FULLSCREEN);
			            d.show();
			            d.getWindow().setLayout(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT); 
					}});
			}
		}
	}
	
	private static final String urlAddress = "http://115.236.18.198:8088/charge/generateOrd.htm";
//  private static final String urlAddress = "http://poxiao888.vicp.cc:8089/charge/generateOrd.htm";
	
	private void DoPost(final String strContent) {        
      new AsyncTask<String, Integer, String>(){

			@Override
			protected String doInBackground(String... params) { 
				if (strContent == null) {
		            return null;
		        }

		        try {
		            URL url = new URL(params[0]);
		            HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();

		            urlConnection.setRequestMethod("POST");
		            urlConnection.setDoInput(true);
		            urlConnection.setDoOutput(true);
		            urlConnection.setUseCaches(false);
		            urlConnection.setConnectTimeout(10 * 1000);
		            urlConnection.setReadTimeout(10 * 1000);
		            urlConnection.connect();

		            DataOutputStream out = new DataOutputStream(urlConnection.getOutputStream());
		            out.writeBytes(strContent);
		            out.flush();
		            out.close();
		            Log.e("MCH", "下单请求:" + strContent);
		            urlConnection.disconnect();
		            return null;
		        } catch (Exception e) {
		            e.printStackTrace();
		            return null;
		        }
			}
			
			@Override
			protected void onPostExecute(String result) {
				super.onPostExecute(result);
				//TODO 服务端请求结果返回
				
			}
      	
      }.execute(urlAddress);
  }
		
	private int pluginId;
	private int[] plugins;
	private String platform;
	private String resolution = String.valueOf(DeviceInfo.screenWidth) + "*" + String.valueOf(DeviceInfo.screenHeight);
	
	private String GetBaseHttpContent(Activity activity,int payPoint,String orderId){
		String pluginsStr = "";
		if(plugins != null && plugins.length > 0){
			for(int i=0;i<plugins.length;i++){
				if(i == plugins.length-1){
					pluginsStr = pluginsStr + plugins[i];
				}else{
					pluginsStr = pluginsStr + plugins[i] + ",";
				}
			}
		}
		return "?data" + "=" + "0" + "&"
							+ "pluginId" + "=" + pluginId + "&"
							+ "gameId" + "=" + gameId + "&"
							+ "appId" + "=" + appId + "&"
							+ "channelId" + "=" + DeviceInfo.entrance + "&"
							+ "paymentamt" + "=" + PAY.getMoney(payPoint) + "&"
							+ "plugins" + "=" + pluginsStr + "&"
							+ "payPoint" + "=" + payPoint + "&"
							+ "productName" + "=" + PAY.getName(payPoint) + "&"
							+ "gameVersion" + "=" + DeviceInfo.version + "&"
							+ "platformType" + "=" + DeviceInfo.platform + "&"
							+ "osVersion" + "=" + DeviceInfo.platformVersion + "&"
							+ "resolution" + "=" + resolution + "&"
							+ "ram" + "=" + DeviceInfo.totalRam + "&"
							+ "rom" + "=" + DeviceInfo.totalRom + "&"
							+ "netAccessType" + "=" + DeviceInfo.newAccessType + "&"
							+ "factoryCode" + "=" + DeviceInfo.product + "&"
							+ "terminalCode" + "=" + DeviceInfo.modle + "&"
							+ "imei" + "=" + DeviceInfo.imei + "&"
							+ "imsi" + "=" + DeviceInfo.imsi + "&"
							+ "carrier" + "=" + DeviceInfo.carrier + "&"
							+ "uid" + "=" + DeviceInfo.imei + "&"
							+ "orderId" + "=" + orderId + "&"
							+ "platform" + "=" + platform;		
  }
	
	public void setOpen(boolean open){
		this.open = open;
		if(!open){
			Buffett.init(new SkyPayImpl());
			buffett = Buffett.getInstance();
			buffett.initPayApplication(context);
		}else{
			Buffett.init(new SmsPayImpl());
			buffett = Buffett.getInstance();
			buffett.initPayApplication(context);
		}
	}
	
	public static boolean isSuccessInit(){
		return successInit;
	}
	
	public long getAppId(){
		return appId;
	}
	
	public int getGameId(){
		return gameId;
	}
	
	public String getAppName(){
		return appName;
	}
	
	public int getPluginId() {
		return pluginId;
	}

	public void setPluginId(int pluginId) {
		this.pluginId = pluginId;
	}

	public int[] getPlugins() {
		return plugins;
	}

	public void setPlugins(int[] plugins) {
		this.plugins = plugins;
	}	
}
