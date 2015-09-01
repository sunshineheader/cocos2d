#include "GameLayer.h"
#include "Matrix.h"
#include "MapInfo.h"
#include"GameData.h"
#include"Audio.h"
#include"math.h"
#include "GameGuiLayer.h"

bool GameLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	GAMEDATA::getInstance()->setLevel(1);
	MARGIN_BOTTOM = 220;
	MARGIN_LEFT = 100;
	Matrix::getInstance()->ROW_NUM = 4;
	Matrix::getInstance()->COL_NUM = 4;
	 clickitem[0] = -1;
	 clickitem[1] = -1;
	 removeCount = 0;
	 GAMEDATA::getInstance()->needResetMap = false;
	 GAMEDATA::getInstance()->needTipPos = false;
	//处理touch事件监听
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::ccTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::ccTouchEnded, this);

	//add game bg to this layer
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* game_bg = Sprite::create("game_bg.jpg");
	game_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(game_bg);

	//棋盘初始化
	Matrix::getInstance()->initMatrix();
	Sprite* element = NULL;
	std::vector<Cell*> allCells = Matrix::getInstance()->getMartixCells();
	for (int i = 0; i < allCells.size(); i++){
	    //开始在棋盘上绘制所有的元素
		Vec2 pos = getPosByPostion(allCells.at(i)->getPosition());
		//int 转 string
		string s = "item" + CCString::createWithFormat("%d", allCells.at(i)->getCellType())->_string + ".png";
		element = Sprite::create(s);
		element->setScale(0.5);
		element->setPosition(pos);
		auto Act= Sequence::create(DelayTime::create(1), ScaleBy::create(0.5, 2), nullptr);
		element->runAction(Act);
		element->setTag(allCells.at(i)->getCellType());
		this->addChild(element);
		allElements.pushBack(element);
	}
	schedule(schedule_selector(GameLayer::showMatrix), 1.0f, 0, 0);
	scheduleUpdate();
	GAMEDATA::getInstance()->setstate(1);
	return true;
}

void GameLayer::resetMap(){
	Matrix::getInstance()->resetMap();
	//TODO:所有元素缩小动画
	Sprite* element = NULL;
	std::vector<Cell*> allCells = Matrix::getInstance()->getMartixCells();
	for (int i = 0; i < allCells.size(); i++){
		if (allCells.at(i)->getCellType() != NULL&&allCells.at(i)->getCellType() != allElements.at(i)->getTag()){
			//开始在棋盘上绘制所有的元素
			//int 转 string
			string s = "item" + CCString::createWithFormat("%d", allCells.at(i)->getCellType())->_string + ".png";
			element = Sprite::create(s);
			allElements.at(i)->setTag(allCells.at(i)->getCellType());
			allElements.at(i)->setTexture(element->getTexture());
		}
	}

	//TODO:所有元素从小放大动画
}

void GameLayer::showMatrix(float dt){
	Sprite* sprite = Sprite::create("GO.png");
	sprite->setPosition(240, 400);
	auto action = Sequence::create(
		MoveBy::create(1.0f, Vec2(0, 0)), FadeOut::create(0),
		nullptr);
	addChild(sprite, 1);
	sprite->runAction(action);
	Audio::getInstance()->playReadyGo();
	GAMEDATA::getInstance()->setstate(0);
}
Vec2 GameLayer::getPosByPostion(int postion){
	int x = Matrix::getInstance()->getXByCellPosition(postion);
	int y = Matrix::getInstance()->getYByCellPosition(postion);
	float pos_x = x * ELEMENT_WIDTH + MARGIN_LEFT + ELEMENT_WIDTH/2;
	float pos_y = y * ELEMENT_WIDTH + MARGIN_BOTTOM + ELEMENT_WIDTH / 2;
	CCLOG("position =%d ,x=%d ,y=%d",x,y);
	return ccp(pos_x, pos_y);
}

void GameLayer::doItemSelectAnima(Vec2 pos){
	auto sp = Sprite::create("select_bg_1.png");
	sp->setPosition(pos);
	this->addChild(sp);
	auto animation = Animation::create();
	for (int i = 1; i<6; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "select_bg_%1d.png", i);
		animation->addSpriteFrameWithFile(szName);
	}
	animation->setDelayPerUnit(2.0f / 5);
	animation->setRestoreOriginalFrame(true);

	auto animate = Animate::create(animation);
	sp->runAction(RepeatForever::create(animate));
	lights.pushBack(sp);
}


void GameLayer::clearClickState(){
	lights.at(0)->removeFromParent();
	lights.at(1)->removeFromParent();
	items.at(0)->removeFromParent();
	items.at(1)->removeFromParent();
	lights.popBack();
	items.popBack();
	lights.popBack();
	items.popBack();
	clickitem[0] = -1;
	clickitem[1] = -1;
}

bool GameLayer::onTouchBegan(Touch*touch, Event*event){
	//TODO:监听点击事件
	auto point = touch->getLocation();
	Audio::getInstance()->hititems();
	return true;
}

void GameLayer::update(float dt){
	if (GAMEDATA::getInstance()->needResetMap){
		GAMEDATA::getInstance()->needResetMap = false;
		resetMap();
	}

	if (GAMEDATA::getInstance()->needTipPos){
		GAMEDATA::getInstance()->needTipPos = false;
		showTipPos();
	}
}

void GameLayer::showTipPos(){
	tipPos = Matrix::getInstance()->getTipPOsition();
	if (tipPos[0] == -1){
		//没有可消除元素
	}
	else{
		doItemSelectAnima(getPosByPostion(tipPos[0]));
		doItemSelectAnima(getPosByPostion(tipPos[1]));
	}
}

void GameLayer::onTouchEnded(Touch*touch, Event*event){
	int  x = touch->getLocation().x;
	int y = touch->getLocation().y;
	CCLOG("onTouchEnded pointX=%d,pointY=%d", screentoIndex(x, y).at(0), screentoIndex(x, y).at(1));
	int pos2 = Matrix::getInstance()->getPositionByXAndY(screentoIndex(x, y).at(0), screentoIndex(x, y).at(1));
	Vec2 scenePos = getPosByPostion(pos2);
	
	if (pos2<0 || pos2 >= Matrix::getInstance()->ROW_NUM*Matrix::getInstance()->COL_NUM){
		CCLOG("onTouchEnded pos2=%d over", pos2);
		return;
	}
	if (Matrix::getInstance()->getMartixCells().at(pos2)->getCellType() == NULL){
		CCLOG("onTouchEnded pos2=%d is null", pos2);
		return;
	}

	if (clickitem[0] != -1 && clickitem[0] == pos2){
		CCLOG("onTouchEnded pos2=%d touch already", pos2);
		return;
	}

	
	if (tipPos.size()>1 && tipPos[0] != tipPos[1]){
		//有提示
		lights.at(0)->removeFromParent();
		lights.at(1)->removeFromParent();
		lights.clear();
		tipPos.clear();
	}
	
	//deal touch item animation
	auto slectedIcon = allElements.at(pos2);
	auto actionUp1 = Sequence::create(ScaleTo::create(0.25, 1.1, 1),
		ScaleTo::create(0.25, 0.9, 1), ScaleTo::create(0.25, 1, 1.01), ScaleTo::create(0.25, 1, 0.9), nullptr);
	slectedIcon->runAction(RepeatForever::create(actionUp1->clone()));
	
	if (clickitem[0] == -1){
		clickitem[0] = pos2;
		doItemSelectAnima(scenePos);
		items.pushBack(slectedIcon);
	}
	else
	{
		clickitem[1] = pos2;
		doItemSelectAnima(scenePos);
		items.pushBack(slectedIcon);
	}


	if (clickitem[0] != -1 && clickitem[1] != -1){
		if (Matrix::getInstance()->canRemoveElement(clickitem[0], clickitem[1])){
			//CCLOG("can remove");
			//处理可相连逻辑
			//1:画出连线,播放连击提示动画
			dealConnectANim();
			//2:播放爆炸动画
			auto boom = Sprite::create("bomb_1.png");
			boom->setPosition(scenePos);
			this->addChild(boom);
			auto animation11 = Animation::create();
			for (int i = 1; i<7; i++)
			{
				char szName[100] = { 0 };
				sprintf(szName, "bomb_%1d.png", i);
				animation11->addSpriteFrameWithFile(szName);
			}
			animation11->setDelayPerUnit(0.2f / 6);
			animation11->setRestoreOriginalFrame(true);

			auto am = Animate::create(animation11);
			auto act2 = Sequence::create(am, FadeOut::create(0), nullptr);
			boom->runAction(act2);

			auto circle = Sprite::create("conn_circle_1.png");
			circle->setPosition(scenePos);
			this->addChild(circle);
			auto animation12 = Animation::create();
			for (int i = 1; i<4; i++)
			{
				char szName[100] = { 0 };
				sprintf(szName, "conn_circle_%1d.png", i);
				animation12->addSpriteFrameWithFile(szName);
			}
			animation12->setDelayPerUnit(0.2f / 3);
			animation12->setRestoreOriginalFrame(true);

			auto am1 = Animate::create(animation12);
			auto act3 = Sequence::create(am1, FadeOut::create(0), nullptr);
			circle->runAction(act3);


			clean.pushBack(boom);
			clean.pushBack(circle);
			//3:结束消除状态，清除缓存信息
			clearClickState();
			//4:处理统计信息
			removeCount += 2;
			GAMEDATA::getInstance()->setAchievescore(GAMEDATA::getInstance()->getAchievescore() + 100);
			GAMEDATA::getInstance()->updateScore = true;
			//判断是否有可消除元素
			if (removeCount == Matrix::getInstance()->COL_NUM*Matrix::getInstance()->ROW_NUM){
				//全部消除
				//TODO:next map
				schedule(schedule_selector(GameLayer::nextMap), 1.0f, 0, 0);
				
			}
			else{
				if (!Matrix::getInstance()->hasRemoveElement()){
					resetMap();
				}
			}
			

		}
		else{
			//CCLOG("can not remove pos1=%d&pos2=%d", clickitem[0], clickitem[1]);
			lights.at(0)->removeFromParent();
			items.at(0)->cleanup();
			Sprite *temp = lights.at(1);
			Sprite *temp1 = items.at(1);
			lights.popBack();
			items.popBack();
			lights.popBack();
			items.popBack();
			lights.pushBack(temp);
			items.pushBack(temp1);
			clickitem[0] = clickitem[1];
			clickitem[1] = -1;
		}
	}

}

void GameLayer::nextMap(float dt){
	GAMEDATA::getInstance()->setLevel(GAMEDATA::getInstance()->getLevel() + 1);
	if (GAMEDATA::getInstance()->getLevel() == 2){
		MARGIN_BOTTOM = 150;
		MARGIN_LEFT = 65;
		Matrix::getInstance()->ROW_NUM = 6;
		Matrix::getInstance()->COL_NUM = 5;
	}
	else{
		MARGIN_BOTTOM = 150;
		MARGIN_LEFT = 30;
		Matrix::getInstance()->ROW_NUM = 6;
		Matrix::getInstance()->COL_NUM = 6;
	}
	clickitem[0] = -1;
	clickitem[1] = -1;
	removeCount = 0;
	GAMEDATA::getInstance()->needResetMap = false;
	GAMEDATA::getInstance()->needTipPos = false;
	
	//棋盘初始化
	Matrix::getInstance()->initMatrix();
	Sprite* element = NULL;
	std::vector<Cell*> allCells = Matrix::getInstance()->getMartixCells();
	CCLOG("allCells.size()= %d", allCells.size());
	//for (int i = 0; i < allElements.size(); i++){
	//	allElements.at(i)->removeFromParent();
	//}
	allElements.clear();
	for (int i = 0; i < allCells.size(); i++){
		//开始在棋盘上绘制所有的元素
		Vec2 pos = getPosByPostion(allCells.at(i)->getPosition());
		//int 转 string
		string s = "item" + CCString::createWithFormat("%d", allCells.at(i)->getCellType())->_string + ".png";
		element = Sprite::create(s);
		element->setPosition(pos);
		element->setTag(allCells.at(i)->getCellType());
		this->addChild(element);
		allElements.pushBack(element);
	}
	schedule(schedule_selector(GameLayer::showMatrix), 1.0f, 0, 0);
	GAMEDATA::getInstance()->setstate(1);
}

vector<int> GameLayer::screentoIndex(float x, float y)
{

	int pos_x=0;
	int pos_y=0;

	for (int i = 0; i < Matrix::getInstance()->COL_NUM; i++){
		if ((x<=i* ELEMENT_WIDTH + ELEMENT_WIDTH + MARGIN_LEFT)&&
			(x>i* ELEMENT_WIDTH  + MARGIN_LEFT)){
			
			pos_x = i;
			CCLOG("pos_x=%d", pos_x);
			break;
		}
	}

	for (int i = 0; i < Matrix::getInstance()->ROW_NUM; i++){
		if ((y <= i * ELEMENT_WIDTH + MARGIN_BOTTOM + ELEMENT_WIDTH)&&
			y > i* ELEMENT_WIDTH + MARGIN_BOTTOM){
			pos_y = i;
			CCLOG("pos_y=%d", pos_y);
			break;
		}
	}
	vector<int> temp;
	temp.push_back(pos_x);
	temp.push_back(pos_y);

	if (pos_x < Matrix::getInstance()->COL_NUM && pos_y <  Matrix::getInstance()->ROW_NUM) {
		return temp;
	}
	else{
		CCLOG("pos_ over");
		temp.push_back(-1);
		temp.push_back(-1);
		return temp;
	}
}

void  GameLayer::deawLine(int x1, int y1, int x2, int y2,bool line){
	if (x1 == x2){
		float pos_x1 = getPosByPostion(Matrix::getInstance()->getPositionByXAndY(x1,y1)).x;
		float pos_y1 = getPosByPostion(Matrix::getInstance()->getPositionByXAndY(x1,y1)).y;

		if (!line){
			if (x1 == Matrix::getInstance()->COL_NUM - 1){
				pos_x1 += 65;
				deawLine(x1, y1, x1 + 1, y1,true);
				deawLine(x2, y2, x2 + 1, y2,true);
			}
			else if (x1 == 0){
				pos_x1 -= 65;
				deawLine(x1, y1, x1 - 1, y1, true);
				deawLine(x2, y2, x2 - 1, y2, true);
			}
		}
		auto DL = Sprite::create("conn_line_v_1.png");
		DL->setPosition(pos_x1, pos_y1 + (y2 - y1) * 35);
		if (y2 < 0 || y2 == Matrix::getInstance()->ROW_NUM){

			DL->setScaleY(0.15*(abs(y2 - y1)));
		}
		else{
			DL->setScaleY(0.18*(abs(y2 - y1)));
		}


		this->addChild(DL);
		auto animation22 = Animation::create();
		for (int i = 1; i < 4; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "conn_line_v_%1d.png", i);
			animation22->addSpriteFrameWithFile(szName);
		}
		animation22->setDelayPerUnit(0.2f / 3);
		animation22->setRestoreOriginalFrame(true);
		auto animate2 = Animate::create(animation22);
		auto act1 = Sequence::create(animate2, FadeOut::create(0), nullptr);
		DL->runAction(act1);
	}
	else if (y1 == y2){
		float pos_x1 = getPosByPostion(Matrix::getInstance()->getPositionByXAndY(x1, y1)).x;
		float pos_y1 = getPosByPostion(Matrix::getInstance()->getPositionByXAndY(x1, y1)).y;

		if ((!line)){
			if (y1 == Matrix::getInstance()->ROW_NUM - 1){
				pos_y1 += 65;
				deawLine(x1, y1, x1, y1 + 1, true);
				deawLine(x2, y2, x2, y2 + 1, true);
			}
			else if (y1 == 0){
				pos_y1 -= 65;
				deawLine(x1, y1, x1, y1 - 1, true);
				deawLine(x2, y2, x2, y2 - 1, true);
			}
		}
		
		auto DL = Sprite::create("conn_line_h_1.png");
		DL->setPosition(pos_x1 + (x2 - x1) * 35, pos_y1);
		if (x2< 0 || x2 == Matrix::getInstance()->COL_NUM){

			DL->setScaleX(0.15*(abs(x2 - x1)));
		}
		else{
			DL->setScaleX(0.19*(abs(x2 - x1)));
		}


		this->addChild(DL);
		auto animation22 = Animation::create();
		for (int i = 1; i < 4; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "conn_line_h_%1d.png", i);
			animation22->addSpriteFrameWithFile(szName);
		}
		animation22->setDelayPerUnit(0.2f / 3);
		animation22->setRestoreOriginalFrame(true);
		auto animate2 = Animate::create(animation22);
		auto act1 = Sequence::create(animate2, FadeOut::create(0), nullptr);
		DL->runAction(act1);
		
	
		
	}
}
void  GameLayer::dealConnectANim(){

	Audio::getInstance()->cleanitem();
	std::vector<int> changePos = Matrix::getInstance()->getRoadChangePos();
	int x1 = Matrix::getInstance()->getXByCellPosition(clickitem[0]);
	int x2 = Matrix::getInstance()->getXByCellPosition(clickitem[1]);
	int y1 = Matrix::getInstance()->getYByCellPosition(clickitem[0]);
	int y2 = Matrix::getInstance()->getYByCellPosition(clickitem[1]);
	//CCLOG("changePos.size()=%d" , changePos.size());
	if (changePos.size()==0){
		//pos1,pos2直连
		deawLine(x1, y1, x2, y2, true);
	}
	else if (changePos.size()==1){
		int x3 = Matrix::getInstance()->getXByCellPosition(changePos[0]);
		int y3 = Matrix::getInstance()->getYByCellPosition(changePos[0]);
		deawLine(x1, y1, x3, y3, true);
		deawLine(x3, y3, x2, y2, true);
	}
	else if (changePos.size() == 2){
		int x3 = Matrix::getInstance()->getXByCellPosition(changePos[0]);
		int y3 = Matrix::getInstance()->getYByCellPosition(changePos[0]);
		int x4 = Matrix::getInstance()->getXByCellPosition(changePos[1]);
		int y4 = Matrix::getInstance()->getYByCellPosition(changePos[1]);
		//CCLOG("deawLine x1=%d,x2=%d,x3=%d,x4=%d,y1=%d,y2=%d,y3=%d,y4=%d",x1,x2,x3,x4,y1,y2,y3,y4);
		if (x1==x3){
			if (y1!=y3){
				deawLine(x3, y3, x1, y1, true);
			}
			if (y2!= y4){
				deawLine(x4, y4, x2, y2, true);
			}
		}else if (x1==x4){
			if (y1 != y4){
				deawLine(x4, y4, x1, y1, true);
			}
			if (y2 != y3){
				deawLine(x3, y3, x2, y2, true);
			}
		}
		else if (y1 == y3){
			if (x1 != x3){
				deawLine(x3, y3, x1, y1, true);
			}
			if (x2 != x4){
				deawLine(x4, y4, x2, y2, true);
			}
		}
		else if (y1 == y4){
			if (x1 != x4){
				deawLine(x4, y4, x1, y1, true);
			}
			if (x2 != x3){
				deawLine(x3, y3, x2, y2, true);
			}
		}

		if (Matrix::getInstance()->boardLine){
			deawLine(x4, y4, x3, y3, false);
		}
		else{
			deawLine(x4, y4, x3, y3, true);
		}
	}

	//TODO:显示连击数
	doubleHitCount++;
	auto sprite2 = Sprite::create("game_conn_icon.png");
	sprite2->setPosition(280, 400);
	auto action = Sequence::create(
		MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(0),
		nullptr);
	sprite2->runAction(action);
	//int 转 string
	CCString* ns = CCString::createWithFormat("%d", doubleHitCount);
	string s = ns->_string;

	auto sprite_num = LabelAtlas::create(s, "game_conn_txt.png", 41, 47, '0');
	sprite_num->setPosition(280+49, 375);
	auto action2 = Sequence::create(
		MoveBy::create(1.0f, Vec2(0, 100)), FadeOut::create(0),
		nullptr);
	sprite_num->runAction(action2);
	addChild(sprite_num);
	addChild(sprite2);

	if (doubleHitCount==1){
		//写一个1.5s的定时器
		schedule(schedule_selector(GameLayer::dealDoubleHit), 1.5f, 0, 0);
	}
}
	
void GameLayer::dealDoubleHit(float dt){
	doubleHitCount = 0;
}

