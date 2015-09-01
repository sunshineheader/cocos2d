#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include "cocos2d.h"
#include "Matrix.h"

USING_NS_CC;

class GameLayer : public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	int  MARGIN_BOTTOM;
	const static int   ELEMENT_WIDTH=70;
	int  MARGIN_LEFT;
	virtual bool onTouchBegan(Touch*touch, Event*event);
private:
	int removeCount = 0;//记录消除个数
	int doubleHitCount = 0;
	int clickitem[2];//保存列表点击元素
	vector<int> tipPos;
	Vector<Sprite*> allElements;//保存所有元素信息
	Vector<Sprite*> lights;//保存两次点击的光圈动画
	Vector<Sprite*> items;//保存两次点击的元素
	Vector<Sprite*> clean;//保存消除的动画
	void update(float dt);
	void showTipPos();
	Vec2 getPosByPostion(int postion);//根据棋盘上的位置获得显示的坐标
	void onTouchEnded(Touch*touch, Event*event);
	vector<int> screentoIndex(float x, float y);
	void showMatrix(float dt);

	void doItemSelectAnima(Vec2 pos);//播放元素选中动画
	void dealConnectANim();//处理消除的连线动画
	void clearClickState();//清除消除的UI数据
	void deawLine(int x1,int y1,int x2,int y2,bool line);//是否是直连的两点【区别边界相连】
	void dealDoubleHit(float dt);//处理连击数，1.5s清一次

	void resetMap();//重画棋盘
	void nextMap(float dt);
};
#endif
