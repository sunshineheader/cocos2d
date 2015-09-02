#include "CircleBy.h"

CircleBy* CircleBy::create(Point curPos, float duration, float degrees, float speed, bool clockwise){
	CircleBy* pCircleBy = new CircleBy();
	pCircleBy->initWithDuration(curPos, duration, degrees, speed, clockwise);
	pCircleBy->autorelease();
	return pCircleBy;
}

bool CircleBy::initWithDuration(Point curPos, float duration, float degrees, float speed, bool clockwise){
	if (ActionInterval::initWithDuration(duration)){
		this->currentPostion = curPos;
		this->speed = speed;
		this->clockWise = clockwise;
		//每次转动转过的弧度
		//CCLOG("radians = %f", degrees);
		//CCLOG("duration = %f", duration);
		//CCLOG("AnimationInterval = %f", Director::getInstance()->getAnimationInterval());
		this->degree = degrees / (duration / Director::getInstance()->getAnimationInterval());
		updateTimes = 1;
		return true;
	}
	return false;
}

void CircleBy::update(float dt){
	updateTimes++;
	//1按照顺时针和逆时针区分2按照象限区分旋转结果
	if (this->clockWise){
		 float roatate = this->getTarget()->getRotation() + degree;
		 float x = speed* cos(CC_DEGREES_TO_RADIANS(roatate));
		 float y = speed* sin(CC_DEGREES_TO_RADIANS(roatate));
		 int rotation = (int)roatate % 360;
		 if (rotation<90){
				 currentPostion.x += abs(x);
				 currentPostion.y -= abs(y);
		 }
		 else if (rotation >= 90 && rotation<180){
				 currentPostion.x -= abs(x);
				 currentPostion.y -= abs(y);
		 }
		 else if (rotation >= 180 && rotation < 270){
				 currentPostion.x -= abs(x);
				 currentPostion.y += abs(y);
		 }
		 else if (rotation >= 270 && rotation < 360){
				 currentPostion.x += abs(x);
				 currentPostion.y += abs(y);
		 }
		 this->getTarget()->setRotation(this->getTarget()->getRotation() + degree);
	}
	else{
		 float roatate = this->getTarget()->getRotation() - degree;
		 float x = speed* cos(CC_DEGREES_TO_RADIANS(roatate));
		 float y = speed* sin(CC_DEGREES_TO_RADIANS(roatate));
		 int rotation = (int)roatate % 360;
		 if (rotation<90){
				 currentPostion.x += abs(x);
				 currentPostion.y += abs(y);
		 }
		 else if (rotation >= 90 && rotation<180){
				 currentPostion.x -= abs(x);
				 currentPostion.y += abs(y);
		 }
		 else if (rotation >= 180 && rotation < 270){
				 currentPostion.x -= abs(x);
				 currentPostion.y -= abs(y);
		 }
		 else if (rotation >= 270 && rotation < 360){
				 currentPostion.x += abs(x);
				 currentPostion.y -= abs(y);
		 }
		 this->getTarget()->setRotation(this->getTarget()->getRotation() - degree);
	}
	Point newPos = Point(currentPostion.x, currentPostion.y);
	this->getTarget()->setPosition(newPos);

}