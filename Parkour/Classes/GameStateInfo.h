#ifndef _GAMESTATEINFO_H_
#define _GAMESTATEINFO_H_

class GameStateInfo{
public:
	static GameStateInfo* getInstance();
	void setGameState(int state);
	int getGameState();
private:
	GameStateInfo();
	void init();
	int state;
	static GameStateInfo* _instance;
};
#endif
