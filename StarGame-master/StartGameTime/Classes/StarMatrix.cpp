#include "StarMatrix.h"
#include "GameData.h"
#include "StarParticle.h"
#include "ComboEffect.h"
#include "Audio.h"
#include <ctime>

bool StarMatrix::BombClick = false;
float StarMatrix::ONE_CLEAR_TIME = 0.08f;

StarMatrix* StarMatrix::create(GameLayer* layer){
	StarMatrix* ret = new StarMatrix();
	if(ret && ret->init(layer)){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool StarMatrix::init(GameLayer* layer){
	if(!Node::init()){
		return false;
	}
	m_layer = layer;
	needClear = false;
	clearOneByOne = false;
	acceptTouch = true;
	clearSumTime = 0;
	selectedListSize = 0;
	memset(stars, 0, sizeof(Star*) * ROW_NUM * COL_NUM);
	initMatrix();
	return true;
}

void StarMatrix::updateStar(float delta){
	for(int i = 0;i < ROW_NUM;i++){
		for(int j = 0;j< COL_NUM;j++){
			if(stars[i][j]!=nullptr){
				stars[i][j]->updatePosition(delta);
			}
		}
	}

	if(clearOneByOne){
		clearSumTime += delta;
		if(clearSumTime > ONE_CLEAR_TIME){
			deleteSelectedList();
			clearSumTime = 0;
		}
	}

	if(needClear){
		clearSumTime += delta;
		if(clearSumTime > ONE_CLEAR_TIME){
			clearMatrixOneByOne();
			clearSumTime = 0;
		}
	}

}

void StarMatrix::onTouch(const Point& p){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Star* s = getStarByTouch(p);
	if(p.x>visibleSize.width/2){
	   StarMatrix::touchLeft=false;
	}else{
	 StarMatrix::touchLeft=true;
	}
	if(s && acceptTouch && GameLayer::totalTime>0){
		clearOneByOne = true;
		if(BombClick){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()-500);
			GAMEDATA::getInstance()->saveGoldNum();
			TopMenu::getInstance()->refreshGold();
			TopMenu::getInstance()->updatePropsNum();
			TopMenu::getInstance()->stopScaleAction();
			useBombAuto(s);
			BombClick =false;
			return;
		}
		genSelectedList(s);
		//deleteSelectedList();
		//长度小于等于1则返回
		if(selectedList.size() <= 1){
			m_layer->hideLinkNum();
			selectedList.at(0)->setSelected(false);
			selectedList.clear();
		}else{
			acceptTouch =false;
			selectedListSize=selectedList.size();
			deleteSelectedList();
		}
	}
}

void StarMatrix::useBombAuto(Star* s){
	genBombList(s);
	deleteBombList();
}

void StarMatrix::setNeedClear(bool b){
	needClear = b;
}

void StarMatrix::setAcceptTouch(bool b){
	acceptTouch = b;
}

void StarMatrix::initMatrix(){
	srand(time(0));
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			int color = abs(rand()%Star::COLOR_MAX_NUM);
			if(color < 0) {
				CCLOG("color i=%d,j=%d");
			}
			Star* star = Star::create(color);
			stars[i][j] = star;
			star->setPosition(getPositionByIndex(i,j) + Point(0,100));
			star->setDesPosition(getPositionByIndex(i,j));
			star->setIndex_ij(i,j);
			this->addChild(star);
		}
	}
}

Point StarMatrix::getPositionByIndex(int i,int j){
	float x = j * Star::STAR_WIDTH + Star::STAR_WIDTH/2;
	float y = Star::STAR_HEIGHT*2 + (StarMatrix::COL_NUM - i)*Star::STAR_HEIGHT - Star::STAR_HEIGHT/2;
	return Point(x,y);
}

Star* StarMatrix::getStarByTouch(const Point& p){
	int k = (p.y)/Star::STAR_HEIGHT;//这里要用K转一下int 不然得不到正确结果
	int i = ROW_NUM - 1 - k + 2;
	int j = p.x/Star::STAR_WIDTH;
	if(i >= 0 && i < ROW_NUM &&
		j >= 0 && j < COL_NUM &&
		stars[i][j] != nullptr){
			CCLOG("i=%d,j=%d",i,j);
			return stars[i][j];
	}else{
		return nullptr;
	}
}

//消除检查
void StarMatrix::genSelectedList(Star* s){
	selectedList.clear();
	deque<Star*> travelList;
	travelList.push_back(s);
	deque<Star*>::iterator it;
	for(it= travelList.begin();it != travelList.end();){
		Star* star = *it;
		Star* linkStar = nullptr;
		int index_i = star->getIndexI();
		int index_j = star->getIndexJ();
		//上
		if(index_i-1 >= 0 && (linkStar = stars[index_i-1][index_j]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i-1][index_j]);
		}
		//下
		if(index_i+1 < ROW_NUM  && (linkStar = stars[index_i+1][index_j]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i+1][index_j]);
		}
		//左
		if(index_j-1 >= 0 && (linkStar = stars[index_i][index_j-1]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i][index_j-1]);
		}
		//右
		if(index_j+1 < COL_NUM && (linkStar = stars[index_i][index_j+1]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(stars[index_i][index_j+1]);
		}
		if(!star->isSelected()){
			star->setSelected(true);
			selectedList.push_back(star);
		}
		travelList.pop_front();
		it = travelList.begin();
	}
}
//产生炸弹的消除队列
void StarMatrix::genBombList(Star* s){
	selectedList.clear();
	selectedList.push_back(s);
	Star* linkStar = nullptr;
	int index_i = s->getIndexI();
	int index_j = s->getIndexJ();
	//上
	if(index_i-1 >= 0 && (linkStar = stars[index_i-1][index_j]) ){
		if(!linkStar->isSelected())
			selectedList.push_back(stars[index_i-1][index_j]);
	}
	//左上
	if(index_i-1 >= 0 && index_j-1 >= 0&& (linkStar = stars[index_i-1][index_j-1]) ){
		if(!linkStar->isSelected())
			selectedList.push_back(stars[index_i-1][index_j-1]);
	}
	//右上
	if(index_i-1 >= 0 && index_j+1 <= COL_NUM && (linkStar = stars[index_i-1][index_j+1]) ){
		if(!linkStar->isSelected())
			selectedList.push_back(stars[index_i-1][index_j+1]);
	}
	//下
	if(index_i+1 < ROW_NUM  && (linkStar = stars[index_i+1][index_j]) ){
		if(!linkStar->isSelected())
			selectedList.push_back(stars[index_i+1][index_j]);
	}
	//左下
	if(index_i+1 < ROW_NUM  && index_j-1 >= 0 && (linkStar = stars[index_i+1][index_j-1]) ){
		if(!linkStar->isSelected())
			selectedList.push_back(stars[index_i+1][index_j-1]);
	}
	//右下
	if(index_i+1 < ROW_NUM  &&  index_j+1 <= COL_NUM && (linkStar = stars[index_i+1][index_j+1]) ){
		if(!linkStar->isSelected())
			selectedList.push_back(stars[index_i+1][index_j+1]);
	}
	//左
	if(index_j-1 >= 0 && (linkStar = stars[index_i][index_j-1]) ){
		if(!linkStar->isSelected())
			selectedList.push_back(stars[index_i][index_j-1]);
	}
	//右
	if(index_j+1 < COL_NUM && (linkStar = stars[index_i][index_j+1]) ){
		if(!linkStar->isSelected())
			selectedList.push_back(stars[index_i][index_j+1]);
	}
}


void StarMatrix::deleteSelectedList(){
	//播放消除音效
	Audio::getInstance()->playPop();

	for(auto it = selectedList.begin();it != selectedList.end();it++){
		Star* star = *it;
		m_layer->showEveryScore(selectedListSize,30+(selectedListSize-selectedList.size())*5,selectedListSize-selectedList.size(),star->getPosition(),touchLeft);
		selectedList.pop_front();
		//粒子效果
		showStarParticleEffect(star->getColor(),star->getPosition(),this);
		stars[star->getIndexI()][star->getIndexJ()] = nullptr;
		star->removeFromParentAndCleanup(true);

		return;
	}
	clearOneByOne =false;
	//COMBO效果
	showComboEffect(selectedListSize,this);
	refreshScore();
	m_layer->showLinkNum(selectedListSize);
	selectedListSize=0;
	acceptTouch =true;
	adjustMatrix();
	if(isEnded()){
		acceptTouch=false;
		GameLayer::_PauseTime=true;// pause time
		m_layer->floatLeftStarMsg(getLeftStarNum());//通知layer弹出剩余星星的信息
		CCLOG("ENDED");
	}
}

void StarMatrix::deleteBombList(){
	//播放消除音效
	Audio::getInstance()->playPropBomb();

	for(auto it = selectedList.begin();it != selectedList.end();it++){
		Star* star = *it;
		selectedList.pop_front();
		//粒子效果
		showStarParticleEffect(star->getColor(),star->getPosition(),this);
		stars[star->getIndexI()][star->getIndexJ()] = nullptr;
		star->removeFromParentAndCleanup(true);
	}
	//COMBO效果
	selectedListSize=0;
	acceptTouch =true;
	adjustMatrix();
	if(isEnded()){
		acceptTouch=false;
		m_layer->floatLeftStarMsg(getLeftStarNum());
	}
}

void StarMatrix::adjustMatrix(){
	//垂直方向调整
	for(int i = ROW_NUM-1;i>=0;i--){
		for(int j = COL_NUM-1;j>=0;j--){
			if(stars[i][j] == nullptr){
				int up = i;
				int dis = 0;
				while(stars[up][j] == nullptr){
					dis++;
					up--;
					if(up<0){
						break;
					}
				}

				for(int begin_i = i - dis;begin_i >= 0;begin_i--){
					if(stars[begin_i][j] == nullptr)
						continue;
					Star* s = stars[begin_i + dis][j] = stars[begin_i][j];
					s->setIndex_ij(begin_i + dis,j);
					s->setDesPosition(getPositionByIndex(begin_i + dis,j));
					stars[begin_i][j] = nullptr;
				}
			}else{
				continue;
			}
		}
	}
	//水平方向调整
	for(int j = 0;j < COL_NUM;j++){
		if(stars[ROW_NUM-1][j] == nullptr){
			int des = 0;
			int right = j;
			while(stars[ROW_NUM-1][right] == nullptr){
				des++;
				right++;
			}
			for(int begin_i = 0;begin_i<ROW_NUM;begin_i++){
				for(int begin_j = j + des;begin_j < COL_NUM;begin_j++){
					if(stars[begin_i][begin_j] == nullptr)
						continue;
					Star* s = stars[begin_i][begin_j - des] = stars[begin_i][begin_j];
					s->setIndex_ij(begin_i,begin_j - des);
					s->setDesPosition(getPositionByIndex(begin_i,begin_j - des));
					stars[begin_i][begin_j] = nullptr;
				}
			}
		}
	}

}


void StarMatrix::refreshScore(){

}


bool StarMatrix::isEnded(){
	//if(getLeftStarNum()<=20){return true;}
	bool bRet = true;
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			if(stars[i][j] == nullptr)
				continue;
			int curColor = stars[i][j]->getColor();
			//上
			if(i-1>=0 && stars[i-1][j]!=nullptr && stars[i-1][j]->getColor() ==  curColor)
				return false;
			//下
			if(i+1<ROW_NUM && stars[i+1][j]!=nullptr && stars[i+1][j]->getColor() == curColor)
				return false;
			//左
			if(j-1>=0 && stars[i][j-1]!=nullptr && stars[i][j-1]->getColor() == curColor)
				return false;
			//右
			if(j+1<COL_NUM && stars[i][j+1]!=nullptr && stars[i][j+1]->getColor() == curColor)
				return false;
		}
	}
	return bRet;
}

void StarMatrix::clearMatrixOneByOne(){
	//播放消除音效
	Audio::getInstance()->playPop();
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			if(stars[i][j] == nullptr)
				continue;
			showStarParticleEffect(stars[i][j]->getColor(),stars[i][j]->getPosition(),this);
			stars[i][j]->removeFromParentAndCleanup(true);
			stars[i][j] = nullptr;
			return;
		}
	}
	//能够执行到这一句说明Matrix全为空，不在需要清空
	needClear = false;
	//转到下一关
	GAMEDATA::getInstance()->setCurLevel(GAMEDATA::getInstance()->getCurLevel() + 1);
	m_layer->gotoNextLevel();
	/*if(GAMEDATA::getInstance()->getCurScore() >= GAMEDATA::getInstance()->getNextScore()){
	GAMEDATA::getInstance()->setCurLevel(GAMEDATA::getInstance()->getCurLevel() + 1);
	m_layer->gotoNextLevel();
	}else{
	m_layer->gotoGameOver();
	CCLOG("GAME OVER");
	}*/
}

int StarMatrix::getLeftStarNum(){
	int ret = 0;
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			if(stars[i][j] == nullptr)
				continue;
			ret++;
		}
	}
	return ret;
}
