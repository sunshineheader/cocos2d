#ifndef __CELL_H__
#define __CELL_H__
class Cell{
public:
	int getCellType();
	void setType(int type);
	int getPosition();
	void setPosition(int pos);
private:
	int type;
	int positon;
};
#endif