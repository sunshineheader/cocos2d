#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

#include "cocos2d.h"

using namespace cocos2d;

class GameView : public Layer{

public:
	Point touchDownPoint;
	Point touchUpPoint;
	Point touchCurPoint;
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(GameView);
	void createMaterials();
	void createGuideMaterials();
	void singleMaterial(int index);
	bool onTouchBegan(Touch *touch, Event  *event);
	void onTouchMoved(Touch *touch, Event  *event);
	void onTouchEnded(Touch *touch, Event  *event);
	int getIndexByPosition(Point p);
	Point getPositionByIndex(int index);
	void quickfind(float dt);
	int addTime(bool isSpecial);
	void addTimeAnim(int time,Point pos);
	void showPlayerGuide();//展示新手引导
	void showPropTimeAnim();
private:
	int newIndex;//新产生的物品的序列
	bool acceptTouch;
	Sprite* quickFindResult;
	CCClippingNode* pClip;
	CCDrawNode* pStencil;
	Sprite* slide;
	Sprite* circle;
	LayerColor* bg;
	bool firstClick;
	bool isGuideTime;
};
#endif
