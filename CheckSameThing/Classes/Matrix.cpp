#include "Matrix.h"
#include"GameData.h"
Matrix* Matrix::instance = 0;

Matrix::Matrix(){
	if (!myCells.empty()){
		myCells.clear();
	}
}



Matrix* Matrix::getInstance(){
	if (instance == 0){
		instance = new Matrix();
	}
	return instance;
}

void Matrix::initMatrix(){
	myCells.clear();
	for (int i = 0; i < ROW_NUM; i++){
		for (int j = 0; j <COL_NUM; j++){
			int type = abs(rand()%MAX_TYPE_NUM);
			//初始化整个棋盘
			Cell* cell = new Cell();
			cell->setType(type+1);//[1,4]
			cell->setPosition(getPositionByXAndY(j, i));
			//CCLOG("position = %d", cell->getPosition());
			myCells.push_back(cell);
		}
	}
}



bool Matrix::canRemoveElement(int pos1, int pos2){
	if (canReMove(myCells, pos1, pos2)){
		myCells[pos1]->setType(NULL);
		myCells[pos2]->setType(NULL);
		return true;
	}
	return false;
}

bool  Matrix::canReMove(std::vector<Cell*> cells, int pos1, int pos2){
	roadChangePos.clear();
	//判断类型是否相同
	if (cells[pos1]->getCellType() != cells[pos2]->getCellType()) {
		return false;
	}
	boardLine = false;
	//根据位置来判断在棋盘上的信息
	int x1 = getXByCellPosition(pos1);
	int y1 = getYByCellPosition(pos1);
	int x2 = getXByCellPosition(pos2);
	int y2 = getYByCellPosition(pos2);
	if (x1 == x2 || y1 == y2) {//同行或者同列
		if (canConnectLevel1(cells, x1, y1, x2, y2)) {
			return true;
		}
		else if (canConnectLevel3(cells, x1, y1, x2, y2)) {
			return true;
		}
	}else {//不同行并且不同列
		if (canConnectLevel2(cells, x1, y1, x2, y2)) {
			return true;
		}
		else if (canConnectLevel3(cells, x1, y1, x2, y2)) {
			
			return true;
		}

	}
	//roadPos.clear();
	roadChangePos.clear();
	return false;

}

bool Matrix::canConnectLevel1(std::vector<Cell*> cells, int x1, int y1, int x2, int y2){
	int mix;
	int max;
	if (x1 == x2) {
		mix = y1 > y2 ? y2 : y1;
		max = y1 > y2 ? y1 : y2;
		for (int i = mix + 1; i < max; i++) {
			//roadPos.push_back(getPositionByXAndY(x1, i));
			if (cells[getPositionByXAndY(x1 ,i)]->getCellType() != NULL) {
				return false;
			}
		}

		return true;
	}

	if (y1 == y2) {
		mix = x1 > x2 ? x2 : x1;
		max = x1 > x2 ? x1 : x2;
		for (int i = mix + 1; i < max; i++) {
			//roadPos.push_back(getPositionByXAndY(i, y1));
			if (cells[getPositionByXAndY(i ,y1)]->getCellType() != NULL) {
				return false;
			}
		}
		return true;
	}

	return false;
}

bool Matrix::canConnectLevel2(std::vector<Cell*> cells, int x1, int y1, int x2, int y2){
	int middleX1 = x1;
	int middleY1 = y2;
	int middleX2 = x2;
	int middleY2 = y1;

	int middle1Position = getPositionByXAndY(middleX1, middleY1);
	if (cells[middle1Position]->getCellType() == NULL &&
		canConnectLevel1(cells, x1, y1, middleX1, middleY1) &&
		canConnectLevel1(cells, x2, y2, middleX1, middleY1)) {
		roadChangePos.push_back(middle1Position);
		return true;
	}

	int middle2Position = getPositionByXAndY(middleX2, middleY2);
	if (cells[middle2Position]->getCellType() == NULL &&
		canConnectLevel1(cells, x1, y1, middleX2, middleY2) &&
		canConnectLevel1(cells, x2, y2, middleX2, middleY2)) {
		roadChangePos.push_back(middle2Position);
		return true;
	}
	
	return false;
}

bool Matrix::canConnectLevel3(std::vector<Cell*> cells, int x1, int y1, int x2, int y2){
	if (y1 == y2) {
		return canConnectLevel3X(cells, x1, y1, x2, y2);
	}
	else if (x1 == x2) {
		return canConnectLevel3Y(cells, x1, y1, x2, y2);
	}
	else {
		if (canConnectLevel3X(cells, x1, y1, x2, y2)) {
			return true;
		}
		return canConnectLevel3Y(cells, x1, y1, x2, y2);
	}
}

bool Matrix::canConnectLevel3X(std::vector<Cell*> cells, int x1, int y1, int x2, int y2){
	// looking for up
	int i;
	i = y1 - 1;
	while (i >= 0) {
		if (cells[getPositionByXAndY(x1, i)]->getCellType() != NULL) {
			break;
		}
		if (i != y2 && canConnectLevel1(cells, x1, y1, x1, i) &&
			canConnectLevel2(cells, x1, i, x2, y2)) {
			roadChangePos.push_back(getPositionByXAndY(x1, i));
			return true;
		}
		i--;
	}

	// looking for down
	i = y1 + 1;
	while (i < ROW_NUM) {
		if (cells[getPositionByXAndY(x1, i)]->getCellType() != NULL) {
			break;
		}
		if (i != y2 &&  canConnectLevel1(cells, x1, y1, x1, i) &&
			canConnectLevel2(cells, x1, i, x2, y2)) {
			roadChangePos.push_back(getPositionByXAndY(x1, i));
			return true;
		}
		i++;
	}

	// check down
	bool canReachUp = true;
	i = y1 - 1;
	while (i >= 0) {
		if (cells[getPositionByXAndY(x1, i)]->getCellType() != NULL) {
			canReachUp = false;
			break;
		}
		i--;
	}

	if (canReachUp) {
		i = y2 - 1;
		while (i >= 0) {
			if (cells[getPositionByXAndY(x2, i)]->getCellType() != NULL) {
				canReachUp = false;
				break;
			}
			i--;
		}
	}

	if (canReachUp) {
		//TODO:底部边框相连
		boardLine = true;
		roadChangePos.push_back(getPositionByXAndY(x1,0));
		roadChangePos.push_back(getPositionByXAndY(x2,0));
		return true;
	}

	// check up
	bool canReachDown = true;
	i = y1 + 1;
	while (i < ROW_NUM) {
		if (cells[getPositionByXAndY(x1, i)]->getCellType() != NULL) {
			canReachDown = false;
			break;
		}
		i++;
	}

	if (canReachDown) {
		i = y2 + 1;
		while (i < ROW_NUM) {
			if (cells[getPositionByXAndY(x2, i)]->getCellType() != NULL) {
				canReachDown = false;
				break;
			}
			i++;
		}
	}

	if (canReachDown) {
		//TODO:顶部边框相连
		boardLine = true;
		roadChangePos.push_back(getPositionByXAndY(x1, ROW_NUM-1));
		roadChangePos.push_back(getPositionByXAndY(x2, ROW_NUM-1));
		return true;
	}

	return false;
}

bool Matrix::canConnectLevel3Y(std::vector<Cell*> cells, int x1, int y1, int x2, int y2){
	int i;
	i = x1 - 1;
	while (i >= 0) {
		if (cells[getPositionByXAndY(i, y1)]->getCellType() != NULL) {
			break;
		}
		if (i != x2 && canConnectLevel1(cells, x1, y1, i, y1) &&
			canConnectLevel2(cells, i, y1, x2, y2)) {
			roadChangePos.push_back(getPositionByXAndY(i,y1));
			return true;
		}
		i--;
	}

	i = x1 + 1;
	while (i < COL_NUM) {
		if (cells[getPositionByXAndY(i, y1)]->getCellType() != NULL) {
			break;
		}
		if (i != x2 &&  canConnectLevel1(cells, x1, y1, i, y1) &&
			canConnectLevel2(cells, i, y1, x2, y2)) {
			roadChangePos.push_back(getPositionByXAndY(i, y1));
			return true;
		}
		i++;
	}

	// check right
	bool canReachRight = true;
	i = x1 - 1;
	while (i >= 0) {
		if (cells[getPositionByXAndY(i, y1)]->getCellType() != NULL) {
			canReachRight = false;
			break;
		}
		i--;
	}

	if (canReachRight) {
		i = x2 - 1;
		while (i >= 0) {
			if (cells[getPositionByXAndY(i, y2)]->getCellType() != NULL) {
				canReachRight = false;
				break;
			}
			i--;
		}
	}

	if (canReachRight) {
		//TODO:左边边框相连
		boardLine = true;
		roadChangePos.push_back(getPositionByXAndY(0, y1));
		roadChangePos.push_back(getPositionByXAndY(0,y2));
		return true;
	}

	// check left
	bool canReachLeft = true;
	i = x1 + 1;
	while (i < COL_NUM) {
		if (cells[getPositionByXAndY(i, y1)]->getCellType() != NULL) {
			canReachLeft = false;
			break;
		}
		i++;
	}

	if (canReachLeft) {
		i = x2 + 1;
		while (i < COL_NUM) {
			if (cells[getPositionByXAndY(i, y2)]->getCellType() != NULL) {
				canReachLeft = false;
				break;
			}
			i++;
		}
	}

	if (canReachLeft) {
		//TODO:右边边边框相连
		boardLine = true;
		roadChangePos.push_back(getPositionByXAndY(COL_NUM-1, y1));
		roadChangePos.push_back(getPositionByXAndY(COL_NUM-1, y2));
		return true;
	}

	return false;
}

int Matrix::getXByCellPosition(int pos){
	return pos % COL_NUM;
}
int Matrix::getYByCellPosition(int pos){
	CCLOG("getYByCellPosition y=%f", pos / COL_NUM);
	return pos / COL_NUM;
}

int Matrix::getPositionByXAndY(int x, int y){
	return x + y*COL_NUM;
}


std::vector<Cell*> Matrix::getMartixCells(){
	return myCells;
}
//返回当前棋盘上是否还有可消除元素
bool Matrix::hasRemoveElement(){
	for (int i = 0; i < myCells.size() - 1; i++){
		if (myCells.at(i)->getCellType()!=NULL){
			for (int j = i + 1; j < myCells.size(); j++){
				if (myCells.at(j)->getCellType() != NULL){
					if (canReMove(myCells, i, j)){
						return true;
					}
				}
				
			}
		}
	}
	return false;
}

//重排
void Matrix::resetMap(){
	//1,已消除元素不用在填充
	
	for (int i = 0; i < myCells.size(); i++){
		if (myCells.at(i)->getCellType() != NULL){
			int type = abs(rand() % MAX_TYPE_NUM);
			myCells.at(i)->setType(type + 1);
			CCLOG("reset pos=%d",i);
		}
	}

	while (!hasRemoveElement())
	{
		resetMap();
	}
}

std::vector<int> Matrix::getRoadChangePos(){
	return roadChangePos;
}


std::vector<int> Matrix::getTipPOsition(){
	vector<int> pos;
	for (int i = 0; i < myCells.size() - 1; i++){
		if (myCells.at(i)->getCellType() != NULL){
			for (int j = i + 1; j < myCells.size(); j++){
				if (myCells.at(j)->getCellType() != NULL){
					if (canReMove(myCells, i, j)){
						pos.push_back(i);
						pos.push_back(j);
						return pos;
					}
				}

			}
		}
	}
	pos.push_back(-1);
	pos.push_back(-1);
	return pos;
}