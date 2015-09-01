#pragma once
#include "cocos2d.h"
USING_NS_CC;
class InfoLayer :public Layer
{
public:
	bool init();
	CREATE_FUNC(InfoLayer);
	void goldAddOne();
	void distanceAddOne();
	int getGoldNum();
	int getDisNum();
	void refreshProgress(int potentialGoldNum,int potentialIndex);
	void refreshMission();
private:
	int m_distance;
	int m_goldNum;
	LabelAtlas *ttf_gold;
	LabelAtlas *ttf_distance;
	LabelBMFont* missionProgress;
	Sprite* progress;
private:
};