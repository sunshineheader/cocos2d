#ifndef GameCountLabel_H
#define GameCountLabel_H
#include "cocos2d.h"

class GameCountLabel :public cocos2d::Layer{
public:
	virtual bool init();
	static GameCountLabel*getInstance();
	CREATE_FUNC(GameCountLabel);
	void update(float dt);
public:
	 cocos2d::Label*count_label;
	 int game_counts=0;
	 static GameCountLabel*_instance;
};
#endif