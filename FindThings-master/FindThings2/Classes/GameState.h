#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

class GAMESTATE{
public:
	static GAMESTATE* getInstance();
	void reset();
	void setGamePause(bool pause);
	bool getGamePause();
	void setGameOver(bool over);
	bool getGameOver();
	bool isUsePropFind();
	void setUsePropFind(bool b);
	bool isUsePropTime();
	void setUsePropTime(bool b);
	bool getIsPaying();
	void setIsPaying(bool b);
	bool getIsRevive();
	void setIsRevive(bool b);
	bool getIsShowPayTime();
	void setIsShowPayTime(bool b);
	bool getIsShowPayFind();
	void setIsShowPayFind(bool b);
	bool getIsFirstTask();
	void setIsFirstTask(bool b);
	bool getIsGuide();
	void setIsGuide(bool b);
	bool getIsCreateGuideTask();
	void setIsCreateGuideTask(bool b);
	bool getIsShowMoreGame();
	void setIsShowMoreGame(bool b);
private:
	GAMESTATE();
	void init();
	static GAMESTATE* _instance;
	bool gamePause;
	bool gameOver;
	bool isUseFind;
	bool isUseTime;
	bool isRevive;
	bool isPaying;//是否已经在支付
	bool isShowPayTime;//本局是否已经弹出过加时计费点
	bool isShowPayFind;//本局是否已经弹出过查找计费点
	bool isFirstTask;//是否是第一次做任务
	bool isGuide;
	bool isCreate;
	bool isShowMoreGame;
};
#endif