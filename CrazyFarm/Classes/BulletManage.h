#ifndef __BULLET_MANAGE_H__
#define __BULLET_MANAGE_H__
#include "Bullet.h"

class BulletManage{
public:
	static BulletManage* getInstance();
	Bullet* createBullet(int type, int rotation);
	void removeBullet(Bullet* fish);
private:
	BulletManage();
	static BulletManage* _instance;
	Vector<Bullet*> bulletPool;
};
#endif