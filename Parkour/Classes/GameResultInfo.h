#ifndef _GAMERESULTINFO_H_
#define _GAMERESULTINFO_H_

class GameResultInfo{
public:
	static GameResultInfo* getInstance();
	void setGameResult(int game_result);
	int getGameResult();
private:
	GameResultInfo();
	void init();
	int gameResult;
	static GameResultInfo* _instance;
};
#endif
