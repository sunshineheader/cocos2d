#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h" 

using namespace cocos2d;
using namespace std;

#define BULLETTYPE_1 0
#define BULLETTYPE_2 1
#define BULLETTYPE_3 2
#define BULLETTYPE_4 3
#define BULLETTYPE_5 4
#define BULLETTYPE_6 5
#define BULLETTYPE_7 6
#define BULLETTYPE_8 7


class Bullet:public Sprite{
public:
	virtual bool init();
	CREATE_FUNC(Bullet);
	void initBullet(int bulletType,float rotation);
private:
	int bulletSpeed;
	int bulletType;
	int bulletRotation;
	string getSrcByType(int type);
	int getSpeedByType(int type);
	void update(float);
	bool checkHeightBorder(float y);//y边界检查
	bool checkWidthBorder(float x);//x边界检查
	void initBulletFrame(string name);//子弹帧动画
	Point getNextPostion(Point pos, float speed, float degree);
};
#endif