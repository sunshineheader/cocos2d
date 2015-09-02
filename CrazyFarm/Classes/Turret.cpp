#include "Turret.h"

bool Turret::init(){
	if (!Sprite::init()){
		return false;
	}
	return true;
}

void Turret::initWithType(int type){
	this->initWithSpriteFrameName(getSrcByType(type));
}

string Turret::getSrcByType(int type){
	switch (type)
	{
	case TURRETTYPE_1:
		return "gun_c_2.png";
	case TURRETTYPE_2:
		return "gun_c_3.png";
	case TURRETTYPE_3:
		return "gun_c_4.png";
	case TURRETTYPE_4:
		return "gun_d_2.png";
	case TURRETTYPE_5:
		return "gun_d_3.png";
	case TURRETTYPE_6:
		return "gun_d_4.png";
	default:
		return "gun_c_2.png";
	}
}