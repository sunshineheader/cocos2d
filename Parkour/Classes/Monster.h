#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"

USING_NS_CC;

class Monster : public cocos2d::Node
{
public:
	Monster();
	~Monster();
	static Monster* create(int ID);
    bool init(int ID);
 
    /* 加入到当前场景 */
    void joinToMap(Node* parent);

	/*获取当前动画播放到第几帧*/
	int getCurrentFrame();

	void logic(float dt);
 
    CC_SYNTHESIZE(int, m_ID, ID);
    CC_SYNTHESIZE(int, m_iPosX, iPosX);
    CC_SYNTHESIZE(int, m_iPosY, iPosY);
    CC_SYNTHESIZE(Value, m_sModelPath, sModelPath);
private:
	float animTime;
	bool startAnim;
};

#endif 
