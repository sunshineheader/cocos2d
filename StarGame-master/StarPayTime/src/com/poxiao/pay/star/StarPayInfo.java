package com.poxiao.pay.star;

import com.tallbigup.buffett.OrderInfo;

public class StarPayInfo {

	private static StarPayInfo instance;
	
	private StarPayInfo(){
	}
	
	public static StarPayInfo getInstance(){
		if(instance == null){
			instance = new StarPayInfo();
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
