#include "GameSlioder.h"
USING_NS_CC;



bool GameSlioder::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	time_progress_bg = Sprite::create("time_progress_bg.png");
	time_progress_bg->setPosition(visibleSize.width/2,visibleSize.height-90);
	addChild(time_progress_bg,-1);

	time_progress_icon = Sprite::create("time_progress_icon.png");
	time_out = ProgressTimer::create(time_progress_icon);
	time_out->setType(ProgressTimerType::BAR);
	time_out->setMidpoint(Vec2(0,0));
	time_out->setBarChangeRate(Vec2(1,0));
	time_out->setPosition(visibleSize.width/2,visibleSize.height-91);
	addChild(time_out,100);
	time_out->setPercentage(100.0f);
	return true;
}


float GameSlioder::get_currcert_postion_x()
{
	return time_progress_icon->getPosition().x;
}

void GameSlioder::updateTimeProgress(float time,float totalTime){
	time_out->setPercentage(time / totalTime*100);
}

