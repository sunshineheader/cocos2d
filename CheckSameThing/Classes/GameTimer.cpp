#include "GameTimer.h"
#include"GameData.h"
#include"GameGuiLayer.h"
GameTimer::GameTimer()
{

}

GameTimer::~GameTimer()
{

}
int m, s;
bool GameTimer::init(float time)
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	label = CCLabelTTF::create();
	ccColor3B color;
	color.r = 240;
	color.g = 255;
	color.b = 255;
	label->setColor(color);
	label->setScale(1.5);

	label->setPosition(240, origin.y + visibleSize.height / 2 + 260);

	this->addChild(label);

	schedule(schedule_selector(GameTimer::update));

	return true;
}
void GameTimer::update(float delta)
{
	if (GAMEDATA::getInstance()->getstate()==1)
		return;
	GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() - delta);
	//CCLOG("%f", GAMEDATA::getInstance()->gettime());
	char* mtime = new char[100];
	//此处只是显示分钟数和秒数  自己可以定义输出时间格式
	//sprintf(mtime, "%d : %d", (int)pTime / 60, (int)pTime % 60);
	s = (int)(GAMEDATA::getInstance()->gettime()+1 )% 60;
	m = (int)GAMEDATA::getInstance()->gettime() / 60;
	if (s < 0){
		s = 00;
	}
	if (m < 0){
		m = 00;
	}
	sprintf(mtime, "%.2d : %.2d", m, s);
	//itoa(0, mtime, 100);
	label->setString(mtime);
}

GameTimer* GameTimer::createTimer(float time)
{
	GameTimer* gametimer = new GameTimer;
	if (gametimer && gametimer->init(time))
	{
		gametimer->autorelease();
		return gametimer;
	}
	else
	{
		delete gametimer;
		gametimer = NULL;
	}
	return NULL;
}