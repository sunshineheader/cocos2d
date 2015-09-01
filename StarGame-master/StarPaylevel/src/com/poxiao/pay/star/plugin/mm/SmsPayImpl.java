package com.poxiao.pay.star.plugin.mm;

import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.Date;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.util.Log;

import com.poxiao.smspay.PxPayCallBack;
import com.poxiao.smspay.SmsPayBasis;
import com.poxiao.smspay.activity.activity_pxpaymain;
import com.poxiao.smspay.device.PhoneDeviceInfo;
import com.tallbigup.buffett.OrderInfo;
import com.tallbigup.buffett.OrderResultInfo;
import com.tallbigup.buffett.PayCallback;
import com.tallbigup.buffett.PayInterface;

public class SmsPayImpl implements PayInterface{
	
	private Activity activity;
	private PayCallback callback;
	
	private PxPayCallBack pxPayCallback = new PxPayCallBack() {
		
		@Override
		public void PayResult(int pxResultCode, int baseResultCode, String baseMsg) {
			Log.i("MCH","pxResultCode=" + pxResultCode);
			if(pxResultCode == activity_pxpaymain.PX_RESULTCODE_GET_INSTRUCT){
				Log.i("MCH","baseResultCode=" + baseResultCode);
				if(baseResultCode == activity_pxpaymain.PX_RESULTCODE_SUCCESS){
					Intent intentActivity = new Intent(activity, activity_pxpaymain.class);
			        activity.startActivity(intentActivity);  
			        activity.runOnUiThread(new Runnable(){

						@Override
						public void run() {
							new Handler().postDelayed(new Runnable(){

								@Override
								public void run() {
									removeDialog();
								}}, 1500);
						}});
				}else{
					OrderResultInfo result = new OrderResultInfo();
					result.setResultCode(1);
					result.setErrorCode(String.valueOf(baseResultCode));
					result.setErrorMsg(baseMsg);
					removeDialog();
					callback.result(result);
				}
			}else{
				OrderResultInfo result = new OrderResultInfo();
				if(baseResultCode == activity_pxpaymain.PX_RESULTCODE_SUCCESS){
					result.setResultCode(0);
					result.setErrorCode("");
					result.setErrorMsg("支付成功");
				}else{
					result.setResultCode(1);
					result.setErrorCode(String.valueOf(baseResultCode));
					result.setErrorMsg(baseMsg);
				}
				callback.result(result);
			}
		}
	};

	@Override
	public void OnActivityCreate(Activity activity) {
	}

	@Override
	public void OnActivityDestory(Activity activity) {
	}

	@Override
	public void OnActivityPause(Activity activity) {
	}

	@Override
	public void OnActivityResume(Activity activity) {
	}

	@Override
	public String getPayPluginName() {
		return "mm_pj";
	}

	@Override
	public int getPayVersionId() {
		return 1;
	}

	@Override
	public void initPayApplication(Context context) {
	}
	
	private ProgressDialog progressDialog;
	
	private void showDialog(){
		if(progressDialog == null){
			progressDialog = new ProgressDialog(activity);
		}
        progressDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);// 设置风格为圆形进度条
        progressDialog.setTitle("提示");// 设置标题
        progressDialog.setMessage("正在进行操作，请稍候...");
        progressDialog.setIndeterminate(true);// 设置进度条是否为不明确
        progressDialog.setCancelable(false);// 设置进度条是否可以按退回键取消
        progressDialog.show();
	}
	
	private void removeDialog(){
		if(progressDialog != null){
			progressDialog.dismiss();
		}
	}

	@Override
	public void pay(final Activity activity, OrderInfo orderInfo, final PayCallback callback) {		
		this.activity = activity;
		this.callback = callback;
		showDialog();
		Date date = new Date();
		SimpleDateFormat format = new SimpleDateFormat("yyyyMMdd");
		
		try {
            PhoneDeviceInfo phoneDeviceInfo = PhoneDeviceInfo.getIntance(activity.getApplication());
            phoneDeviceInfo.setInputParam(1, pxPayCallback, PhoneDeviceInfo.getIntance(activity.getApplication()).getGameId(),
            		PhoneDeviceInfo.getIntance(activity.getApplication()).getAppId(), orderInfo.getPrice(),
            		URLEncoder.encode(orderInfo.getProductName(), "utf-8"),"300010" + format.format(date) + orderInfo.getOrderId());
            phoneDeviceInfo.displayLogInfo();
        } catch (Exception e) {
            e.printStackTrace();
        }
        new SmsPayBasis().DoGetGameBasisCode(activity,pxPayCallback); 
	}

	@Override
	public void OnActivityResult(int requestCode, int resultCode, Intent data) {
		
	}
}
