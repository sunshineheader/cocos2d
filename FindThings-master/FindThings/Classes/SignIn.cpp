#include "SignIn.h"
#include "Chinese.h"
#include "CallAndroidMethod.h"
#include "GameData.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Chinese.h"
#include "Audio.h"

SignIn* SignIn::_instance = nullptr;

SignIn::SignIn(){
	this->init();
}

SignIn* SignIn::getInstance(){
	if(_instance == nullptr){
		_instance = new SignIn();
	}
	return _instance;
}

bool SignIn::init(){
	if(!Node::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* sign_bg = Sprite::create("sign_in_bg.png");
	sign_bg->setAnchorPoint(ccp(0.5,0.5));
	sign_bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(sign_bg,-1);

	Sprite* title = Sprite::create("sign_in_title.png");
	title->setAnchorPoint(ccp(0.5,0.5));
	title->setPosition(visibleSize.width/2,visibleSize.height/2+100);
	this->addChild(title);

	MenuItemImage* day_1 =  MenuItemImage::create("sign_in_item_bg_1.png","sign_in_item_bg_1.png");
	MenuItemImage* day_2 =  MenuItemImage::create("sign_in_item_bg_1.png","sign_in_item_bg_1.png");
	MenuItemImage* day_3 =  MenuItemImage::create("sign_in_item_bg_1.png","sign_in_item_bg_1.png");
	MenuItemImage* day_4 =  MenuItemImage::create("sign_in_item_bg_1.png","sign_in_item_bg_1.png");
	MenuItemImage* day_5 =  MenuItemImage::create("sign_in_item_bg_1.png","sign_in_item_bg_1.png");
	Menu* signMenu = Menu ::create(day_1,day_2,day_3,day_4,day_5,NULL);
	signMenu->alignItemsHorizontallyWithPadding(10);
	signMenu->setAnchorPoint(Point(0.5,0.5));
	signMenu->setPosition(visibleSize.width/2,visibleSize.height/2);
	signMenu->setTouchEnabled(false);
	this->addChild(signMenu);

	MenuItemImage* confirm = MenuItemImage::create("sign_in_confirm_up.png","sign_in_confirm_down.png",CC_CALLBACK_0(SignIn::startGameT,this));
	Menu* start = Menu::create(confirm,NULL);
	start->setAnchorPoint(ccp(0.5,0.5));
	start->setPosition(visibleSize.width/2,visibleSize.height/2-120);
	this->addChild(start);

	auto signedBg = Sprite::create("sign_in_item_bg_2.png");
	signedBg->setVisible(false);
	this->addChild(signedBg);
	auto hasSignMark = Sprite::create("sign_in_has_sign.png");
	hasSignMark->setVisible(false);
	this->addChild(hasSignMark);

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		int signDay = CallAndroidMethod::getInstance()->getCurrentSignDayas();
		if(signDay == 0){
			signedBg->setPosition(70,442);
			hasSignMark->setPosition(102,496);
		}else if(signDay == 1){
			signedBg->setPosition(155,442);
			hasSignMark->setPosition(187,496);
		}else if(signDay == 2){
			signedBg->setPosition(240,442);
			hasSignMark->setPosition(272,496);
		}else if(signDay == 3){
			signedBg->setPosition(325,442);
			hasSignMark->setPosition(357,496);
		}else if(signDay >= 4){
			signedBg->setPosition(410,442);
			hasSignMark->setPosition(442,496);
		}
    #endif
	return true;
}

void SignIn::startGameT(){
	//开始游戏
	Director::getInstance()->replaceScene(TransitionFade::create(1,GameScene::create()));
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CallAndroidMethod::getInstance()->sign();
#endif
}
