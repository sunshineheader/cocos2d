#include "Bullet.h"


bool Bullet::init(){
	if (!Sprite::init()){
		return false;
	}
	return true;
}

void Bullet::initBullet(int bulletType, float rotation){
	this->bulletType = bulletType;
	this->bulletRotation = rotation;
	this->bulletSpeed = getSpeedByType(bulletType);
	initBulletFrame(getSrcByType(bulletType));
	scheduleUpdate();
}


string Bullet::getSrcByType(int type){
	switch (type)
	{
	case BULLETTYPE_1:
		return "bullet02_";
	case BULLETTYPE_2:
		return "bullet02_";
	case BULLETTYPE_3:
		return "bullet02_";
	case BULLETTYPE_4:
		return "bullet02_";
	case BULLETTYPE_5:
		return "bullet03_";
	case BULLETTYPE_6:
		return "bullet02_";
	case BULLETTYPE_7:
		return "bullet02_";
	case BULLETTYPE_8:
		return "bullet02_";
	default:
		return "bullet02_";;
	}

}

void Bullet::initBulletFrame(string name){
	this->initWithSpriteFrameName(name + "01.png");
}


int Bullet::getSpeedByType(int type){
	switch (type)
	{
	case BULLETTYPE_1:
		return 2;
	case BULLETTYPE_2:
		return 2;
	case BULLETTYPE_3:
		return 2;
	case BULLETTYPE_4:
		return 2;
	case BULLETTYPE_5:
		return 2;
	case BULLETTYPE_6:
		return 2;
	case BULLETTYPE_7:
		return 2;
	case BULLETTYPE_8:
		return 2;
	default:
		return 2;
	}
}
bool test = true;
void Bullet::update(float dt){
	//×Óµ¯ÔË¶¯
	Point nextPos = getNextPostion(this->getPosition(), this->bulletSpeed, this->getRotation());
	auto move = MoveTo::create(dt, nextPos);
	this->runAction(move);
}


Point Bullet::getNextPostion(Point pos, float speed, float degree){
	CCLOG("degree : %f", degree);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float next_x = pos.x + speed*sin(CC_DEGREES_TO_RADIANS(degree));
	float next_y = pos.y + speed*cos(CC_DEGREES_TO_RADIANS(degree));
	if (checkHeightBorder(next_y)){
		this->setRotation(180 - this->getRotation());
		next_x = pos.x + speed*sin(CC_DEGREES_TO_RADIANS(this->getRotation()));
		next_y = pos.y + speed*cos(CC_DEGREES_TO_RADIANS(this->getRotation()));
	}
	else if (checkWidthBorder(next_x)){
		this->setRotation(-this->getRotation());
		next_x = pos.x + speed*sin(CC_DEGREES_TO_RADIANS(this->getRotation()));
		next_y = pos.y + speed*cos(CC_DEGREES_TO_RADIANS(this->getRotation()));
	}
	return  Point(next_x, next_y);
}


bool Bullet::checkHeightBorder(float y){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (y < 0 || y > visibleSize.height){
		return true;
	}
	return false;
}

bool Bullet::checkWidthBorder(float x){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (x < 0 || x > visibleSize.width){
		return true;
	}
	return false;
}
