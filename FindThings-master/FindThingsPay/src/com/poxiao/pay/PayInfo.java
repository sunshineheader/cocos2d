package com.poxiao.pay;

import com.tallbigup.buffett.OrderInfo;

public class PayInfo {

	private static PayInfo instance;
	
	private PayInfo(){
	}
	
	public static PayInfo getInstance(){
		if(instance == null){
			instance = new PayInfo();
		}
		return instance;
	}
	
	public OrderInfo getOrderInfo(int payCode, String sequence, String orderId) {
		OrderInfo orderInfo = new OrderInfo();
		orderInfo.setPrice(PAY.getMoney(payCode));
		orderInfo.setProductName(PAY.getName(payCode));
		orderInfo.setOrderDesc(PAY.getDesc(payCode));
		orderInfo.setOrderId(orderId);
		orderInfo.setPayPointNum(payCode);
		orderInfo.setSequence(sequence);
		return orderInfo;
	}
}
