#include "BulletManage.h"


BulletManage* BulletManage::_instance = 0;

BulletManage* BulletManage::getInstance(){
	if (_instance == 0){
		_instance = new BulletManage();
	}
	return _instance;
}

BulletManage::BulletManage(){

}

Bullet* BulletManage::createBullet(int type,int rotation){
	auto bullet = Bullet::create();
	bullet->initBullet(type,rotation);
	bullet->setPosition(ccp(400,20));
	bulletPool.pushBack(bullet);
	return bullet;
}

void BulletManage::removeBullet(Bullet* bullet){
	bulletPool.eraseObject(bullet);
}
