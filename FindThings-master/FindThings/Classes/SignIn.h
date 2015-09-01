#ifndef _SIGNIN_H_
#define _SIGNIN_H_
#include <string>
#include "cocos2d.h"

using namespace cocos2d;
class SignIn : public Node{
public:
	static SignIn* getInstance();
	virtual bool init();
	CREATE_FUNC(SignIn);
	void startGameT();
private:
	static SignIn* _instance;
private:
	SignIn();
};
#endif
