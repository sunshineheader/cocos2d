#ifndef GameLayerScene_H
#define GameLayerScene_H
#include "cocos2d.h"
#include "GameCountLabel.h"
using namespace cocos2d;


class GameLayer :public cocos2d::Layer{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);
	//void update(float dt);
	void startGame();
	CREATE_FUNC(GameLayer);
	virtual bool onTouchBegan(cocos2d::Touch*touch, cocos2d::Event* event);
	void addNewBlock();
	void addYellowBlock();
	void EveryThreeCallBack();
	void EveryTwoCallBack();
	void RebornCallBack(int index);
	int tag;
	int  currcert_tag ;
	
	void reStartGame(float dt);
	void gameFail(float dt);
private:
	GameCountLabel*mylabel;
	Vector<Sprite*> sprite_vec;
	cocos2d::Label*count_label;
	cocos2d::Sprite* block;
	cocos2d::Sprite* gary;
	cocos2d::Sprite* red;
	cocos2d::Sprite* s;
	int currentClick_count;//记录当前点击模块在序列中的位置
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;;
	Label* start;
	MenuItemLabel* start_game_item;
	Texture2D*white_texture;
	Texture2D*black_texture;
	Texture2D*gray_texture;
	Texture2D*red_texture;
	Texture2D*yellow_texture;
	int pos_x;
	int pos_y;
	int layer_speed;
	float distance;
	float layer_position_y;
	int game_counts;
	int error_nbumer;
	float add_new;
	float mytime;
	float newspeed;
	int index;
	int countVar;
	int  currcert_speed;
	float back_posititon_y;

	//s=vt
	float v;
	float t;
	float l;
	float length;
	int myTag;
	//float positionX=0;
	bool  PauseGame = false;
	bool startPlayGame = false;
	int  startTag = 1;

};

#endif