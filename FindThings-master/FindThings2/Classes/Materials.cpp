#include "Materials.h"
#include "ImageInfoUtil.h"

bool Materials::init(){
	if(!Node::init()){
		return false;
	}
	return true;
}

bool Materials::onTouchBegan(Touch *touch, Event  *event,Point basePos){
	Point touchPoint = Point(touch->getLocation().x+abs(basePos.x),touch->getLocation().y);
	if(good->getBoundingBox().containsPoint(touchPoint)){
		return true;
	}else{
		return false;
	}	
}

void Materials::setMSprite(std::string imageName,Point* pos){
	good = Sprite::createWithSpriteFrameName(imageName+".png");
	good->setAnchorPoint(Point::ANCHOR_MIDDLE);
	good->setPosition(pos->x,pos->y);
	this->addChild(good);
}


int Materials::getMaterialsID(){
	return ID;
}

std::string Materials::getMaterialsName(){
	return mname;
}

void Materials::setMaterialsID(int id,Point* pos){
	this->ID=id;
	this->mname =getImageNameById(ID);
	setMSprite(mname,pos);
	this->dis_pos = pos;
}

void Materials::changeMaterials(std::string name){
	this->mname =name;
	setMSprite(mname,dis_pos);
}

std::string Materials::getImageNameById(int id){
	std::string imgaeName="";
	ImageInfo info=ImageInfoUtil::getInstance()->getInfoById(id);
	imgaeName=info.image_name;
	if(info.special==0){
		special = false;
	}else{
		special = true;
	}
	return imgaeName;
}

bool Materials::isSpecial(){
	if(special==0){
		return false;
	}else{
		return true;
	}
}

Point* Materials::getDisPosition(){
   return dis_pos;
}