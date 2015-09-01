#include "StarMatrix.h"
#include "GameData.h"
#include "StarParticle.h"
#include "ComboEffect.h"
#include "Audio.h"
#include "OvalActionInterval.h"
#include <ctime>

bool StarMatrix::BombClick = false;
bool StarMatrix::HammerClick= false;
bool StarMatrix::MagicClick = false;
bool StarMatrix::RainBowClick = false;
bool StarMatrix::removeAnim = false;
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
	isShowAnim = false;
	acceptTouch = true;
	clearSumTime = 0;
	selectedListSize = 0;
	animSprite=nullptr;
	memset(stars, 0, sizeof(Star*) * ROW_NUM * COL_NUM);
	initMatrix();
	scheduleUpdate();
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
	if(s && acceptTouch){
		clearOneByOne = true;
		if(BombClick){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()-1000);
			GAMEDATA::getInstance()->saveGoldNum();
			TopMenu::getInstance()->refreshGold();
			/*if(animSprite->getTag()==(s->getIndexI()*COL_NUM+s->getIndexJ())){*/
			useBombAuto(s);
			m_layer->hidePropInfos();
			/*}else{
				setBombPosition(s);
			}*/
			return;
		}else if(HammerClick){
			if(GAMEDATA::getInstance()->getChuiNum() > 0){
				GAMEDATA::getInstance()->setChuiNum(0);
				GAMEDATA::getInstance()->saveChuiNum();
			}else{
				GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()-800);
				GAMEDATA::getInstance()->saveGoldNum();
				TopMenu::getInstance()->refreshGold();
			}
		/*	if(animSprite->getTag()==(s->getIndexI()*COL_NUM+s->getIndexJ())){*/
			doHammer(s);
			m_layer->hidePropInfos();
			/*}else{
				setHammerPosition(s);
			}*/
			return;
		}else if(MagicClick){
			if(GAMEDATA::getInstance()->getBiNum() > 0){
				GAMEDATA::getInstance()->setBiNum(0);
				GAMEDATA::getInstance()->saveBiNum();
			}else{
				GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()-800);
				GAMEDATA::getInstance()->saveGoldNum();
				TopMenu::getInstance()->refreshGold();
			}
			/*if(animSprite->getTag()==(s->getIndexI()*COL_NUM+s->getIndexJ())){*/
			doMagic(s);
			m_layer->hidePropInfos();
			/*}else{
				setMagicposition(s);
			}*/
			return;	
		}else if(RainBowClick){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()-600);
			GAMEDATA::getInstance()->saveGoldNum();
			TopMenu::getInstance()->refreshGold();
			doRainbow();
			m_layer->hidePropInfos();
			return;	
		}
		genSelectedList(s);
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


void StarMatrix::doHammer(Star* s){
	selectedList.clear();
	selectedList.push_back(s);
	//播放消除音效
	Audio::getInstance()->playPropBomb();
	selectedList.pop_front();
	m_layer->showEveryScore(selectedListSize,5+(selectedListSize-selectedList.size())*5,selectedListSize-selectedList.size(),s->getPosition(),touchLeft);
	//粒子效果
	showStarParticleEffect(s->getColor(),s->getPosition(),this);
	stars[s->getIndexI()][s->getIndexJ()] = nullptr;
	s->removeFromParentAndCleanup(true);
	m_layer->showLinkNum(selectedListSize);

	selectedListSize=0;
	acceptTouch =true;
	adjustMatrix();
	if(isEnded()){
		acceptTouch=false;
		m_layer->hideProps();
		m_layer->floatLeftStarMsg(getLeftStarNum());//通知layer弹出剩余星星的信息
		CCLOG("ENDED");
	}
}

void StarMatrix::doMagic(Star* s){
	s->changeColor(5);
}

void StarMatrix::doRainbow(){
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			if(stars[i][j] != nullptr){
				auto col= random(0,3);
				stars[i][j]->changeColor(col);
			}      
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
	int color = s->getColor();
	for(it= travelList.begin();it != travelList.end();){
		Star* star = *it;
		Star* linkStar = nullptr;
		int index_i = star->getIndexI();
		int index_j = star->getIndexJ();
		//上
		if(index_i-1 >= 0 && (linkStar = stars[index_i-1][index_j]) ){
			if(!linkStar->isSelected()){
				if(star->getColor()==5&&linkStar->getColor()==color){
					travelList.push_back(stars[index_i-1][index_j]);		
				}else if((linkStar->getColor() == star->getColor()||linkStar->getColor()==5)){
					travelList.push_back(stars[index_i-1][index_j]);				
				}
			}
		}
		//下
		if(index_i+1 < ROW_NUM  && (linkStar = stars[index_i+1][index_j]) ){			
			if(!linkStar->isSelected()){
				if(star->getColor()==5&&linkStar->getColor()==color){
					travelList.push_back(stars[index_i+1][index_j]);
				}else if((linkStar->getColor() == star->getColor()||linkStar->getColor()==5)){
					travelList.push_back(stars[index_i+1][index_j]);		
				}
			}
		}
		//左
		if(index_j-1 >= 0 && (linkStar = stars[index_i][index_j-1]) ){
			if(!linkStar->isSelected()){
				if(star->getColor()==5&&linkStar->getColor()==color){
					travelList.push_back(stars[index_i][index_j-1]);
				}else if((linkStar->getColor() == star->getColor()||linkStar->getColor()==5)){
					travelList.push_back(stars[index_i][index_j-1]);	
				}
			}
		}
		//右
		if(index_j+1 < COL_NUM && (linkStar = stars[index_i][index_j+1]) ){				
			if(!linkStar->isSelected()){
				if(star->getColor()==5&&linkStar->getColor()==color){
					travelList.push_back(stars[index_i][index_j+1]);
				}else if((linkStar->getColor() == star->getColor()||linkStar->getColor()==5)){
					travelList.push_back(stars[index_i][index_j+1]);
				}
			}
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
		m_layer->showEveryScore(selectedListSize,5+(selectedListSize-selectedList.size())*5,selectedListSize-selectedList.size(),star->getPosition(),touchLeft);
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
	m_layer->showLinkNum(selectedListSize);
	selectedListSize=0;
	acceptTouch =true;
	adjustMatrix();
	if(isEnded()){
		acceptTouch=false;
		m_layer->hideProps();
		m_layer->floatLeftStarMsg(getLeftStarNum());//通知layer弹出剩余星星的信息
		CCLOG("ENDED");
	}
}

void StarMatrix::deleteBombList(){
	//播放消除音效
	Audio::getInstance()->playPropBomb();
	for(auto it = selectedList.begin();it != selectedList.end();it++){
		Star* star = *it;
		//粒子效果
		showStarParticleEffect(star->getColor(),star->getPosition(),this);
		stars[star->getIndexI()][star->getIndexJ()] = nullptr;
		star->removeFromParentAndCleanup(true);
	}
	selectedList.clear();
	//COMBO效果
	selectedListSize=0;
	acceptTouch =true;
	adjustMatrix();
	if(isEnded()){
		acceptTouch=false;
		m_layer->hideProps();
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




bool StarMatrix::isEnded(){
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
	if(GAMEDATA::getInstance()->getCurScore() >= GAMEDATA::getInstance()->getNextScore()){
		GAMEDATA::getInstance()->setCurLevel(GAMEDATA::getInstance()->getCurLevel() + 1);
		m_layer->gotoNextLevel();
	}else{
		m_layer->gotoGameOver();
		CCLOG("GAME OVER");
	}
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


Animation* StarMatrix::createAnimation(std::string prefixName, int framesNum, float delay)
{
	Vector<SpriteFrame*> animFrames;
	for (int i = 1; i <= framesNum; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "_%i.png",i);
		std::string str =  prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(animFrames, delay);
}


Star* StarMatrix::getHammerStar(){
	//先检查第五列,依次向左
	for(int j=4;j<COL_NUM;j++){
		for(int i=5;i<ROW_NUM;i++){
			if(stars[i][j] != nullptr)
				return stars[i][j];	
		}
	}
	return stars[9][0];
}

//显示锤子动画
void StarMatrix::showHammerAnim(){
	animSprite=Sprite::create();
	animSprite->setAnchorPoint(Point(0,0));
	this->addChild(animSprite);
	auto anim = createAnimation("anim_hammer",5,0.2f);
	Animate* mate =Animate::create(anim);
	Star* s= getHammerStar();
	animSprite->setPosition(s->getPosition());
	int index_i = s->getIndexI();
	int index_j = s->getIndexJ();
	CCLOG("X= %d",index_i);
	CCLOG("Y= %d",index_j);
	animSprite->setTag(index_i*COL_NUM+index_j);
	animSprite->runAction(RepeatForever::create(mate));
}
//显示画笔动画
void StarMatrix::showMagicAnim(){
	animSprite=Sprite::create("anim_magic.png");
	animSprite->setAnchorPoint(Point(0,0));
	Star* s= getHammerStar();
	animSprite->setPosition(s->getPosition());
	int index_i = s->getIndexI();
	int index_j = s->getIndexJ();
	animSprite->setTag(index_i*COL_NUM+index_j);
	this->addChild(animSprite);	
	OvalConfig config;
	config.a = 12;
	config.b = 12;
	config.centerPosition = animSprite->getPosition();
	config.moveInAnticlockwise = true;
	config.zOrder = make_pair(-1, 0);
	auto moveAction = MoveOvalBy::create(1.0, config);
	animSprite->runAction(RepeatForever::create(moveAction));
}
//显示重排动画
void StarMatrix::showRainbowAnim(){
	auto visibleSize = Director::getInstance()->getVisibleSize();
    animSprite=Sprite::create("anim_redo.png");
	animSprite->setAnchorPoint(Point(0.5,0.5));
	animSprite->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(animSprite);
	auto rotate = RotateBy::create(1,90);
    animSprite->runAction(RepeatForever::create(rotate));
}
//显示炸弹动画
void StarMatrix::showBombAnim(){
	animSprite=Sprite::create("anim_redo.png");
	animSprite->setAnchorPoint(Point(0,0));
	Star* s= getHammerStar();
	animSprite->setPosition(s->getPosition());
	int index_i = s->getIndexI();
	int index_j = s->getIndexJ();
	animSprite->setTag(index_i*COL_NUM+index_j);
	this->addChild(animSprite);
	auto rotate = RotateBy::create(1,90);
    animSprite->runAction(RepeatForever::create(rotate));
}

void StarMatrix::removeAnimSprite(){
	isShowAnim=false;
	animSprite->removeFromParentAndCleanup(true);
}

void StarMatrix::setHammerPosition(Star* s){
	if(nullptr!=animSprite){
		animSprite->setPosition(s->getPosition());
		int index_i = s->getIndexI();
		int index_j = s->getIndexJ();
		animSprite->setTag(index_i*COL_NUM+index_j);
	}
}

void StarMatrix::setMagicposition(Star* s){
	if(nullptr!=animSprite){
		animSprite->stopAllActions();
		animSprite->setPosition(s->getPosition());
		int index_i = s->getIndexI();
		int index_j = s->getIndexJ();
		animSprite->setTag(index_i*COL_NUM+index_j);
		OvalConfig config;
		config.a = 12;
		config.b = 12;
		config.centerPosition = animSprite->getPosition();
		config.moveInAnticlockwise = true;
		config.zOrder = make_pair(-1, 0);
		MoveOvalBy* moveAction = MoveOvalBy::create(1.0, config);
		animSprite->runAction(RepeatForever::create(moveAction));}
}

void StarMatrix::setBombPosition(Star* s){
	if(nullptr!=animSprite){
		animSprite->setPosition(s->getPosition());
		int index_i = s->getIndexI();
		int index_j = s->getIndexJ();
		animSprite->setTag(index_i*COL_NUM+index_j);
	}
}

void StarMatrix::update(float dt){
	if(!isShowAnim){
		if(HammerClick){
			isShowAnim=true;
			//showHammerAnim();
		}else if(MagicClick){
			isShowAnim=true;
			//showMagicAnim();
		}else if(RainBowClick){
			isShowAnim=true;
			//showRainbowAnim();
		}else if(BombClick){
			isShowAnim=true;
			//showRainbowAnim();
		}
	
	}
	if(removeAnim){
		if(HammerClick){
			HammerClick=false;
			//removeAnimSprite();	
			removeAnim=false;
		}else if(MagicClick){
			MagicClick=false;
			//removeAnimSprite();	
			removeAnim=false;
		}
		else if(RainBowClick){
			RainBowClick=false;
			//removeAnimSprite();	
			removeAnim=false;
		}
		else if(BombClick){
			BombClick=false;
			//removeAnimSprite();	
			removeAnim=false;
		}
	}
}
