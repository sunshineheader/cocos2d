#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include "cocos2d.h"
USING_NS_CC;

class Monster;

class GameLayer: public cocos2d::Layer{
public:
	GameLayer();
	~GameLayer();
	virtual bool init();
	CREATE_FUNC(GameLayer);
	virtual void update(float dt);
	virtual bool onTouchBegan(Touch *touch, Event *unused);
	virtual void onTouchMoved(Touch *touch, Event *unused);
private:
	Monster **m_matrix;// 2D array which store (Monster *).
	int m_width;
	int m_height;
	// for rapid count position
	float m_matrixLeftBottomX;
	float m_matrixLeftBottomY;
	bool m_isTouchEnable;// is need to deal with touch event
	Monster *m_srcMonster;// 用户移动的怪物
	Monster *m_destMonster;// 移动到哪个怪物
	bool m_isAnimationing;
	bool m_isNeedFillVacancies;//是否有空缺需要填补
	bool m_movingVertical;// true: 4消除产生纵向炸弹.  false: 4消除产生横向炸弹.

	void initMatrix();
	void createAndDropMonster(int row, int col);
	Point positionOfItem(int row, int col);
	void checkAndRemoveChain();
	void getColChain(Monster *monster, std::list<Monster *> &chainList);
	void getRowChain(Monster *monster, std::list<Monster *> &chainList);
	void removeMonster();
	void actionEndCallback(Node *node);
	void explodeMonster(Monster *monster);

	void fillVacancies();
	Monster *monsterOfPoint(Point *point);
	void swapMonster();
	void markRemove(Monster *monster);
	void calculateScore(int number);

	int countRemoveMonster = 0;
};
#endif