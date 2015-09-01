#ifndef _GAMEOVERLAYER_H_
#define _GAMEOVERLAYER_H_

#include "cocos2d.h"
#include "Upgrade.h"

using namespace cocos2d;

class GameOverLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameOverLayer);
	void update(float delta);
	void continueGame();
	void back();
	void getSoudState(CCObject* pSender);
	void getMusicState(CCObject* pSender);
	GameOverLayer getInstance();
private:
	float scoreNum;
	float animTime;
	int curScore;
	int rankNumTemp;
	float rotation;
	bool hasShowUpgrade;
	bool canClick;
	bool hasShowBeat;
	bool hasShowPrizeGold;
	bool hasShowHappy;
	bool hasPlaySound;
	bool hasShowScore;
	bool hasShowBtn;
	Node* upgrade;
	MenuItemImage* startBtn;
	Menu* startMenu;
	Menu* backMenu;
	MenuItemImage* musicBtnOn;
	MenuItemImage* musicBtnOff;
	MenuItemImage* soundEffectOn;
	MenuItemImage* soundEffectOff;
	LabelAtlas* labelScore;
	LabelAtlas* beatNum;
	Sprite* beatDesc1;
	Sprite* beatDesc2;
	Sprite* beatPerTxt;
	LabelAtlas* prizeGold;
	LabelAtlas* happyNum1;
	LabelAtlas* happyNum2;
	Sprite* goldIcon;
	Sprite* happy1;
	Sprite* happy2;
	Sprite* happyPoint;
	Sprite* addScoreTxt;
	LabelAtlas* addScore;
	int addScoreNum;

};
#endif
