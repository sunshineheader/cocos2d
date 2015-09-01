#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <string.h>
#include "stdlib.h"
#include "cocos2d.h"
#include "Cell.h"


using namespace std;
class Matrix{
public:
	enum CellType
	{
		TYPE_1=1,
		TYPE_2=2,
		TYPE_3=3,
		TYPE_4=4
	};

	Matrix();
	~Matrix();
	
	static Matrix*getInstance();
	int ROW_NUM;//行数
	int COL_NUM;//列数
	void initMatrix();
	bool canRemoveElement(int pos1, int pos2);
	std::vector<Cell*> getMartixCells();//返回棋盘
	int getXByCellPosition(int pos);//根据编号来获取在棋盘上的X值
	int getYByCellPosition(int pos);//根据编号来获取在棋盘上的Y值
	int getPositionByXAndY(int x, int y);//根据棋盘上X,和Y来确定编号

	bool hasRemoveElement();//返回当前棋盘上是否还有可消除元素
	void resetMap();//重排
	std::vector<int> getRoadChangePos();

	std::vector<int> getTipPOsition();//获得消除提示的元素
	bool boardLine = false;
private:
	std::vector<int> roadChangePos;//记录转折点

	static Matrix* instance;
	std::vector<Cell*> myCells;
	bool canReMove(std::vector<Cell*>, int pos1, int pos2);//检测是否可以被消去
	bool canConnectLevel1(std::vector<Cell*>, int x1, int y1, int x2, int y2);//1级检查
	bool canConnectLevel2(std::vector<Cell*>, int x1, int y1, int x2, int y2);//2级检查
	bool canConnectLevel3(std::vector<Cell*>, int x1, int y1, int x2, int y2);//3级检查
	bool canConnectLevel3X(std::vector<Cell*>, int x1, int y1, int x2, int y2);//3级X向
	bool canConnectLevel3Y(std::vector<Cell*>, int x1, int y1, int x2, int y2);//3级Y向
	const static int MAX_TYPE_NUM = 4;//棋盘中允许出现的最多的元素种类
};
#endif
