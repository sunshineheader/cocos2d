#ifndef GameSlioder_H
#define  GameSlioder_H


#include "cocos2d.h"
class GameSlioder :public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameSlioder);
	float get_currcert_postion_x();
	void updateTimeProgress(float time, float totalTime);

private:
	cocos2d:: Size visibleSize;
	cocos2d:: Vec2 origin;
	cocos2d:: Sprite*time_progress_icon;
	cocos2d:: Sprite*time_progress_bg;
	cocos2d::ProgressTimer *time_out;
};
#endif

