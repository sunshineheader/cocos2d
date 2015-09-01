#ifndef _RESULTGOLD_H_
#define _RESULTGOLD_H_
#include <string>
#include "cocos2d.h"
using namespace cocos2d;
class ResultGold : public Node{
public:
	static ResultGold* getInstance();
	static void cleanInstance();
	virtual bool init();
	void refreshGold();
	void refreshMagenicInfo();
	void refreshSuperInfo();
	void refreshPotentialInfo();
	void refreshPlayerLevel();
	void upgradeSuper();
	void upgradeMagenic();
	void upgradePotential();
	void refreshPropNum();
	static bool clickedUpgradeProp;
private:
	static ResultGold* _instance;
	LabelAtlas* playerGold;
	LabelAtlas* magneticUpgradeGold;
	LabelAtlas* magneticTime1;
	LabelAtlas* superUpgradeGold;
	LabelAtlas* superTime1;
	LabelAtlas* potentialUpgradeGold;
	LabelAtlas* potentialTime1;
	LabelAtlas* levelNum;
	Sprite* magneticProgress;
	Sprite* superProgress;
	Sprite* potentialProgress;
	LabelAtlas* prop_sup_num;
	LabelAtlas* prop_mag_num;
	LabelAtlas* prop_pot_num;
private:
	ResultGold();
};
#endif
