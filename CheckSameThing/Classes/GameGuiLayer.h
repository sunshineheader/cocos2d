#ifndef __GAME_GUI_LAYER_H__
#define __GAME_GUI_LAYER_H__
#include "cocos2d.h"
#define wSize Director::getInstance()->getVisibleSize()
USING_NS_CC;

class GameGuiLayer : public Node{
public:
	static GameGuiLayer*getInstance();
	virtual bool init();
	CREATE_FUNC(GameGuiLayer);
	static bool addTime;
	static bool help;
	static bool refresh;

	void updateScore();
	//static const int Map_1[];
private:
	static GameGuiLayer*_instance;
	void pauseGame();
	void update(float dt);
	void gotoResult();
	void addTimeBtn();
	void helpTip();
	void refreshBtn();
	Sprite* notime;
	LabelTTF*label;
	LabelTTF*label1;
	LabelTTF*label2;
	CCLabelAtlas* Ascore;

	
};
#endif