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
private:
	GAMESTATE();
	void init();
	static GAMESTATE* _instance;
	bool gamePause;
	bool gameOver;
};
#endif