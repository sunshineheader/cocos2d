#ifndef _BLINKTITLE_H_
#define _BLINKTITLE_H_
#include "cocos2d.h"
USING_NS_CC;
class BlinkTitle : public Node{
private:
	BlinkTitle();
public:
	static BlinkTitle* create(const std::string& fileName); 
private:
	bool init(const std::string& fileName);

};

#endif