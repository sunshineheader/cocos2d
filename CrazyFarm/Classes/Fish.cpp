#include "Fish.h"

bool Fish::init(){
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

void Fish::initFish(int fishType){
	this->fishType = fishType;
	this->speed = getFishSpeedByType(fishType);;
	this->experience = getFishExperienceByType(fishType);
	this->fishGold = getFishGoldByType(fishType);
	this->resoureName = getSrcByType(fishType);
	initFishAnim(resoureName, 0);
}

void Fish::initFishAnim(string name, int startIndex){
	Sprite* image = Sprite::create();
	image->setRotation(270);
	this->addChild(image);
	Vector<SpriteFrame*> animFrames;
	int i = startIndex;
	do {
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name + String::createWithFormat("%d", i + 1)->_string + ".png");
		if (frame) {
			animFrames.pushBack(frame);
		}
		else {
			break;
		}

	} while (++i);
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	auto action = RepeatForever::create(Animate::create(animation));
	image->runAction(action);
}

string Fish::getSrcByType(int type){
	switch (type)
	{
	case FISHTYPE_1:
		return "0_0";
	case FISHTYPE_2:
		return "2_0";
	case FISHTYPE_3:
		return "5_0";
	case FISHTYPE_4:
		return "8_0";
	case FISHTYPE_5:
		return "10_0";
	case FISHTYPE_6:
		return "11_0";
	case FISHTYPE_7:
		return "14_0";
	case FISHTYPE_8:
		return "16_0";
	default:
		return "0_0";
	}
}


int Fish::getFishGoldByType(int type){
	//TODO
	return 0;
}


int Fish::getFishExperienceByType(int type){
	//TODO
	return 0;
}


float Fish::getFishSpeedByType(int type){
	return 1;
}

void Fish::move(int moveType){
	//选择鱼的移动模式
	switch (moveType)
	{
	case 1:
		schedule(schedule_selector(Fish::moveFishStraight), 0, CC_REPEAT_FOREVER, 0);
		break;
	case 2:
		schedule(schedule_selector(Fish::moveFishCircle), 0, 0, 0);
		break;
	default:
		schedule(schedule_selector(Fish::moveFishRandom), 0, CC_REPEAT_FOREVER, 0);
		break;
	}
}

void Fish::moveFishStraight(float dt){
	//TODO 鱼的直线移动
	Point nextPos = getNextPostion(this->getPosition(), this->speed, this->getRotation());
	auto move = MoveTo::create(dt, nextPos);
	this->runAction(move);
}

void Fish::moveFishCircle(float dt){
	//TODO 鱼的圆形移动
	Point circlePoint = this->getPosition();
	auto cirlce = CircleBy::create(circlePoint, 2, 360, 2, true);
	this->runAction(cirlce);
}

void Fish::moveFishRandom(float dt){
	//TOOD 鱼的随机运动

}


Point Fish::getNextPostion(Point pos, float speed, float degree){
	//TODO 完善鱼的直线移动
	if (degree < 0){
		degree += 360;
	}
	float next_x = speed*cos(CC_DEGREES_TO_RADIANS(degree));
	float next_y = speed*sin(CC_DEGREES_TO_RADIANS(degree));
	int rotation = (int)degree % 360;
	if (rotation < 90){
		pos.x += abs(next_x);
		pos.y -= abs(next_y);
	}
	else if (rotation >= 90 && rotation < 180){
		pos.x -= abs(next_x);
		pos.y -= abs(next_y);
	}
	else if (rotation >= 180 && rotation < 270){
		pos.x -= abs(next_x);
		pos.y += abs(next_y);
	}
	else if (rotation >= 270 && rotation < 360){
		pos.x += abs(next_x);
		pos.y += abs(next_y);
	}
	return  Point(pos.x, pos.y);
}

bool Fish::checkOutBorder(){

	return false;
}


