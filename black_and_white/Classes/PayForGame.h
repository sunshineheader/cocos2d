#ifndef PAYFORGAME_H
#define PAYFORGAME_H
#include "cocos2d.h"
#include <jni.h>
using namespace std;
using namespace cocos2d;

class PayForGame{
public:
	PayForGame();
	~PayForGame();
	static PayForGame*getInstance();
	void payformoney_callback(int payforgame_event_id);
	void payforGame(int id);
public:
	static PayForGame*_instance;

};
#endif
