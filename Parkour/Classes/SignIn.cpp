#include "SignIn.h"
#include "CallAndroidMethod.h"
#include "GAMEDATA.h"
#include "MenuLayer.h"
#include "Audio.h"

int SignIn::currentSignDay = 0;

bool SignIn::init()
{
	if (!Layer::init())
	{
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sign_in.plist");
	auto bg = Sprite::create("black_bg.png");
	bg->setScaleX(800);
	bg->setScaleY(480);
	bg->setPosition(400,240);
	this->addChild(bg);

	auto signInBg = Sprite::createWithSpriteFrameName("sign_in_bg.png");
	signInBg->setPosition(400,240);
	this->addChild(signInBg);

	//day1
	auto currentSignBg1 = Sprite::createWithSpriteFrameName("sign_in_current_bg.png");
	currentSignBg1->setPosition(208.5,286);
	currentSignBg1->setVisible(false);
	this->addChild(currentSignBg1);

	auto hasSignBg1 = Sprite::createWithSpriteFrameName("sign_in_has_bg.png");
	hasSignBg1->setPosition(208.5,286);
	hasSignBg1->setVisible(false);
	this->addChild(hasSignBg1);

	auto hasNotSignBg1 = Sprite::createWithSpriteFrameName("sign_in_has_not_bg.png");
	hasNotSignBg1->setPosition(208.5,286);
	this->addChild(hasNotSignBg1);

	auto day1 = Sprite::createWithSpriteFrameName("sign_in_day_1.png");
	day1->setPosition(208.5,324);
	this->addChild(day1);

	auto icon11 = Sprite::createWithSpriteFrameName("sign_in_super_1.png");
	icon11->setPosition(208.5,289);
	this->addChild(icon11);

	auto icon12 = Sprite::createWithSpriteFrameName("sign_in_super_2.png");
	icon12->setPosition(208.5,289);
	icon12->setVisible(false);
	this->addChild(icon12);

	auto txt_x_1 = Sprite::createWithSpriteFrameName("sign_in_x.png");
	txt_x_1->setPosition(204,257.5);
	this->addChild(txt_x_1);

	auto num1 = LabelAtlas::create("1","sign_in_num.png",9,11,48);
	num1->setAnchorPoint(Point(0.5,0.5));
	num1->setPosition(212.5,257.5);
	this->addChild(num1);

	//day2
	auto currentSignBg2 = Sprite::createWithSpriteFrameName("sign_in_current_bg.png");
	currentSignBg2->setPosition(305.5,286);
	currentSignBg2->setVisible(false);
	this->addChild(currentSignBg2);

	auto hasSignBg2 = Sprite::createWithSpriteFrameName("sign_in_has_bg.png");
	hasSignBg2->setPosition(305.5,286);
	hasSignBg2->setVisible(false);
	this->addChild(hasSignBg2);

	auto hasNotSignBg2 = Sprite::createWithSpriteFrameName("sign_in_has_not_bg.png");
	hasNotSignBg2->setPosition(305.5,286);
	this->addChild(hasNotSignBg2);

	auto day2 = Sprite::createWithSpriteFrameName("sign_in_day_2.png");
	day2->setPosition(305.5,324);
	this->addChild(day2);

	auto icon21 = Sprite::createWithSpriteFrameName("sign_in_potential_1.png");
	icon21->setPosition(305.5,289);
	this->addChild(icon21);

	auto icon22 = Sprite::createWithSpriteFrameName("sign_in_potential_2.png");
	icon22->setPosition(305.5,289);
	icon22->setVisible(false);
	this->addChild(icon22);

	auto txt_x_2 = Sprite::createWithSpriteFrameName("sign_in_x.png");
	txt_x_2->setPosition(301,257.5);
	this->addChild(txt_x_2);

	auto num2 = LabelAtlas::create("1","sign_in_num.png",9,11,48);
	num2->setAnchorPoint(Point(0.5,0.5));
	num2->setPosition(309.5,257.5);
	this->addChild(num2);

	//day3
	auto currentSignBg3 = Sprite::createWithSpriteFrameName("sign_in_current_bg.png");
	currentSignBg3->setPosition(400.5,286);
	currentSignBg3->setVisible(false);
	this->addChild(currentSignBg3);

	auto hasSignBg3 = Sprite::createWithSpriteFrameName("sign_in_has_bg.png");
	hasSignBg3->setPosition(400.5,286);
	hasSignBg3->setVisible(false);
	this->addChild(hasSignBg3);

	auto hasNotSignBg3 = Sprite::createWithSpriteFrameName("sign_in_has_not_bg.png");
	hasNotSignBg3->setPosition(400.5,286);
	this->addChild(hasNotSignBg3);

	auto day3 = Sprite::createWithSpriteFrameName("sign_in_day_3.png");
	day3->setPosition(400.5,324);
	this->addChild(day3);

	auto icon31 = Sprite::createWithSpriteFrameName("sign_in_magnetic_1.png");
	icon31->setPosition(400.5,289);
	this->addChild(icon31);

	auto icon32 = Sprite::createWithSpriteFrameName("sign_in_magnetic_2.png");
	icon32->setPosition(400.5,289);
	icon32->setVisible(false);
	this->addChild(icon32);

	auto txt_x_3 = Sprite::createWithSpriteFrameName("sign_in_x.png");
	txt_x_3->setPosition(396,257.5);
	this->addChild(txt_x_3);

	auto num3 = LabelAtlas::create("1","sign_in_num.png",9,11,48);
	num3->setAnchorPoint(Point(0.5,0.5));
	num3->setPosition(404.5,257.5);
	this->addChild(num3);

	//day4
	auto currentSignBg4 = Sprite::createWithSpriteFrameName("sign_in_current_bg.png");
	currentSignBg4->setPosition(495.5,286);
	currentSignBg4->setVisible(false);
	this->addChild(currentSignBg4);

	auto hasSignBg4 = Sprite::createWithSpriteFrameName("sign_in_has_bg.png");
	hasSignBg4->setPosition(495.5,286);
	hasSignBg4->setVisible(false);
	this->addChild(hasSignBg4);

	auto hasNotSignBg4 = Sprite::createWithSpriteFrameName("sign_in_has_not_bg.png");
	hasNotSignBg4->setPosition(495.5,286);
	this->addChild(hasNotSignBg4);

	auto day4 = Sprite::createWithSpriteFrameName("sign_in_day_4.png");
	day4->setPosition(495.5,324);
	this->addChild(day4);

	auto icon41 = Sprite::createWithSpriteFrameName("sign_in_super_1.png");
	icon41->setPosition(495.5,289);
	this->addChild(icon41);

	auto icon42 = Sprite::createWithSpriteFrameName("sign_in_super_2.png");
	icon42->setPosition(495.5,289);
	icon42->setVisible(false);
	this->addChild(icon42);

	auto txt_x_4 = Sprite::createWithSpriteFrameName("sign_in_x.png");
	txt_x_4->setPosition(491,257.5);
	this->addChild(txt_x_4);

	auto num4 = LabelAtlas::create("2","sign_in_num.png",9,11,48);
	num4->setAnchorPoint(Point(0.5,0.5));
	num4->setPosition(499.5,257.5);
	this->addChild(num4);

	//day5
	auto currentSignBg5 = Sprite::createWithSpriteFrameName("sign_in_current_bg.png");
	currentSignBg5->setPosition(591.5,286);
	currentSignBg5->setVisible(false);
	this->addChild(currentSignBg5);

	auto hasSignBg5 = Sprite::createWithSpriteFrameName("sign_in_has_bg.png");
	hasSignBg5->setPosition(591.5,286);
	hasSignBg5->setVisible(false);
	this->addChild(hasSignBg5);

	auto hasNotSignBg5 = Sprite::createWithSpriteFrameName("sign_in_has_not_bg.png");
	hasNotSignBg5->setPosition(591.5,286);
	this->addChild(hasNotSignBg5);

	auto day5 = Sprite::createWithSpriteFrameName("sign_in_day_5.png");
	day5->setPosition(591.5,324);
	this->addChild(day5);

	auto icon51 = Sprite::createWithSpriteFrameName("sign_in_potential_1.png");
	icon51->setPosition(591.5,289);
	this->addChild(icon51);

	auto icon52 = Sprite::createWithSpriteFrameName("sign_in_potential_2.png");
	icon52->setPosition(591.5,289);
	icon52->setVisible(false);
	this->addChild(icon52);

	auto txt_x_5 = Sprite::createWithSpriteFrameName("sign_in_x.png");
	txt_x_5->setPosition(587,257.5);
	this->addChild(txt_x_5);

	auto num5 = LabelAtlas::create("2","sign_in_num.png",9,11,48);
	num5->setAnchorPoint(Point(0.5,0.5));
	num5->setPosition(595.5,257.5);
	this->addChild(num5);

	//day6
	auto currentSignBg6 = Sprite::createWithSpriteFrameName("sign_in_current_bg.png");
	currentSignBg6->setPosition(208.5,175);
	currentSignBg6->setVisible(false);
	this->addChild(currentSignBg6);

	auto hasSignBg6 = Sprite::createWithSpriteFrameName("sign_in_has_bg.png");
	hasSignBg6->setPosition(208.5,175);
	hasSignBg6->setVisible(false);
	this->addChild(hasSignBg6);

	auto hasNotSignBg6 = Sprite::createWithSpriteFrameName("sign_in_has_not_bg.png");
	hasNotSignBg6->setPosition(208.5,175);
	this->addChild(hasNotSignBg6);

	auto day6 = Sprite::createWithSpriteFrameName("sign_in_day_6.png");
	day6->setPosition(208.5,213);
	this->addChild(day6);

	auto icon61 = Sprite::createWithSpriteFrameName("sign_in_magnetic_1.png");
	icon61->setPosition(208.5,178);
	this->addChild(icon61);

	auto icon62 = Sprite::createWithSpriteFrameName("sign_in_magnetic_2.png");
	icon62->setPosition(208.5,178);
	icon62->setVisible(false);
	this->addChild(icon62);

	auto txt_x_6 = Sprite::createWithSpriteFrameName("sign_in_x.png");
	txt_x_6->setPosition(204,146.5);
	this->addChild(txt_x_6);

	auto num6 = LabelAtlas::create("2","sign_in_num.png",9,11,48);
	num6->setAnchorPoint(Point(0.5,0.5));
	num6->setPosition(212.5,146.5);
	this->addChild(num6);

	//day7
	auto currentSignBg7 = Sprite::createWithSpriteFrameName("sign_in_current_bg.png");
	currentSignBg7->setPosition(305.5,175);
	currentSignBg7->setVisible(false);
	this->addChild(currentSignBg7);

	auto hasSignBg7 = Sprite::createWithSpriteFrameName("sign_in_has_bg.png");
	hasSignBg7->setPosition(305.5,175);
	hasSignBg7->setVisible(false);
	this->addChild(hasSignBg7);

	auto hasNotSignBg7 = Sprite::createWithSpriteFrameName("sign_in_has_not_bg.png");
	hasNotSignBg7->setPosition(305.5,175);
	this->addChild(hasNotSignBg7);

	auto day7 = Sprite::createWithSpriteFrameName("sign_in_day_7.png");
	day7->setPosition(305.5,213);
	this->addChild(day7);

	auto icon71 = Sprite::createWithSpriteFrameName("sign_in_super_1.png");
	icon71->setPosition(305.5,178);
	this->addChild(icon71);

	auto icon72 = Sprite::createWithSpriteFrameName("sign_in_super_2.png");
	icon72->setPosition(305.5,178);
	icon72->setVisible(false);
	this->addChild(icon72);

	auto txt_x_7 = Sprite::createWithSpriteFrameName("sign_in_x.png");
	txt_x_7->setPosition(301,146.5);
	this->addChild(txt_x_7);

	auto num7 = LabelAtlas::create("3","sign_in_num.png",9,11,48);
	num7->setAnchorPoint(Point(0.5,0.5));
	num7->setPosition(309.5,146.5);
	this->addChild(num7);

	//day8
	auto currentSignBg8 = Sprite::createWithSpriteFrameName("sign_in_current_bg.png");
	currentSignBg8->setPosition(400.5,175);
	currentSignBg8->setVisible(false);
	this->addChild(currentSignBg8);

	auto hasSignBg8 = Sprite::createWithSpriteFrameName("sign_in_has_bg.png");
	hasSignBg8->setPosition(400.5,175);
	hasSignBg8->setVisible(false);
	this->addChild(hasSignBg8);

	auto hasNotSignBg8 = Sprite::createWithSpriteFrameName("sign_in_has_not_bg.png");
	hasNotSignBg8->setPosition(400.5,175);
	this->addChild(hasNotSignBg8);

	auto day8 = Sprite::createWithSpriteFrameName("sign_in_day_8.png");
	day8->setPosition(400.5,213);
	this->addChild(day8);

	auto icon81 = Sprite::createWithSpriteFrameName("sign_in_potential_1.png");
	icon81->setPosition(400.5,178);
	this->addChild(icon81);

	auto icon82 = Sprite::createWithSpriteFrameName("sign_in_potential_2.png");
	icon82->setPosition(400.5,178);
	icon82->setVisible(false);
	this->addChild(icon82);

	auto txt_x_8 = Sprite::createWithSpriteFrameName("sign_in_x.png");
	txt_x_8->setPosition(396,146.5);
	this->addChild(txt_x_8);

	auto num8 = LabelAtlas::create("3","sign_in_num.png",9,11,48);
	num8->setAnchorPoint(Point(0.5,0.5));
	num8->setPosition(404.5,146.5);
	this->addChild(num8);

	//day9
	auto currentSignBg9 = Sprite::createWithSpriteFrameName("sign_in_current_bg.png");
	currentSignBg9->setPosition(495.5,175);
	currentSignBg9->setVisible(false);
	this->addChild(currentSignBg9);

	auto hasSignBg9 = Sprite::createWithSpriteFrameName("sign_in_has_bg.png");
	hasSignBg9->setPosition(495.5,175);
	hasSignBg9->setVisible(false);
	this->addChild(hasSignBg9);

	auto hasNotSignBg9 = Sprite::createWithSpriteFrameName("sign_in_has_not_bg.png");
	hasNotSignBg9->setPosition(495.5,175);
	this->addChild(hasNotSignBg9);

	auto day9 = Sprite::createWithSpriteFrameName("sign_in_day_9.png");
	day9->setPosition(495.5,213);
	this->addChild(day9);

	auto icon91 = Sprite::createWithSpriteFrameName("sign_in_magnetic_1.png");
	icon91->setPosition(495.5,178);
	this->addChild(icon91);

	auto icon92 = Sprite::createWithSpriteFrameName("sign_in_magnetic_2.png");
	icon92->setPosition(495.5,178);
	icon92->setVisible(false);
	this->addChild(icon92);

	auto txt_x_9 = Sprite::createWithSpriteFrameName("sign_in_x.png");
	txt_x_9->setPosition(491,146.5);
	this->addChild(txt_x_9);

	auto num9 = LabelAtlas::create("3","sign_in_num.png",9,11,48);
	num9->setAnchorPoint(Point(0.5,0.5));
	num9->setPosition(499.5,146.5);
	this->addChild(num9);

	//day10
	auto currentSignBg10 = Sprite::createWithSpriteFrameName("sign_in_current_bg.png");
	currentSignBg10->setPosition(591.5,175);
	currentSignBg10->setVisible(false);
	this->addChild(currentSignBg10);

	auto hasSignBg10 = Sprite::createWithSpriteFrameName("sign_in_has_bg.png");
	hasSignBg10->setPosition(591.5,175);
	hasSignBg10->setVisible(false);
	this->addChild(hasSignBg10);

	auto hasNotSignBg10 = Sprite::createWithSpriteFrameName("sign_in_has_not_bg.png");
	hasNotSignBg10->setPosition(591.5,175);
	this->addChild(hasNotSignBg10);

	auto day10 = Sprite::createWithSpriteFrameName("sign_in_day_10.png");
	day10->setPosition(591.5,213);
	this->addChild(day10);

	auto icon101 = Sprite::createWithSpriteFrameName("sign_in_super_1.png");
	icon101->setPosition(591.5,178);
	this->addChild(icon101);

	auto icon102 = Sprite::createWithSpriteFrameName("sign_in_super_2.png");
	icon102->setPosition(591.5,178);
	icon102->setVisible(false);
	this->addChild(icon102);

	auto txt_x_10 = Sprite::createWithSpriteFrameName("sign_in_x.png");
	txt_x_10->setPosition(587.5,146.5);
	this->addChild(txt_x_10);

	auto num10 = LabelAtlas::create("3","sign_in_num.png",9,11,48);
	num10->setAnchorPoint(Point(0.5,0.5));
	num10->setPosition(595.5,146.5);
	this->addChild(num10);

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	
	currentSignDay = CallAndroidMethod::getInstance()->getCurrentSignDayas();
	if(currentSignDay == 0){
		currentSignBg1->setVisible(true);
		hasNotSignBg1->setVisible(false);
		hasSignBg1->setVisible(false);
		icon11->setVisible(true);
		icon12->setVisible(false);

		currentSignBg2->setVisible(false);
		hasNotSignBg2->setVisible(true);
		hasSignBg2->setVisible(false);
		icon21->setVisible(true);
		icon22->setVisible(false);

		currentSignBg3->setVisible(false);
		hasNotSignBg3->setVisible(true);
		hasSignBg3->setVisible(false);
		icon31->setVisible(true);
		icon32->setVisible(false);
		
		currentSignBg4->setVisible(false);
		hasNotSignBg4->setVisible(true);
		hasSignBg4->setVisible(false);
		icon41->setVisible(true);
		icon42->setVisible(false);

		currentSignBg5->setVisible(false);
		hasNotSignBg5->setVisible(true);
		hasSignBg5->setVisible(false);
		icon51->setVisible(true);
		icon52->setVisible(false);
		
		currentSignBg6->setVisible(false);
		hasNotSignBg6->setVisible(true);
		hasSignBg6->setVisible(false);
		icon61->setVisible(true);
		icon62->setVisible(false);
		
		currentSignBg7->setVisible(false);
		hasNotSignBg7->setVisible(true);
		hasSignBg7->setVisible(false);
		icon71->setVisible(true);
		icon72->setVisible(false);
		
		currentSignBg8->setVisible(false);
		hasNotSignBg8->setVisible(true);
		hasSignBg8->setVisible(false);
		icon81->setVisible(true);
		icon82->setVisible(false);
		
		currentSignBg9->setVisible(false);
		hasNotSignBg9->setVisible(true);
		hasSignBg9->setVisible(false);
		icon91->setVisible(true);
		icon92->setVisible(false);
		
		currentSignBg10->setVisible(false);
		hasNotSignBg10->setVisible(true);
		hasSignBg10->setVisible(false);
		icon101->setVisible(true);
		icon102->setVisible(false);
	}else if(currentSignDay == 1){
		currentSignBg1->setVisible(false);
		hasNotSignBg1->setVisible(false);
		hasSignBg1->setVisible(true);
		icon11->setVisible(false);
		icon12->setVisible(true);

		currentSignBg2->setVisible(true);
		hasNotSignBg2->setVisible(false);
		hasSignBg2->setVisible(false);
		icon21->setVisible(true);
		icon22->setVisible(false);

		currentSignBg3->setVisible(false);
		hasNotSignBg3->setVisible(true);
		hasSignBg3->setVisible(false);
		icon31->setVisible(true);
		icon32->setVisible(false);
		
		currentSignBg4->setVisible(false);
		hasNotSignBg4->setVisible(true);
		hasSignBg4->setVisible(false);
		icon41->setVisible(true);
		icon42->setVisible(false);

		currentSignBg5->setVisible(false);
		hasNotSignBg5->setVisible(true);
		hasSignBg5->setVisible(false);
		icon51->setVisible(true);
		icon52->setVisible(false);
		
		currentSignBg6->setVisible(false);
		hasNotSignBg6->setVisible(true);
		hasSignBg6->setVisible(false);
		icon61->setVisible(true);
		icon62->setVisible(false);
		
		currentSignBg7->setVisible(false);
		hasNotSignBg7->setVisible(true);
		hasSignBg7->setVisible(false);
		icon71->setVisible(true);
		icon72->setVisible(false);
		
		currentSignBg8->setVisible(false);
		hasNotSignBg8->setVisible(true);
		hasSignBg8->setVisible(false);
		icon81->setVisible(true);
		icon82->setVisible(false);
		
		currentSignBg9->setVisible(false);
		hasNotSignBg9->setVisible(true);
		hasSignBg9->setVisible(false);
		icon91->setVisible(true);
		icon92->setVisible(false);
		
		currentSignBg10->setVisible(false);
		hasNotSignBg10->setVisible(true);
		hasSignBg10->setVisible(false);
		icon101->setVisible(true);
		icon102->setVisible(false);
	}else if(currentSignDay == 2){
		currentSignBg1->setVisible(false);
		hasNotSignBg1->setVisible(false);
		hasSignBg1->setVisible(true);
		icon11->setVisible(false);
		icon12->setVisible(true);

		currentSignBg2->setVisible(false);
		hasNotSignBg2->setVisible(false);
		hasSignBg2->setVisible(true);
		icon21->setVisible(false);
		icon22->setVisible(true);

		currentSignBg3->setVisible(true);
		hasNotSignBg3->setVisible(false);
		hasSignBg3->setVisible(false);
		icon31->setVisible(true);
		icon32->setVisible(false);
		
		currentSignBg4->setVisible(false);
		hasNotSignBg4->setVisible(true);
		hasSignBg4->setVisible(false);
		icon41->setVisible(true);
		icon42->setVisible(false);

		currentSignBg5->setVisible(false);
		hasNotSignBg5->setVisible(true);
		hasSignBg5->setVisible(false);
		icon51->setVisible(true);
		icon52->setVisible(false);
		
		currentSignBg6->setVisible(false);
		hasNotSignBg6->setVisible(true);
		hasSignBg6->setVisible(false);
		icon61->setVisible(true);
		icon62->setVisible(false);
		
		currentSignBg7->setVisible(false);
		hasNotSignBg7->setVisible(true);
		hasSignBg7->setVisible(false);
		icon71->setVisible(true);
		icon72->setVisible(false);
		
		currentSignBg8->setVisible(false);
		hasNotSignBg8->setVisible(true);
		hasSignBg8->setVisible(false);
		icon81->setVisible(true);
		icon82->setVisible(false);
		
		currentSignBg9->setVisible(false);
		hasNotSignBg9->setVisible(true);
		hasSignBg9->setVisible(false);
		icon91->setVisible(true);
		icon92->setVisible(false);
		
		currentSignBg10->setVisible(false);
		hasNotSignBg10->setVisible(true);
		hasSignBg10->setVisible(false);
		icon101->setVisible(true);
		icon102->setVisible(false);
	}else if(currentSignDay == 3){
		currentSignBg1->setVisible(false);
		hasNotSignBg1->setVisible(false);
		hasSignBg1->setVisible(true);
		icon11->setVisible(false);
		icon12->setVisible(true);

		currentSignBg2->setVisible(false);
		hasNotSignBg2->setVisible(false);
		hasSignBg2->setVisible(true);
		icon21->setVisible(false);
		icon22->setVisible(true);

		currentSignBg3->setVisible(false);
		hasNotSignBg3->setVisible(false);
		hasSignBg3->setVisible(true);
		icon31->setVisible(false);
		icon32->setVisible(true);
		
		currentSignBg4->setVisible(true);
		hasNotSignBg4->setVisible(false);
		hasSignBg4->setVisible(false);
		icon41->setVisible(true);
		icon42->setVisible(false);

		currentSignBg5->setVisible(false);
		hasNotSignBg5->setVisible(true);
		hasSignBg5->setVisible(false);
		icon51->setVisible(true);
		icon52->setVisible(false);
		
		currentSignBg6->setVisible(false);
		hasNotSignBg6->setVisible(true);
		hasSignBg6->setVisible(false);
		icon61->setVisible(true);
		icon62->setVisible(false);
		
		currentSignBg7->setVisible(false);
		hasNotSignBg7->setVisible(true);
		hasSignBg7->setVisible(false);
		icon71->setVisible(true);
		icon72->setVisible(false);
		
		currentSignBg8->setVisible(false);
		hasNotSignBg8->setVisible(true);
		hasSignBg8->setVisible(false);
		icon81->setVisible(true);
		icon82->setVisible(false);
		
		currentSignBg9->setVisible(false);
		hasNotSignBg9->setVisible(true);
		hasSignBg9->setVisible(false);
		icon91->setVisible(true);
		icon92->setVisible(false);
		
		currentSignBg10->setVisible(false);
		hasNotSignBg10->setVisible(true);
		hasSignBg10->setVisible(false);
		icon101->setVisible(true);
		icon102->setVisible(false);
	}else if(currentSignDay == 4){
		currentSignBg1->setVisible(false);
		hasNotSignBg1->setVisible(false);
		hasSignBg1->setVisible(true);
		icon11->setVisible(false);
		icon12->setVisible(true);

		currentSignBg2->setVisible(false);
		hasNotSignBg2->setVisible(false);
		hasSignBg2->setVisible(true);
		icon21->setVisible(false);
		icon22->setVisible(true);

		currentSignBg3->setVisible(false);
		hasNotSignBg3->setVisible(false);
		hasSignBg3->setVisible(true);
		icon31->setVisible(false);
		icon32->setVisible(true);
		
		currentSignBg4->setVisible(false);
		hasNotSignBg4->setVisible(false);
		hasSignBg4->setVisible(true);
		icon41->setVisible(false);
		icon42->setVisible(true);

		currentSignBg5->setVisible(true);
		hasNotSignBg5->setVisible(false);
		hasSignBg5->setVisible(false);
		icon51->setVisible(true);
		icon52->setVisible(false);
		
		currentSignBg6->setVisible(false);
		hasNotSignBg6->setVisible(true);
		hasSignBg6->setVisible(false);
		icon61->setVisible(true);
		icon62->setVisible(false);
		
		currentSignBg7->setVisible(false);
		hasNotSignBg7->setVisible(true);
		hasSignBg7->setVisible(false);
		icon71->setVisible(true);
		icon72->setVisible(false);
		
		currentSignBg8->setVisible(false);
		hasNotSignBg8->setVisible(true);
		hasSignBg8->setVisible(false);
		icon81->setVisible(true);
		icon82->setVisible(false);
		
		currentSignBg9->setVisible(false);
		hasNotSignBg9->setVisible(true);
		hasSignBg9->setVisible(false);
		icon91->setVisible(true);
		icon92->setVisible(false);
		
		currentSignBg10->setVisible(false);
		hasNotSignBg10->setVisible(true);
		hasSignBg10->setVisible(false);
		icon101->setVisible(true);
		icon102->setVisible(false);
	}else if(currentSignDay == 5){
		currentSignBg1->setVisible(false);
		hasNotSignBg1->setVisible(false);
		hasSignBg1->setVisible(true);
		icon11->setVisible(false);
		icon12->setVisible(true);

		currentSignBg2->setVisible(false);
		hasNotSignBg2->setVisible(false);
		hasSignBg2->setVisible(true);
		icon21->setVisible(false);
		icon22->setVisible(true);

		currentSignBg3->setVisible(false);
		hasNotSignBg3->setVisible(false);
		hasSignBg3->setVisible(true);
		icon31->setVisible(false);
		icon32->setVisible(true);
		
		currentSignBg4->setVisible(false);
		hasNotSignBg4->setVisible(false);
		hasSignBg4->setVisible(true);
		icon41->setVisible(false);
		icon42->setVisible(true);

		currentSignBg5->setVisible(false);
		hasNotSignBg5->setVisible(false);
		hasSignBg5->setVisible(true);
		icon51->setVisible(false);
		icon52->setVisible(true);
		
		currentSignBg6->setVisible(true);
		hasNotSignBg6->setVisible(false);
		hasSignBg6->setVisible(false);
		icon61->setVisible(true);
		icon62->setVisible(false);
		
		currentSignBg7->setVisible(false);
		hasNotSignBg7->setVisible(true);
		hasSignBg7->setVisible(false);
		icon71->setVisible(true);
		icon72->setVisible(false);
		
		currentSignBg8->setVisible(false);
		hasNotSignBg8->setVisible(true);
		hasSignBg8->setVisible(false);
		icon81->setVisible(true);
		icon82->setVisible(false);
		
		currentSignBg9->setVisible(false);
		hasNotSignBg9->setVisible(true);
		hasSignBg9->setVisible(false);
		icon91->setVisible(true);
		icon92->setVisible(false);
		
		currentSignBg10->setVisible(false);
		hasNotSignBg10->setVisible(true);
		hasSignBg10->setVisible(false);
		icon101->setVisible(true);
		icon102->setVisible(false);
	}else if(currentSignDay == 6){
		currentSignBg1->setVisible(false);
		hasNotSignBg1->setVisible(false);
		hasSignBg1->setVisible(true);
		icon11->setVisible(false);
		icon12->setVisible(true);

		currentSignBg2->setVisible(false);
		hasNotSignBg2->setVisible(false);
		hasSignBg2->setVisible(true);
		icon21->setVisible(false);
		icon22->setVisible(true);

		currentSignBg3->setVisible(false);
		hasNotSignBg3->setVisible(false);
		hasSignBg3->setVisible(true);
		icon31->setVisible(false);
		icon32->setVisible(true);
		
		currentSignBg4->setVisible(false);
		hasNotSignBg4->setVisible(false);
		hasSignBg4->setVisible(true);
		icon41->setVisible(false);
		icon42->setVisible(true);

		currentSignBg5->setVisible(false);
		hasNotSignBg5->setVisible(false);
		hasSignBg5->setVisible(true);
		icon51->setVisible(false);
		icon52->setVisible(true);
		
		currentSignBg6->setVisible(false);
		hasNotSignBg6->setVisible(false);
		hasSignBg6->setVisible(true);
		icon61->setVisible(false);
		icon62->setVisible(true);
		
		currentSignBg7->setVisible(true);
		hasNotSignBg7->setVisible(false);
		hasSignBg7->setVisible(false);
		icon71->setVisible(true);
		icon72->setVisible(false);
		
		currentSignBg8->setVisible(false);
		hasNotSignBg8->setVisible(true);
		hasSignBg8->setVisible(false);
		icon81->setVisible(true);
		icon82->setVisible(false);
		
		currentSignBg9->setVisible(false);
		hasNotSignBg9->setVisible(true);
		hasSignBg9->setVisible(false);
		icon91->setVisible(true);
		icon92->setVisible(false);
		
		currentSignBg10->setVisible(false);
		hasNotSignBg10->setVisible(true);
		hasSignBg10->setVisible(false);
		icon101->setVisible(true);
		icon102->setVisible(false);
	}else if(currentSignDay == 7){
		currentSignBg1->setVisible(false);
		hasNotSignBg1->setVisible(false);
		hasSignBg1->setVisible(true);
		icon11->setVisible(false);
		icon12->setVisible(true);

		currentSignBg2->setVisible(false);
		hasNotSignBg2->setVisible(false);
		hasSignBg2->setVisible(true);
		icon21->setVisible(false);
		icon22->setVisible(true);

		currentSignBg3->setVisible(false);
		hasNotSignBg3->setVisible(false);
		hasSignBg3->setVisible(true);
		icon31->setVisible(false);
		icon32->setVisible(true);
		
		currentSignBg4->setVisible(false);
		hasNotSignBg4->setVisible(false);
		hasSignBg4->setVisible(true);
		icon41->setVisible(false);
		icon42->setVisible(true);

		currentSignBg5->setVisible(false);
		hasNotSignBg5->setVisible(false);
		hasSignBg5->setVisible(true);
		icon51->setVisible(false);
		icon52->setVisible(true);
		
		currentSignBg6->setVisible(false);
		hasNotSignBg6->setVisible(false);
		hasSignBg6->setVisible(true);
		icon61->setVisible(false);
		icon62->setVisible(true);
		
		currentSignBg7->setVisible(false);
		hasNotSignBg7->setVisible(false);
		hasSignBg7->setVisible(true);
		icon71->setVisible(false);
		icon72->setVisible(true);
		
		currentSignBg8->setVisible(true);
		hasNotSignBg8->setVisible(false);
		hasSignBg8->setVisible(false);
		icon81->setVisible(true);
		icon82->setVisible(false);
		
		currentSignBg9->setVisible(false);
		hasNotSignBg9->setVisible(true);
		hasSignBg9->setVisible(false);
		icon91->setVisible(true);
		icon92->setVisible(false);
		
		currentSignBg10->setVisible(false);
		hasNotSignBg10->setVisible(true);
		hasSignBg10->setVisible(false);
		icon101->setVisible(true);
		icon102->setVisible(false);
	}else if(currentSignDay == 8){
		currentSignBg1->setVisible(false);
		hasNotSignBg1->setVisible(false);
		hasSignBg1->setVisible(true);
		icon11->setVisible(false);
		icon12->setVisible(true);

		currentSignBg2->setVisible(false);
		hasNotSignBg2->setVisible(false);
		hasSignBg2->setVisible(true);
		icon21->setVisible(false);
		icon22->setVisible(true);

		currentSignBg3->setVisible(false);
		hasNotSignBg3->setVisible(false);
		hasSignBg3->setVisible(true);
		icon31->setVisible(false);
		icon32->setVisible(true);
		
		currentSignBg4->setVisible(false);
		hasNotSignBg4->setVisible(false);
		hasSignBg4->setVisible(true);
		icon41->setVisible(false);
		icon42->setVisible(true);

		currentSignBg5->setVisible(false);
		hasNotSignBg5->setVisible(false);
		hasSignBg5->setVisible(true);
		icon51->setVisible(false);
		icon52->setVisible(true);
		
		currentSignBg6->setVisible(false);
		hasNotSignBg6->setVisible(false);
		hasSignBg6->setVisible(true);
		icon61->setVisible(false);
		icon62->setVisible(true);
		
		currentSignBg7->setVisible(false);
		hasNotSignBg7->setVisible(false);
		hasSignBg7->setVisible(true);
		icon71->setVisible(false);
		icon72->setVisible(true);
		
		currentSignBg8->setVisible(false);
		hasNotSignBg8->setVisible(false);
		hasSignBg8->setVisible(true);
		icon81->setVisible(false);
		icon82->setVisible(true);
		
		currentSignBg9->setVisible(true);
		hasNotSignBg9->setVisible(false);
		hasSignBg9->setVisible(false);
		icon91->setVisible(true);
		icon92->setVisible(false);
		
		currentSignBg10->setVisible(false);
		hasNotSignBg10->setVisible(true);
		hasSignBg10->setVisible(false);
		icon101->setVisible(true);
		icon102->setVisible(false);
	}else if(currentSignDay == 9){
		currentSignBg1->setVisible(false);
		hasNotSignBg1->setVisible(false);
		hasSignBg1->setVisible(true);
		icon11->setVisible(false);
		icon12->setVisible(true);

		currentSignBg2->setVisible(false);
		hasNotSignBg2->setVisible(false);
		hasSignBg2->setVisible(true);
		icon21->setVisible(false);
		icon22->setVisible(true);

		currentSignBg3->setVisible(false);
		hasNotSignBg3->setVisible(false);
		hasSignBg3->setVisible(true);
		icon31->setVisible(false);
		icon32->setVisible(true);
		
		currentSignBg4->setVisible(false);
		hasNotSignBg4->setVisible(false);
		hasSignBg4->setVisible(true);
		icon41->setVisible(false);
		icon42->setVisible(true);

		currentSignBg5->setVisible(false);
		hasNotSignBg5->setVisible(false);
		hasSignBg5->setVisible(true);
		icon51->setVisible(false);
		icon52->setVisible(true);
		
		currentSignBg6->setVisible(false);
		hasNotSignBg6->setVisible(false);
		hasSignBg6->setVisible(true);
		icon61->setVisible(false);
		icon62->setVisible(true);
		
		currentSignBg7->setVisible(false);
		hasNotSignBg7->setVisible(false);
		hasSignBg7->setVisible(true);
		icon71->setVisible(false);
		icon72->setVisible(true);
		
		currentSignBg8->setVisible(false);
		hasNotSignBg8->setVisible(false);
		hasSignBg8->setVisible(true);
		icon81->setVisible(false);
		icon82->setVisible(true);
		
		currentSignBg9->setVisible(false);
		hasNotSignBg9->setVisible(false);
		hasSignBg9->setVisible(true);
		icon91->setVisible(false);
		icon92->setVisible(true);
		
		currentSignBg10->setVisible(true);
		hasNotSignBg10->setVisible(false);
		hasSignBg10->setVisible(false);
		icon101->setVisible(true);
		icon102->setVisible(false);
	}
	#endif

	auto confirmBtn = MenuItemImage::create(
		"dialog_conti_game_bg_normal.png",
		"dialog_conti_game_bg_click.png",
		CC_CALLBACK_0(SignIn::signIn, this));
	auto confirmMenu = Menu::create(confirmBtn, NULL);
	confirmMenu->setPosition(400,84);
	this->addChild(confirmMenu);
	
	auto confirmTxt = MenuItemImage::create(
		"sign_in_confirm_normal_txt.png",
		"sign_in_confirm_click_txt.png",
		CC_CALLBACK_0(SignIn::signIn, this));
	auto confirmTxtMenu = Menu::create(confirmTxt, NULL);
	confirmTxtMenu->setPosition(400,84);
	this->addChild(confirmTxtMenu);

	return true;
}

void SignIn::signIn(){
	Audio::getInstance()->playSound("Music/paddle_hit.wav");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)		
	CallAndroidMethod::getInstance()->sign();
	switch(currentSignDay){
	case 0:
		GAMEDATA::getInstance()->setPotentialPropNum(GAMEDATA::getInstance()->getPotentialPropNum()+1);
		break;
	case 1:
		GAMEDATA::getInstance()->setSuperPropNum(GAMEDATA::getInstance()->getSuperPropNum()+1);
		break;
	case 2:
		GAMEDATA::getInstance()->setMagneticPropNum(GAMEDATA::getInstance()->getMagneticPropNum()+1);
		break;
	case 3:
		GAMEDATA::getInstance()->setPotentialPropNum(GAMEDATA::getInstance()->getPotentialPropNum()+2);
		break;
	case 4:
		GAMEDATA::getInstance()->setSuperPropNum(GAMEDATA::getInstance()->getSuperPropNum()+2);
		break;
	case 5:
		GAMEDATA::getInstance()->setMagneticPropNum(GAMEDATA::getInstance()->getMagneticPropNum()+2);
		break;
	case 6:
		GAMEDATA::getInstance()->setPotentialPropNum(GAMEDATA::getInstance()->getPotentialPropNum()+3);
		break;
	case 7:
		GAMEDATA::getInstance()->setSuperPropNum(GAMEDATA::getInstance()->getSuperPropNum()+3);
		break;
	case 8:
		GAMEDATA::getInstance()->setMagneticPropNum(GAMEDATA::getInstance()->getMagneticPropNum()+3);
		break;
	case 9:
		GAMEDATA::getInstance()->setPotentialPropNum(GAMEDATA::getInstance()->getPotentialPropNum()+3);
		break;
	}
	#endif
	this->setVisible(false);
	MenuLayer::showSignInPrize = true;
}
