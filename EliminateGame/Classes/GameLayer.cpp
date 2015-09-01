#include "GameLayer.h"
#include "Monster.h"
#include "GameData.h"

#define MATRIX_WIDTH (7)
#define MATRIX_HEIGHT (9)

#define MONSTER_GAP (1)

GameLayer::GameLayer()
	: m_matrix(NULL)
	, m_width(0)
	, m_height(0)
	, m_matrixLeftBottomX(0)
	, m_matrixLeftBottomY(0)
	, m_isNeedFillVacancies(false)
	, m_isAnimationing(true)//start with drop animation
	, m_isTouchEnable(true)
	, m_srcMonster(NULL)
	, m_destMonster(NULL)
	, m_movingVertical(true)//drop animation is vertical
{
}

GameLayer::~GameLayer()
{
	if (m_matrix) {
		free(m_matrix);
	}
}


bool GameLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	GAMEDATA::getInstance()->init();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("monster.plist");
	// background
	Size winSize = Director::getInstance()->getWinSize();
	auto background = Sprite::create("game_bg.png");
	background->setAnchorPoint(Point(0, 1));
	background->setPosition(Point(0, winSize.height));
	this->addChild(background, -1);

	// you can load this value from other module.
	m_width = MATRIX_WIDTH;
	m_height = MATRIX_HEIGHT;

	// init position value
	m_matrixLeftBottomX = (winSize.width - Monster::getContentWidth() * m_width - (m_width - 1) * MONSTER_GAP) / 2;
	m_matrixLeftBottomY = (winSize.height - Monster::getContentWidth() * m_height - (m_height - 1) * MONSTER_GAP) / 2;

	// init point array
	int arraySize = sizeof(Monster *) * m_width * m_height;
	m_matrix = (Monster **)malloc(arraySize);
	memset((void*)m_matrix, 0, arraySize);

	initMatrix();
	scheduleUpdate();

	// bind touch event
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

Monster *GameLayer::monsterOfPoint(Point *point)
{
	Monster *monster = NULL;
	Rect rect = Rect(0, 0, 0, 0);

	for (int i = 0; i < m_height * m_width; i++) {
		monster = m_matrix[i];
		if (monster) {
			rect.origin.x = monster->getPositionX() - (monster->getContentSize().width / 2);
			rect.origin.y = monster->getPositionY() - (monster->getContentSize().height / 2);
			rect.size = monster->getContentSize();
			if (rect.containsPoint(*point)) {
				return monster;
			}
		}
	}

	return NULL;
}

bool GameLayer::onTouchBegan(Touch *touch, Event *unused)
{
	m_srcMonster = NULL;
	m_destMonster = NULL;
	if (m_isTouchEnable) {
		auto location = touch->getLocation();
		m_srcMonster = monsterOfPoint(&location);
	}
	return m_isTouchEnable;
}

void GameLayer::onTouchMoved(Touch *touch, Event *unused)
{
	if (!m_srcMonster || !m_isTouchEnable) {
		return;
	}

	int row = m_srcMonster->getRow();
	int col = m_srcMonster->getCol();

	auto location = touch->getLocation();
	auto halfMonterWidth = m_srcMonster->getContentSize().width / 2;
	auto halfMonterHeight = m_srcMonster->getContentSize().height / 2;

	auto  upRect = Rect(m_srcMonster->getPositionX() - halfMonterWidth,
		m_srcMonster->getPositionY() + halfMonterHeight,
		m_srcMonster->getContentSize().width,
		m_srcMonster->getContentSize().height);

	if (upRect.containsPoint(location)) {
		row++;
		if (row < m_height) {
			m_destMonster = m_matrix[row * m_width + col];
		}
		m_movingVertical = true;
		swapMonster();
		return;
	}

	auto  downRect = Rect(m_srcMonster->getPositionX() - halfMonterWidth,
		m_srcMonster->getPositionY() - (halfMonterHeight * 3),
		m_srcMonster->getContentSize().width,
		m_srcMonster->getContentSize().height);

	if (downRect.containsPoint(location)) {
		row--;
		if (row >= 0) {
			m_destMonster = m_matrix[row * m_width + col];
		}
		m_movingVertical = true;
		swapMonster();
		return;
	}

	auto  leftRect = Rect(m_srcMonster->getPositionX() - (halfMonterWidth * 3),
		m_srcMonster->getPositionY() - halfMonterHeight,
		m_srcMonster->getContentSize().width,
		m_srcMonster->getContentSize().height);

	if (leftRect.containsPoint(location)) {
		col--;
		if (col >= 0) {
			m_destMonster = m_matrix[row * m_width + col];
		}
		m_movingVertical = false;
		swapMonster();
		return;
	}

	auto  rightRect = Rect(m_srcMonster->getPositionX() + halfMonterWidth,
		m_srcMonster->getPositionY() - halfMonterHeight,
		m_srcMonster->getContentSize().width,
		m_srcMonster->getContentSize().height);

	if (rightRect.containsPoint(location)) {
		col++;
		if (col < m_width) {
			m_destMonster = m_matrix[row * m_width + col];
		}
		m_movingVertical = false;
		swapMonster();
		return;
	}
	// not a useful movement
}

void GameLayer::swapMonster()
{
	m_isAnimationing = true;
	m_isTouchEnable = false;
	if (!m_srcMonster || !m_destMonster) {
		m_movingVertical = true;
		return;
	}

	Point posOfSrc = m_srcMonster->getPosition();
	Point posOfDest = m_destMonster->getPosition();
	float time = 0.2;

	// 1.swap in matrix
	m_matrix[m_srcMonster->getRow() * m_width + m_srcMonster->getCol()] = m_destMonster;
	m_matrix[m_destMonster->getRow() * m_width + m_destMonster->getCol()] = m_srcMonster;
	int tmpRow = m_srcMonster->getRow();
	int tmpCol = m_srcMonster->getCol();
	m_srcMonster->setRow(m_destMonster->getRow());
	m_srcMonster->setCol(m_destMonster->getCol());
	m_destMonster->setRow(tmpRow);
	m_destMonster->setCol(tmpCol);

	// 2.check for remove able
	std::list<Monster *> colChainListOfFirst;
	getColChain(m_srcMonster, colChainListOfFirst);

	std::list<Monster *> rowChainListOfFirst;
	getRowChain(m_srcMonster, rowChainListOfFirst);

	std::list<Monster *> colChainListOfSecond;
	getColChain(m_destMonster, colChainListOfSecond);

	std::list<Monster *> rowChainListOfSecond;
	getRowChain(m_destMonster, rowChainListOfSecond);

	if (colChainListOfFirst.size() >= 3
		|| rowChainListOfFirst.size() >= 3
		|| colChainListOfSecond.size() >= 3
		|| rowChainListOfSecond.size() >= 3) {
		// just swap
		m_srcMonster->runAction(MoveTo::create(time, posOfDest));
		m_destMonster->runAction(MoveTo::create(time, posOfSrc));
		return;
	}

	// 3.no chain, swap back
	m_matrix[m_srcMonster->getRow() * m_width + m_srcMonster->getCol()] = m_destMonster;
	m_matrix[m_destMonster->getRow() * m_width + m_destMonster->getCol()] = m_srcMonster;
	tmpRow = m_srcMonster->getRow();
	tmpCol = m_srcMonster->getCol();
	m_srcMonster->setRow(m_destMonster->getRow());
	m_srcMonster->setCol(m_destMonster->getCol());
	m_destMonster->setRow(tmpRow);
	m_destMonster->setCol(tmpCol);

	m_srcMonster->runAction(Sequence::create(
		MoveTo::create(time, posOfDest),
		MoveTo::create(time, posOfSrc),
		NULL));
	m_destMonster->runAction(Sequence::create(
		MoveTo::create(time, posOfSrc),
		MoveTo::create(time, posOfDest),
		NULL));
}

void GameLayer::update(float dt)
{
	// check if animationing
	if (m_isAnimationing) {
		// init with false
		m_isAnimationing = false;
		for (int i = 0; i < m_height * m_width; i++) {
			Monster *mon = m_matrix[i];
			if (mon && mon->getNumberOfRunningActions() > 0) {
				m_isAnimationing = true;
				break;
			}
		}
	}

	// if Monter is moving, ignore use touch event
	m_isTouchEnable = !m_isAnimationing;

	if (!m_isAnimationing) {
		if (m_isNeedFillVacancies) {
			//爆炸效果结束后才掉落新怪物，增强打击感
			fillVacancies();
			m_isNeedFillVacancies = false;
		}
		else {
			checkAndRemoveChain();
		}
	}
}

//横向chain检查
void GameLayer::getColChain(Monster *monster, std::list<Monster *> &chainList)
{
	chainList.push_back(monster);// add first Monter

	int neighborCol = monster->getCol() - 1;
	while (neighborCol >= 0) {
		Monster *neighborMonster = m_matrix[monster->getRow() * m_width + neighborCol];
		if (neighborMonster
			&& (neighborMonster->getImgIndex() == monster->getImgIndex())
			&& !neighborMonster->getIsNeedRemove()
			&& !neighborMonster->getIgnoreCheck()) {
			chainList.push_back(neighborMonster);
			neighborCol--;
		}
		else {
			break;
		}
	}

	neighborCol = monster->getCol() + 1;
	while (neighborCol < m_width) {
		Monster *neighborMonster = m_matrix[monster->getRow() * m_width + neighborCol];
		if (neighborMonster
			&& (neighborMonster->getImgIndex() == monster->getImgIndex())
			&& !neighborMonster->getIsNeedRemove()
			&& !neighborMonster->getIgnoreCheck()) {
			chainList.push_back(neighborMonster);
			neighborCol++;
		}
		else {
			break;
		}
	}
}

void GameLayer::getRowChain(Monster *monster, std::list<Monster *> &chainList)
{
	chainList.push_back(monster);// add first monster

	int neighborRow = monster->getRow() - 1;
	while (neighborRow >= 0) {
		Monster *neighborMonster = m_matrix[neighborRow * m_width + monster->getCol()];
		if (neighborMonster
			&& (neighborMonster->getImgIndex() == monster->getImgIndex())
			&& !neighborMonster->getIsNeedRemove()
			&& !neighborMonster->getIgnoreCheck()) {
			chainList.push_back(neighborMonster);
			neighborRow--;
		}
		else {
			break;
		}
	}

	neighborRow = monster->getRow() + 1;
	while (neighborRow < m_height) {
		Monster *neighborMonster = m_matrix[neighborRow * m_width + monster->getCol()];
		if (neighborMonster
			&& (neighborMonster->getImgIndex() == monster->getImgIndex())
			&& !neighborMonster->getIsNeedRemove()
			&& !neighborMonster->getIgnoreCheck()) {
			chainList.push_back(neighborMonster);
			neighborRow++;
		}
		else {
			break;
		}
	}
}

void GameLayer::fillVacancies()
{
	// reset moving direction flag
	m_movingVertical = true;
	m_isAnimationing = true;

	Size size = CCDirector::getInstance()->getWinSize();
	int *colEmptyInfo = (int *)malloc(sizeof(int) * m_width);
	memset((void *)colEmptyInfo, 0, sizeof(int) * m_width);

	// 1. drop exist monster
	Monster *monster = NULL;
	for (int col = 0; col < m_width; col++) {
		int removedMonterOfCol = 0;
		// from buttom to top
		for (int row = 0; row < m_height; row++) {
			monster = m_matrix[row * m_width + col];
			if (NULL == monster) {
				removedMonterOfCol++;
			}
			else {
				if (removedMonterOfCol > 0) {
					// evey item have its own drop distance
					int newRow = row - removedMonterOfCol;
					// switch in matrix
					m_matrix[newRow * m_width + col] = monster;
					m_matrix[row * m_width + col] = NULL;
					// move to new position
					Point startPosition = monster->getPosition();
					Point endPosition = positionOfItem(newRow, col);
					float speed = (startPosition.y - endPosition.y) / size.height;
					monster->stopAllActions();// must stop pre drop action
					monster->runAction(CCMoveTo::create(speed, endPosition));
					// set the new row to item
					monster->setRow(newRow);
				}
			}
		}

		// record empty info
		colEmptyInfo[col] = removedMonterOfCol;
	}

	// 2. create new item and drop down.
	for (int col = 0; col < m_width; col++) {
		for (int row = m_height - colEmptyInfo[col]; row < m_height; row++) {
			createAndDropMonster(row, col);
		}
	}

	free(colEmptyInfo);
}

void GameLayer::removeMonster()
{
	// make sequence remove
	m_isAnimationing = true;
	for (int i = 0; i < m_height * m_width; i++) {
		Monster *monster = m_matrix[i];
		if (!monster) {
			continue;
		}

		if (monster->getIsNeedRemove()) {
			m_isNeedFillVacancies = true;//需要掉落
			//播放消失的动画
			explodeMonster(monster);
		}
	}
}


void GameLayer::calculateScore(int number){
	if (number > 0){
		int totalScore = 0;
		for (int i = 1; i <= number; i++){
			totalScore += i * 5;
		}
		int score = GAMEDATA::getInstance()->getScore() + totalScore;
		GAMEDATA::getInstance()->setScore(score);
		countRemoveMonster = 0;
	}
}


void GameLayer::actionEndCallback(Node *node)
{
	Monster *monster = (Monster *)node;
	m_matrix[monster->getRow() * m_width + monster->getCol()] = NULL;
	monster->removeFromParent();
}

void GameLayer::explodeMonster(Monster *monster)
{
	float time = 0.3;
	// 1. action for Monter
	monster->runAction(Sequence::create(
		ScaleTo::create(time, 0.0),
		CallFuncN::create(CC_CALLBACK_1(GameLayer::actionEndCallback, this)),
		NULL));

	// 2. action for circle
	auto circleSprite = Sprite::create("circle.png");
	addChild(circleSprite, 10);
	circleSprite->setPosition(monster->getPosition());
	circleSprite->setScale(0);// start size
	circleSprite->runAction(Sequence::create(ScaleTo::create(time, 1.0),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, circleSprite)),
		NULL));

	// 3. particle effect
	auto particleStars = ParticleSystemQuad::create("stars.plist");
	particleStars->setAutoRemoveOnFinish(true);
	particleStars->setBlendAdditive(false);
	particleStars->setPosition(monster->getPosition());
	particleStars->setScale(0.3);
	addChild(particleStars, 20);
}

void GameLayer::checkAndRemoveChain()
{
	Monster *monster;
	// 1. reset ingnore flag
	for (int i = 0; i < m_height * m_width; i++) {
		monster = m_matrix[i];
		if (!monster) {
			continue;
		}
		monster->setIgnoreCheck(false);
	}

	// 2. check chain
	for (int i = 0; i < m_height * m_width; i++) {
		monster = m_matrix[i];
		if (!monster) {
			continue;
		}

		if (monster->getIsNeedRemove()) {
			continue;// 已标记过的跳过检查
		}
		if (monster->getIgnoreCheck()) {
			continue;// 新变化的特殊monster，不消除
		}

		// start count chain
		std::list<Monster *> colChainList;
		getColChain(monster, colChainList);

		std::list<Monster *> rowChainList;
		getRowChain(monster, rowChainList);

		std::list<Monster *> &longerList = colChainList.size() > rowChainList.size() ? colChainList : rowChainList;
		if (longerList.size() < 3) {
			continue;// 小于3个不消除
		}
		countRemoveMonster = longerList.size();
		std::list<Monster *>::iterator itList;
		bool isSetedIgnoreCheck = false;
		for (itList = longerList.begin(); itList != longerList.end(); itList++) {
			monster = (Monster *)*itList;
			if (!monster) {
				continue;
			}

			if (longerList.size() > 3) {
				if (monster == m_srcMonster || monster == m_destMonster) {
					isSetedIgnoreCheck = true;
					monster->setIgnoreCheck(true);
					//4消特殊元素先关闭
					monster->setIsNeedRemove(true);
					//monster->setDisplayMode(m_movingVertical ? DISPLAY_MODE_VERTICAL : DISPLAY_MODE_HORIZONTAL);
					continue;
				}
			}
			markRemove(monster);
		}

		// 如何是自由掉落产生的4消, 取最后一个变化为特殊怪物
		if (!isSetedIgnoreCheck && longerList.size() > 3) {
			monster->setIgnoreCheck(true);
			//4消特殊元素先关闭
			monster->setIsNeedRemove(true);
			//monster->setDisplayMode(m_movingVertical ? DISPLAY_MODE_VERTICAL : DISPLAY_MODE_HORIZONTAL);
		}
	}

	// 3.消除标记了的怪物
	removeMonster();
    // 4.计算消除的分数
	//计算消除得分
	calculateScore(countRemoveMonster);
}

void GameLayer::markRemove(Monster *Monter)
{
	if (Monter->getIsNeedRemove()) {
		return;
	}
	if (Monter->getIgnoreCheck()) {
		return;
	}

	// mark self
	Monter->setIsNeedRemove(true);
	// check for type and mark for certical neighbour
	if (Monter->getDisplayMode() == DISPLAY_MODE_VERTICAL) {
		for (int row = 0; row < m_height; row++) {
			Monster *tmp = m_matrix[row * m_width + Monter->getCol()];
			if (!tmp || tmp == Monter) {
				continue;
			}

			if (tmp->getDisplayMode() == DISPLAY_MODE_NORMAL) {
				tmp->setIsNeedRemove(true);
			}
			else {
				markRemove(tmp);
			}
		}
		// check for type and mark for horizontal neighbour
	}
	else if (Monter->getDisplayMode() == DISPLAY_MODE_HORIZONTAL) {
		for (int col = 0; col < m_width; col++) {
			Monster *tmp = m_matrix[Monter->getRow() * m_width + col];
			if (!tmp || tmp == Monter) {
				continue;
			}

			if (tmp->getDisplayMode() == DISPLAY_MODE_NORMAL) {
				tmp->setIsNeedRemove(true);
			}
			else {
				markRemove(tmp);
			}
		}
	}
}

void GameLayer::initMatrix()
{
	for (int row = 0; row < m_height; row++) {
		for (int col = 0; col < m_width; col++) {
			createAndDropMonster(row, col);
		}
	}
}

void GameLayer::createAndDropMonster(int row, int col)
{
	Size size = Director::getInstance()->getWinSize();

	Monster *monster = Monster::create(row, col);

	// create animation
	Point endPosition = positionOfItem(row, col);
	Point startPosition = Point(endPosition.x, endPosition.y + size.height / 2);
	monster->setPosition(startPosition);
	float speed = startPosition.y / (1.5 * size.height);
	monster->runAction(MoveTo::create(speed, endPosition));
	this->addChild(monster);

	m_matrix[row * m_width + col] = monster;
}

Point GameLayer::positionOfItem(int row, int col)
{
	float x = m_matrixLeftBottomX + (Monster::getContentWidth() + MONSTER_GAP) * col + Monster::getContentWidth() / 2;
	float y = m_matrixLeftBottomY + (Monster::getContentWidth() + MONSTER_GAP) * row + Monster::getContentWidth() / 2;
	return Point(x, y);
}
