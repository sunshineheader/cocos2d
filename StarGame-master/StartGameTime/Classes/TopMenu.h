#ifndef _TOPMENU_H_
#define _TOPMENU_H_
#include <string>
#include "cocos2d.h"
#include "FloatWord.h"
using namespace cocos2d;
class TopMenu : public Node{
public:
	static TopMenu* getInstance();
	virtual bool init();
	CREATE_FUNC(TopMenu);
	void refresh(int score);
	void usePropsBomb();
	void usePropsTime();
	void PauseGame();
	void updatePropsNum();
	void stopScaleAction();
	void cleanScore();
	void refreshGold();
	void pay();
private:
	static TopMenu* _instance;
	Label* highestScore;
	Label* curScore;
	Layer* gamePause;
	Label* propBombNum;
	Label* propTimeNum;
	Label* playerGold;
	MenuItemImage* BombBtn;
	MenuItemImage* TimeBtn;
	FloatWord* plusTimeWord;
private:
	TopMenu();

};
#endif
