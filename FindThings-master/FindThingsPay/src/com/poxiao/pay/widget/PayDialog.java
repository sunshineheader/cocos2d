package com.poxiao.pay.widget;

import android.app.Activity;
import android.app.Dialog;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import com.poxiao.pay.PayInfo;
import com.poxiao.pay.R;
import com.tallbigup.buffett.Buffett;
import com.tallbigup.buffett.OrderInfo;
import com.tallbigup.buffett.OrderResultInfo;
import com.tallbigup.buffett.PayCallback;

public class PayDialog extends Dialog {

	private Activity activity;
	private Buffett buffett;
	private int payPoint;
	private String sequence;
	private String orderId;
	private PayCallback callback;
	private DIALOGTYPE TYPE;

	private ImageView payTip1;
	private ImageView payTipsText;
	private ImageView payTipsText2;

	private MarkClickOkInterface markClickOkInterface;

	private static final int DIALOG_TYPE_MM = 1;
	private static final int DIALOG_TYPE_LT = 2;

	public enum DIALOGTYPE {
		DIALOG_TYPE_MM, DIALOG_TYPE_LT;
	}

	public PayDialog(Activity activity, Buffett buffett, int payPoint,
			String sequence, String orderId, DIALOGTYPE type,
			MarkClickOkInterface markClickOkInterface, PayCallback callback) {
		super(activity, R.style.dialog_game_style);
		this.activity = activity;
		this.buffett = buffett;
		this.payPoint = payPoint;
		this.sequence = sequence;
		this.orderId = orderId;
		this.callback = callback;
		this.TYPE = type;
		this.markClickOkInterface = markClickOkInterface;
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.dialog_pay);
		initView();
	}

	private void initView() {
		final OrderInfo orderInfo = PayInfo.getInstance().getOrderInfo(
				payPoint, sequence, orderId);

		payTip1 = (ImageView) findViewById(R.id.pay_tip1);
		payTipsText = (ImageView) findViewById(R.id.payTipsText);
		payTipsText2 = (ImageView) findViewById(R.id.payTipsText2);
		Log.e("MCH", "payPoint=" + String.valueOf(payPoint));
		switch (payPoint) {
		case 1:
			if (TYPE == DIALOGTYPE.DIALOG_TYPE_MM) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_1);
			} else if (TYPE == DIALOGTYPE.DIALOG_TYPE_LT) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_lt_1);
			}
			payTip1.setBackgroundResource(R.drawable.pay_tip_goods_1);
			break;
		case 2:
			if (TYPE == DIALOGTYPE.DIALOG_TYPE_MM) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_2);
			} else if (TYPE == DIALOGTYPE.DIALOG_TYPE_LT) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_lt_2);
			}
			payTip1.setBackgroundResource(R.drawable.pay_tip_goods_2);
			break;
		case 3:
			if (TYPE == DIALOGTYPE.DIALOG_TYPE_MM) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_3);
			} else if (TYPE == DIALOGTYPE.DIALOG_TYPE_LT) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_lt_3);
			}
			payTip1.setBackgroundResource(R.drawable.pay_tip_goods_3);
			break;
		case 4:
			if (TYPE == DIALOGTYPE.DIALOG_TYPE_MM) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_4);
			} else if (TYPE == DIALOGTYPE.DIALOG_TYPE_LT) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_lt_4);
			}
			payTip1.setBackgroundResource(R.drawable.pay_tip_goods_4);
			break;
		case 5:
			if (TYPE == DIALOGTYPE.DIALOG_TYPE_MM) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_5);
			} else if (TYPE == DIALOGTYPE.DIALOG_TYPE_LT) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_lt_5);
			}
			payTip1.setBackgroundResource(R.drawable.pay_tip_goods_5);
			break;
		case 6:
			if (TYPE == DIALOGTYPE.DIALOG_TYPE_MM) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_6);
			} else if (TYPE == DIALOGTYPE.DIALOG_TYPE_LT) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_lt_6);
			}
			payTip1.setBackgroundResource(R.drawable.pay_tip_goods_6);
			break;
		case 7:
			if (TYPE == DIALOGTYPE.DIALOG_TYPE_MM) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_7);
			} else if (TYPE == DIALOGTYPE.DIALOG_TYPE_LT) {
				payTipsText
						.setBackgroundResource(R.drawable.pay_tip_goods_text_lt_7);
			}
			payTip1.setBackgroundResource(R.drawable.pay_tip_goods_7);
			break;
		case 8:
			payTip1.setBackgroundResource(R.drawable.pay_tip_goods_5);
			payTipsText.setBackgroundResource(R.drawable.pay_tip_goods_text_8);
			payTipsText2.setVisibility(View.INVISIBLE);
			break;
		case 9:
			payTip1.setBackgroundResource(R.drawable.pay_tip_goods_7);
			payTipsText.setBackgroundResource(R.drawable.pay_tip_goods_text_9);
			payTipsText2.setVisibility(View.INVISIBLE);
			break;

		}

		ImageButton okBtn = (ImageButton) findViewById(R.id.pay_confirm);
		okBtn.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				Log.e("MCH", "Price=" + orderInfo.getPrice());
				// TODO :  免付费版本，关掉支付
				if (0 < orderInfo.getPrice()) { // PAY.getMoney()
					markClickOkInterface.clickOk();
					buffett.pay(activity, orderInfo, callback);
				} else {
					OrderResultInfo result = new OrderResultInfo();
					result.setResultCode(0);
					result.setErrorCode("0");
					result.setErrorMsg("支付成功");
					callback.result(result);
				}
				dismiss();
			}

		});
		ImageButton cancelBtn = (ImageButton) findViewById(R.id.pay_cancel);
		cancelBtn.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				doCancel();
			}
		});
	}

	@Override
	public void onBackPressed() {
		super.onBackPressed();
		doCancel();
	}

	private void doCancel() {
		OrderResultInfo result = new OrderResultInfo();
		result.setResultCode(-3);
		result.setErrorCode("-3");
		result.setErrorMsg("取消支付");
		callback.result(result);
		dismiss();
	}

}
