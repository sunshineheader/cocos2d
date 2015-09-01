/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.poxiao.pay.xbll.GamePay;
import com.tallbigup.android.cloud.TbuCloud;
import android.app.Dialog;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;

public class AppActivity extends Cocos2dxActivity {
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		initGamePay();
		GameInfoUtil.getInstance();
		NetWorkService.init(this);
		PayService.init(this);
		NativeNotifyService.init(this);
		SignInService.init(this);
		NetWorkService.getOpenMoreGame();
		if(TbuCloud.markUserType(getApplicationContext()) == 0){
			   TbuCloud.markUserPay(getApplicationContext(), 0);
		}
		TbuCloud.markUserLogin(getApplicationContext(), System.currentTimeMillis());				
		TbuCloud.markAppOpened(AppActivity.this);
		GameApplication.getInstance().startPush();
	}
	
	
	private void initGamePay(){
		GamePay.getInstance().initOnFirstActivity(AppActivity.this);;// appName
	}


}
