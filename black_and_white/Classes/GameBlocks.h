#ifndef GAMEBLOCKS_H
#define GAMEBLOCKS_H
#include "cocos2d.h"
#include "GameDefinition.h"
using namespace cocos2d;

class GameBlocks :public Sprite{
public:
	enum Color{
		YELLOW,
		WHITE,
		BLACK
	};
public:
	virtual bool init();
	virtual void initMatrix();
	static Vector<GameBlocks*>*getGameBlocks();
	CREATE_FUNC(GameBlocks);
public:
	static GameBlocks*create(int color);
	std::string getImage(int color);
private:
	const static int RowNumber=ROW_NUMBER;
	const static int ColNumber=COL_NUMBER;
	static Vector<GameBlocks*>*gameblocks;
private:
	int mycolor;
	int index_i;
	int index_j;


};

#endif
