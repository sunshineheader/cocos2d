#ifndef GameOverLabel_H
#define GameOverLabel_H
#include "cocos2d.h"

class GameOverLabel :public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameOverLabel);
	void game_again_callback(cocos2d::Ref* psender);
	void game_back_callback(cocos2d::Ref* psender);
private:
	int best_sorce = 0;
	int currcert_sorce = 0;
};
#endif