#ifndef __LEVELLAYER_H__
#define __LEVELLAYER_H__

#include <iostream>
#include "cocos2d.h"  

USING_NS_CC; 

#define SHORTEST_SLIDE_LENGTH (20)

class LevelLayer: public Layer
{
private:

    int pageNode;
    int curPageNode;
    Point touchDownPoint;
    Point touchUpPoint;
    Point touchCurPoint;
    float WINDOW_WIDTH;
    float WINDOW_HEIGHT;
    void goToCurrNode();
	void gotoGame();
	void backgame_callback();
	void openbuttle_callback();
	void openscene_callback();

public:
    virtual bool init();
    CREATE_FUNC(LevelLayer);
    
    void menuCloseCallback(Ref* pSender);
    bool onTouchBegan(Touch *touch, Event  *event);
    void onTouchMoved(Touch *touch, Event  *event);
    void onTouchEnded(Touch *touch, Event  *event);
    void addNode(Node *level);
};
  
#endif
