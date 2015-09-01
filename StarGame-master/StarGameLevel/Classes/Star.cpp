#include "Star.h"

Star* Star::create(int color){
	Star* ret = new Star();
	if(ret && ret->initWithFile(ret->getImage(color))){
		ret->color = color;
		ret->selected = false;
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

char* Star::getImage(int color){
	switch(color){
	/*case BLUE:
		return "blue.png";*/
	case GREEN:
		return "green.png";
	case YELLOW:
		return "orange.png";
	case RED:
		return "red.png";
	case PURPLE:
		return "purple.png";
	case MULTICOLOUR:
		return "super_star.png";
	}
}

bool Star::isSelected(){
	return selected;
}

int Star::getColor(){
	return color;
}

void Star::setDesPosition(const Point& p){
	desPosition = p;
}

void Star::updatePosition(float delta){
	if(desPosition.y != getPositionY()){
		setPositionY(getPositionY() - MOVE_SPEED*delta);
		if(getPositionY() < desPosition.y){
			setPositionY(desPosition.y);
		}
	}
	if(desPosition.x != getPositionX()){
		setPositionX(getPositionX() - MOVE_SPEED*delta);
		if(getPositionX() < desPosition.x){
			setPositionX(desPosition.x);
		}
	}
}

void Star::changeColor(int color){
	this->color=color;
	Texture2D* image = Director::getInstance()->getTextureCache()->addImage(getImage(color));
	this->setTexture(image);
}