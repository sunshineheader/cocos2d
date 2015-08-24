#ifndef GameData_H
#define GameData_H

class GameData{
public:
	GameData();
	~GameData();
	static GameData* getInstance();
	void initData();

	inline void set_currcert_sorce(int sorce){ this->currcert_sorce = sorce; };
	inline int get_currcert_sorce(){ return this->currcert_sorce; };

	void setBestSorce(int value);
	int getBestSorce();
	void set_is_first_login(bool value);
	bool get_is_first_login();
	void set_error_number(int err);
	int get_error_number();
	void set_currcert_life(int life);
	int get_currcert_life();
	void set_xiao_guo(bool ishave);
	bool get_xiao_guo();



public:
	static GameData* data_instance;
	int currcert_sorce;
	int currcert_speed;
	//new add 
	bool reStart;
	bool gotoResult;
	int gameTimes = 0;//记录游戏第几局了
};

#endif