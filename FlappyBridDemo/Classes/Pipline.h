#pragma once
#include "cocos2d.h"
#include "GameData.h"
using namespace cocos2d;

class Pipline :public Sprite 
{
public:
	enum PiplineState
	{
		Top = 0,
		Down
	};
public:
	static Pipline* create(const std::string & file);
	virtual bool init();
	void setNextPosition();
	void setPhysicsConfiger();
	void update(float dt);
	bool Pipline::checkWidthBorder(float x);
	//void setPiplineStatePosition();
	void setPiplineState(int state);
	int  getPiplineState();
public:
	static Vector<Pipline*> piplineList;
	void pushbackToList();
	void removeFromList();
private:
	Size visibleSize;
	Vec2 origin;
	int m_state;
	int distance;
	int dy;
};