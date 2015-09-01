#ifndef _ABOUT_H_
#define _ABOUT_H_
#include <string>
#include "cocos2d.h"
#include "FloatWord.h"
using namespace cocos2d;
class About : public Node{
public:
	virtual bool init();
	CREATE_FUNC(About);
	void hideSelf();
	void startGame();

private:
	About();

};
#endif
