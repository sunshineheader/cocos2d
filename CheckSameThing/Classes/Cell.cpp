#include "Cell.h"

int Cell::getCellType(){
	return type;
}

void Cell::setType(int type){
	this->type = type;
}

int Cell::getPosition(){
	return positon;
}

void Cell::setPosition(int pos){
	this->positon = pos;
}