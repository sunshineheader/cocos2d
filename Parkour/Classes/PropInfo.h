#ifndef _PROPINFO_H_
#define _PROPINFO_H_
#include <string>
#include "cocos2d.h"
#include "Player.h"
using namespace cocos2d;
class PropInfo : public Node{
public:
	static PropInfo* getInstance(Player* player);
	static PropInfo* getInstance2();
	virtual bool init();
	void updatePosition(float x,float y);
	void refreshSuperNum();
	void refreshMagneticNum();
	void refreshPotentialNum();
	bool usePropPotential(Touch* m_touch, Event* m_event);
	bool usePropSuper(Touch* m_touch, Event* m_event);
	bool usePropMagnetic(Touch* m_touch, Event* m_event);
	bool isShowVisible();
	void setShowVisible(bool show_visible);
	void removeTouchListener();
private:
	static PropInfo* _instance;
	Sprite* potentialIcon;
	Sprite* superIcon;
	Sprite* magneticIcon;
	Sprite* use_info;
	LabelAtlas* potentialNum;
	LabelAtlas* superNum;
	LabelAtlas* magneticNum;
	static Player* m_player;
	bool showVisible;
	EventListenerTouchOneByOne* listener1;
	EventListenerTouchOneByOne* listener2;
	EventListenerTouchOneByOne* listener3;
private:
	PropInfo();
};
#endif
