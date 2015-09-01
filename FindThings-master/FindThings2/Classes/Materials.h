#ifndef __MATERIALS_H__
#define __MATERIALS_H__
#include "cocos2d.h"
using namespace cocos2d;


class Materials : public Node{
public:
	virtual bool init();
	int getMaterialsID();
	void setMaterialsID(int id,Point* pos);
	void changeMaterials(std::string name);
	std::string getMaterialsName();
	bool isSpecial();
	bool onTouchBegan(Touch *touch, Event  *event,Point basePos);
	Point* getDisPosition();
    CREATE_FUNC(Materials);

private :
	Sprite* good;//ŒÔ∆∑
	int ID;//Œ®“ªID
	std::string mname;
	void setMSprite(std::string imageName,Point* pos);
	std::string getImageNameById(int id);
	Point* dis_pos;
	bool special;
};
#endif