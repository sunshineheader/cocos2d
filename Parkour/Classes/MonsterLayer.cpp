#include "MonsterLayer.h"
#include "Monster.h"
#include "ObjectTag.h"
#include "PlayerState.h"
#include "GameStateInfo.h"
#include "GameState.h"
#include "GAMEDATA.h"
#include "TollgateScene.h"
#include "CallAndroidMethod.h"
#include "Audio.h"

Player* MonsterLayer::m_player = NULL;
InfoLayer* MonsterLayer::m_infoLayer = NULL;
int MonsterLayer::playerRowNum = 7;

MonsterLayer::MonsterLayer()
{
	
}
 
MonsterLayer::~MonsterLayer()
{
   SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("monster.plist");
}

MonsterLayer* MonsterLayer::createLayer(Player* player,InfoLayer* infoLayer){
	m_player = player;
	m_infoLayer = infoLayer;
	auto monsterLayer = MonsterLayer::create();
	return monsterLayer;
}
 
bool MonsterLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
	speed = TollgateScene::speed*TollgateScene::level;
	speed2 = TollgateScene::speed*TollgateScene::level*2;
	speed_x = 6*TollgateScene::level;
	speed_y = 2;
	distance = 0;
	totalOffset = 0;
	canSlide = true;
	canJump = true;
	needContiSlide = false;
	tag = 1;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("monster.plist");

    /* ���عؿ��Ĺ������� */
    loadMonstersFromTmxConf();
	float x = m_player->getPositionX();
	float y = m_player->getPositionY();
	CCLOG("x=%f",x);
	CCLOG("y=%f",y);
	loadNextMap(1);
    return true;
}

void MonsterLayer::loadMonstersFromTmxConf()
{
    /* ���ص�ͼ */
    auto map = TMXTiledMap::create("map_0.tmx");
	map->setTag(1);
    this->addChild(map);    
}

void MonsterLayer::loadNextMap(float shifting){
	 /* ���ص�ͼ */
	auto map = TMXTiledMap::create(String::createWithFormat("map_%d.tmx",tag%63)->_string);
	CCLOG("load map");
	tag ++;
	if(tag%63 == 0){
		TollgateScene::level = TollgateScene::level + 0.1*tag/63;
	}
	map->setTag(tag);
	map->setPositionX(800-totalOffset);
	auto objectGroup = map->getObjectGroup("monster");
	ValueVector objects = objectGroup->getObjects();
	if(objects.size() > 0){
		int propNum;
		for(auto monster : m_monsterVec){
			if(monster->getID() > 2){
				propNum ++;
			}
		}
		for(const auto monster : objects){
			const ValueMap dict = monster.asValueMap();
			int id = dict.at("id").asInt();
			int iPosX = dict.at("x").asInt();
			int iPosY = dict.at("y").asInt();
			if(id <= 2){
				auto m = Monster::create(id);
				m->setiPosX(iPosX+800-totalOffset);
				m->setiPosY(iPosY);
				m->joinToMap(this);
				m_monsterVec.pushBack(m);
			}else if(id == 3){
				if(Player::skillState == Player_Normal && propNum == 0){
					int ran = CCRANDOM_0_1() * 10000;
					if(ran%9 < 4){
						auto m = Monster::create(id);
						m->setiPosX(iPosX+800-totalOffset);
						m->setiPosY(iPosY);
						m->joinToMap(this);
						m_monsterVec.pushBack(m);
					}
				}
			}else if(id == 4){
				if(Player::skillState == Player_Normal && propNum == 0){
					int ran = CCRANDOM_0_1() * 10000;
					if(ran%9 < 4){
						auto m = Monster::create(id);
						m->setiPosX(iPosX+800-totalOffset);
						m->setiPosY(iPosY);
						m->joinToMap(this);
						m_monsterVec.pushBack(m);
					}
				}
			}else if(id == 5){
				if(Player::skillState == Player_Normal &&  propNum == 0){
					int ran = CCRANDOM_0_1() * 10000;
					if(ran%9 < 4){
						auto m = Monster::create(id);
						m->setiPosX(iPosX+800-totalOffset);
						m->setiPosY(iPosY);
						m->joinToMap(this);
						m_monsterVec.pushBack(m);
					}
				}
			}else if(id == 6){
				auto m = Monster::create(id);
				m->setiPosX(iPosX+800-totalOffset);
				m->setiPosY(iPosY);
				m->joinToMap(this);
				m_monsterVec.pushBack(m);
			}
		}
	}
	this->addChild(map);	
}

void MonsterLayer::logic(float dt)
{   
	speed = TollgateScene::speed*TollgateScene::level;
	speed2 = TollgateScene::speed*TollgateScene::level*2;
	speed_x = 6*TollgateScene::level;
	auto nowmap1 = (TMXTiledMap*)this->getChildByTag(tag-1);
	if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
		nowmap1->setPositionX(nowmap1->getPositionX()-speed2);
	}else{
		nowmap1->setPositionX(nowmap1->getPositionX()-speed);
	}

	auto nowmap2 = (TMXTiledMap*)this->getChildByTag(tag);
	if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
		nowmap2->setPositionX(nowmap2->getPositionX()-speed2);
	}else{
		nowmap2->setPositionX(nowmap2->getPositionX()-speed);
	}

	for (auto monster : m_monsterVec)
    {        
		if(monster->getPositionX() < -100){
			deleteMonsterVec.pushBack(monster);
		}
		monster->logic(dt);
		if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
			monster->setPositionX(monster->getPositionX()-speed2);
		}else{
			monster->setPositionX(monster->getPositionX()-speed);
		}
    }
	for(auto monster : deleteMonsterVec)
	{
		m_monsterVec.eraseObject(monster,false);
		monster->removeFromParentAndCleanup(true);
	}
	deleteMonsterVec.clear();

	for(auto monsterAnim : m_monsterAnim){
		if(monsterAnim->getPositionX() < -100){
			m_delMonsterAnim.pushBack(monsterAnim);
		}
		if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
			monsterAnim->setPositionX(monsterAnim->getPositionX()-speed2);
		}else{
			monsterAnim->setPositionX(monsterAnim->getPositionX()-speed);
		}
	}
	for(auto monsterAnim : m_delMonsterAnim){
		m_monsterAnim.eraseObject(monsterAnim,false);
		monsterAnim->removeFromParent();
	}

	for(auto gold : m_goldAnim){
		gold->setPositionX(gold->getPositionX()-3);
		gold->setPositionY(gold->getPositionY()+6);
		if(gold->getPositionY() > 480){
			m_delGoldAnim.pushBack(gold);
		}
	}
	for(auto gold : m_delGoldAnim){
		m_goldAnim.eraseObject(gold,false);
		gold->removeFromParent();
	}
	m_delGoldAnim.clear();

	checkCollision(nowmap1,nowmap2);
	if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
		distance += speed2;
	}else{
		distance += speed;
	}
	if(distance >= 800){
		totalOffset = totalOffset+distance-800;
		loadNextMap(totalOffset);
		distance = 0;
		this->getChildByTag(tag-2)->removeFromParentAndCleanup(true);
	}
}

bool MonsterLayer::checkCollision(TMXTiledMap* nowmap1,TMXTiledMap* nowmap2){
	if(Player::skillState == Player_Transition_Fly){
		auto stairLayer1 = nowmap1->getLayer("stair");
		int startCol1 = (200-nowmap1->getPositionX())/32;
		int indexY1 = playerRowNum+2;
		if(startCol1 >= 0){
			int endPos = 19+startCol1;
			if(endPos > 25){
				endPos = 25;
			}
			for(int i=startCol1;i<endPos;i++){
				bool needAddStair = true;
				for(int j=5;j<15;j++){
					int gid = stairLayer1->tileGIDAt(Vec2(i,j));
					if(gid != 9 && gid != 0){
						needAddStair = false;
						indexY1 = j;
						break;
					}
				}
				if(needAddStair){
					stairLayer1->setTileGID(i%2+3,Vec2(i,indexY1));
					stairLayer1->setTileGID(i%2+14,Vec2(i,indexY1+1));
				}
			}
		}
		auto stairLayer2= nowmap2->getLayer("stair");
		int startCol2 = (200-nowmap2->getPositionX())/32;
		int indexY2 = indexY1;
		if(startCol2 >= -19){
			int endPos = 19+startCol2;
			if(endPos > 25){
				endPos = 25;
			}
			if(startCol2 < 0){
				startCol2 = 0;
			}
			for(int i=startCol2;i<endPos;i++){
				bool needAddStair = true;
				for(int j=7;j<15;j++){
					int gid = stairLayer2->tileGIDAt(Vec2(i,j));
					if(gid != 9 && gid != 0){
						needAddStair = false;
						indexY2 = j;
						break;
					}
				}
				if(needAddStair){
					stairLayer2->setTileGID(i%2+3,Vec2(i,indexY2));
					stairLayer2->setTileGID(i%2+14,Vec2(i,indexY2+1));
				}
			}
		}
	}
	for(auto monster : m_monsterVec){
		if(checkSpritesCollision(m_player,monster)){
			if(monster->getID() == 1){		
				if(Player::skillState == Player_Normal || Player::skillState == Player_Magic){
					float x1 = m_player->getPositionX();
					float x2 = monster->getPositionX();
					if(x1-x2 < 24){
						GameStateInfo::getInstance()->setGameState(Game_End);
						return true;
					}
				}
			}else if(monster->getID() == 2){
				GAMEDATA::getInstance()->setDodgeMonsterNums(GAMEDATA::getInstance()->getDodgeMonsterNums()+1);float w1 = m_player->getContentSize().width;
				float h1 = m_player->getContentSize().height;
				float w2 = monster->getContentSize().width;
				float h2 = monster->getContentSize().height;
				float x1 = m_player->getPositionX();
				float y1 = m_player->getPositionY();
				float x2 = monster->getPositionX();
				float y2 = monster->getPositionY();
				if(Player::skillState == Player_Normal || Player::skillState == Player_Magic){
					if(y1-y2>h1/2+h2/2-50 && m_player->getUpSpeed() < 34){
						auto sp = Sprite::create("black_bg.png");
						sp->setPosition(monster->getPositionX(),monster->getPositionY());
						this->addChild(sp);
						m_monsterAnim.pushBack(sp);
						deleteMonsterVec.pushBack(monster);
						monster->removeFromParent();

						Vector<SpriteFrame*> monsterDiedFrames;
						SpriteFrame* frame;

						for(int i=0;i<8;i++){
							frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("monster_die_%d.png",i+1)->_string);
							monsterDiedFrames.pushBack(frame);
						}
						auto animation = Animation::createWithSpriteFrames(monsterDiedFrames,0.02f);
						monsterDiedAction = Animate::create(animation);
						sp->runAction(monsterDiedAction);

						Player::state = Player_Run;
						m_player->smallJump();
					}else{
						GAMEDATA::getInstance()->setDodgeMonsterNums(GAMEDATA::getInstance()->getDodgeMonsterNums()-1);
						GameStateInfo::getInstance()->setGameState(Game_End);
						return true;
					}
				}else{
					if(y1-y2>h1/2+h2/2-50 && m_player->getUpSpeed() < 34){
						auto sp = Sprite::create("black_bg.png");
						sp->setPosition(monster->getPositionX(),monster->getPositionY());
						this->addChild(sp);
						m_monsterAnim.pushBack(sp);
						deleteMonsterVec.pushBack(monster);
						monster->removeFromParent();

						Vector<SpriteFrame*> monsterDiedFrames;
						SpriteFrame* frame;

						for(int i=0;i<8;i++){
							frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("monster_die_%d.png",i+1)->_string);
							monsterDiedFrames.pushBack(frame);
						}
						auto animation = Animation::createWithSpriteFrames(monsterDiedFrames,0.02f);
						monsterDiedAction = Animate::create(animation);
						sp->runAction(monsterDiedAction);
						Player::state = Player_Run;
						m_player->smallJump();
					}else{
						auto sp = Sprite::create("black_bg.png");
						sp->setPosition(monster->getPositionX(),monster->getPositionY());
						this->addChild(sp);
						m_monsterAnim.pushBack(sp);
						deleteMonsterVec.pushBack(monster);
						monster->removeFromParent();

						Vector<SpriteFrame*> monsterDiedFrames;
						SpriteFrame* frame;

						for(int i=0;i<8;i++){
							frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("monster_die_%d.png",i+1)->_string);
							monsterDiedFrames.pushBack(frame);
						}
						auto animation = Animation::createWithSpriteFrames(monsterDiedFrames,0.02f);
						monsterDiedAction = Animate::create(animation);
						sp->runAction(monsterDiedAction);
					}
				}
			}else if(monster->getID() == 3){
				Audio::getInstance()->playSound("Music/use_prop.mp3");
				deleteMonsterVec.pushBack(monster);
				monster->removeFromParent();
				if(Player::skillState != Player_Fly && Player::skillState != Player_Active){
					Player::skillState = Player_Magic;
					m_player->magneticMove();
				}
				GAMEDATA::getInstance()->setEatMagneticPropNums(GAMEDATA::getInstance()->getEatMagneticPropNums()+1);
			}else if(monster->getID() == 4){
				Audio::getInstance()->playSound("Music/use_prop.mp3");
				deleteMonsterVec.pushBack(monster);
				monster->removeFromParent();
				if(GAMEDATA::getInstance()->isFirstEatPotentialProp()){
					GAMEDATA::getInstance()->setFirstEatPotentialProp(false);
					#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
					CallAndroidMethod::getInstance()->pay(10);
					#endif
				}else{
					Player::skillState = Player_Fly;
					m_player->quickMove();
				}
				GAMEDATA::getInstance()->setEatPotentialPropNums(GAMEDATA::getInstance()->getEatPotentialPropNums()+1);
			}else if(monster->getID() == 5){
				Audio::getInstance()->playSound("Music/use_prop.mp3");
				deleteMonsterVec.pushBack(monster);
				monster->removeFromParent();
				if(Player::skillState != Player_Fly && Player::skillState != Player_Active){
					Player::skillState = Player_Super;
					m_player->superMove();
				}
				GAMEDATA::getInstance()->setEatSuperPropNums(GAMEDATA::getInstance()->getEatSuperPropNums()+1);
			}else if(monster->getID() == 6){
				deleteMonsterVec.pushBack(monster);
				monster->removeFromParent();
			}
		}
	}
	for(auto gold : m_eatGold1){
		if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
			gold->setPositionX(gold->getPositionX()-speed2);
		}else{
			gold->setPositionX(gold->getPositionX()-speed);
		}
	}
	for(auto gold : m_eatGold2){
		if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
			gold->setPositionX(gold->getPositionX()-speed2);
		}else{
			gold->setPositionX(gold->getPositionX()-speed);
		}
	}
	if(Player::skillState == Player_Magic || Player::skillState == Player_Fly || Player::skillState == Player_Active){
		auto stairLayer1 = nowmap1->getLayer("stair");
		int startCol1 = (0-nowmap1->getPositionX())/32;
		for(int i=startCol1;i<25;i++){
			for(int j=0;j<15;j++){
				if(stairLayer1->getTileGIDAt(Vec2(i,j)) == 9){
					if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
						auto gold = Sprite::create("gold.png");
						gold->setPosition(i*32+16+nowmap1->getPositionX(),480-j*32-16);
						this->addChild(gold);
						m_eatGold1.pushBack(gold);
						stairLayer1->removeTileAt(Vec2(i,j));
						auto delay = DelayTime::create((i-startCol1)*0.02f);
						auto magneticGold = CallFunc::create([=](){
							this->magneticGold(gold,1);
						});
						auto seq = Sequence::create(delay,magneticGold,NULL);
						gold->runAction(seq);
					}else{
						auto gold = Sprite::create("gold.png");
						gold->setPosition(i*32+16+nowmap1->getPositionX(),480-j*32-16);
						this->addChild(gold);
						m_eatGold1.pushBack(gold);
						stairLayer1->removeTileAt(Vec2(i,j));
						auto delay = DelayTime::create((i-startCol1)*0.04f);
						auto magneticGold = CallFunc::create([=](){
							this->magneticGold(gold,1);
						});
						auto seq = Sequence::create(delay,magneticGold,NULL);
						gold->runAction(seq);
					}
				}
			}
		}
		int startCol2 = (800-nowmap2->getPositionX())/32;
		auto stairLayer2 = nowmap2->getLayer("stair");
		if(startCol2 > 12){
			if(startCol2 < 21){				
				for(int i=0;i<startCol1-4;i++){
					for(int j=0;j<15;j++){
						if(stairLayer2->getTileGIDAt(Vec2(i,j)) == 9){
							if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
								auto gold = Sprite::create("gold.png");
								gold->setPosition(i*32+16+nowmap2->getPositionX(),480-j*32-16);
								this->addChild(gold);
								m_eatGold2.pushBack(gold);
								stairLayer2->removeTileAt(Vec2(i,j));						
								auto delay = DelayTime::create((25-startCol1+i)*0.02f);
								auto magneticGold = CallFunc::create([=](){
									this->magneticGold(gold,2);
								});
								auto seq = Sequence::create(delay,magneticGold,NULL);
								gold->runAction(seq);
							}else{
								auto gold = Sprite::create("gold.png");
								gold->setPosition(i*32+16+nowmap2->getPositionX(),480-j*32-16);
								this->addChild(gold);
								m_eatGold2.pushBack(gold);
								stairLayer2->removeTileAt(Vec2(i,j));						
								auto delay = DelayTime::create((25-startCol1+i)*0.04f);
								auto magneticGold = CallFunc::create([=](){
									this->magneticGold(gold,2);
								});
								auto seq = Sequence::create(delay,magneticGold,NULL);
								gold->runAction(seq);
							}
						}
					}
				}
			}else{
				for(int i=0;i<startCol1;i++){
					for(int j=0;j<15;j++){
						if(stairLayer2->getTileGIDAt(Vec2(i,j)) == 9){
							if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
								auto gold = Sprite::create("gold.png");
								gold->setPosition(i*32+16+nowmap2->getPositionX(),480-j*32-16);
								this->addChild(gold);
								m_eatGold2.pushBack(gold);
								stairLayer2->removeTileAt(Vec2(i,j));						
								auto delay = DelayTime::create((25-startCol1+i)*0.02f);
								auto magneticGold = CallFunc::create([=](){
									this->magneticGold(gold,2);
								});
								auto seq = Sequence::create(delay,magneticGold,NULL);
								gold->runAction(seq);
							}else{
								auto gold = Sprite::create("gold.png");
								gold->setPosition(i*32+16+nowmap2->getPositionX(),480-j*32-16);
								this->addChild(gold);
								m_eatGold2.pushBack(gold);
								stairLayer2->removeTileAt(Vec2(i,j));						
								auto delay = DelayTime::create((25-startCol1+i)*0.04f);
								auto magneticGold = CallFunc::create([=](){
									this->magneticGold(gold,2);
								});
								auto seq = Sequence::create(delay,magneticGold,NULL);
								gold->runAction(seq);
							}
						}
					}
				}
			}
		}
	}
	if(Player::state == Player_Slide){
		auto stairLayer = nowmap1->getLayer("stair");
		int upSpeed = m_player->getUpSpeed();
		if(Player::jumpFromGround){
			Player::jumpFromGround = false;
			m_player->setPositionY(m_player->getPositionY()+((float)upSpeed)/3.0f+16);
		}else{
			if(upSpeed <= 0){
				m_player->setPositionY(m_player->getPositionY()+((float)upSpeed)/2.0f);
			}else{
				m_player->setPositionY(m_player->getPositionY()+((float)upSpeed)/3.0f);
			}
		}
		float px = m_player->getPositionX()-nowmap1->getPositionX();
		float py = m_player->getPositionY();
		int col = (int)px/32;
		int row = 14-(int)py/32;
		if(row > 13 && Player::skillState != Player_Fly && Player::skillState != Player_Active){
			GameStateInfo::getInstance()->setGameState(Game_End);
			return true;
		}
		if(col == 24){
			auto stairLayer2 = nowmap2->getLayer("stair");
			int topLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row-2));
			int topMiddleGid = stairLayer->getTileGIDAt(Vec2(col,row-2));
			int topRightGid = stairLayer2->getTileGIDAt(Vec2(col-24,row-2));
			int bottomLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row));
			int bottomMiddleGid = stairLayer->getTileGIDAt(Vec2(col,row));
			int ceilGid1 = stairLayer->getTileGIDAt(Vec2(col,row-3));
			int ceilGid2 = stairLayer2->getTileGIDAt(Vec2(0,row-3));
			int ceilGid3 = stairLayer2->getTileGIDAt(Vec2(1,row-3));
			int frontBottomGid = stairLayer2->getTileGIDAt(Vec2(col-24,row-1));
			if(topRightGid == 9 || frontBottomGid == 9){
				m_infoLayer->goldAddOne();
				goldAnim();
				int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
				int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
				if(Player::skillState != Player_Active){
					GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
					if(potentialGoldNum == potentialIndex*300){
						GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
						GAMEDATA::getInstance()->setActiveGoldNum(0);
						Player::skillState = Player_Active;
						m_player->quickMove();
					}
				}
				m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
				if(topRightGid == 9){
					stairLayer2->removeTileAt(Vec2(col-24,row-2));
				}else if(frontBottomGid == 9){
					stairLayer2->removeTileAt(Vec2(col-24,row-1));
				}
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}else if(topRightGid > 0 || frontBottomGid > 0){
				m_player->setPositionX(m_player->getPositionX()-speed);
			}else{
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}
			if((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid)){
				int upSpeed = m_player->getUpSpeed();
				m_player->setUpSpeed(upSpeed-speed_y);
			}else{
				m_player->setUpSpeed(0);
				playerRowNum = row;
				if(row == 7){
					m_player->setPositionY(230.4+64-45);
				}else if(row == 6){
					m_player->setPositionY(230.4+64+32-45);
				}else if(row == 5){
					m_player->setPositionY(230.4+64+64-45);
				}else if(row == 8){
					m_player->setPositionY(230.4+64-32-45);
				}else if(row == 9){
					m_player->setPositionY(230.4+64-64-45);
				}else if(row == 10){
					m_player->setPositionY(230.4+64-96-45);
				}
				int gid1 = 0;
				int gid2 = 0;
				for(int k = row-1;k>4;k--){
					gid1 = stairLayer->getTileGIDAt(Vec2(col-1,k));
					gid2 = stairLayer->getTileGIDAt(Vec2(col,k));
					if((gid1>0 && gid1!=9) || (gid2>0 && gid2!=9)){
						playerRowNum --;
						m_player->setPositionY(m_player->getPositionY()+32);
					}else{
						break;
					}
				}
			}			
			if((ceilGid1 != 9 && ceilGid1 != 0) || (ceilGid2 != 9 && ceilGid2 != 0)){
				needContiSlide = true;
				canJump = false;
			}else{
				if(ceilGid3 != 9 && ceilGid3 != 0){
					needContiSlide = true;
				}else{
					needContiSlide = false;
					if(!TollgateScene::isSliding){
						m_player->move();
					}
				}
				if((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid)){
					canJump = false;
					canSlide = false;
				}else{
					canJump = true;
					canSlide = true;
				}
			}
		}else if(col == 25){
			auto stairLayer2 = nowmap2->getLayer("stair");
			int topLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row-2));
			int topMiddleGid = stairLayer2->getTileGIDAt(Vec2(col-25,row-2));
			int topRightGid = stairLayer2->getTileGIDAt(Vec2(col-24,row-2));
			int bottomLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row));
			int bottomMiddleGid = stairLayer2->getTileGIDAt(Vec2(col-25,row));
			int frontBottomGid = stairLayer2->getTileGIDAt(Vec2(col-24,row-1));
			int ceilGid1 = stairLayer2->getTileGIDAt(Vec2(0,row-3));
			int ceilGid2 = stairLayer2->getTileGIDAt(Vec2(1,row-3));
			int ceilGid3 = stairLayer2->getTileGIDAt(Vec2(2,row-3));
			if(topRightGid == 9 || frontBottomGid == 9){
				m_infoLayer->goldAddOne();
				goldAnim();
				int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
				int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
				if(Player::skillState != Player_Active){
					GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
					if(potentialGoldNum == potentialIndex*300){
						GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
						GAMEDATA::getInstance()->setActiveGoldNum(0);
						Player::skillState = Player_Active;
						m_player->quickMove();
					}
				}
				m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
				if(topRightGid == 9){
					stairLayer2->removeTileAt(Vec2(col-24,row-2));
				}else if(frontBottomGid == 9){
					stairLayer2->removeTileAt(Vec2(col-24,row-1));
				}
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}else if(topRightGid > 0 || frontBottomGid > 0){
				m_player->setPositionX(m_player->getPositionX()-speed);
			}else{
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}
			if((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid)){
				int upSpeed = m_player->getUpSpeed();
				m_player->setUpSpeed(upSpeed-speed_y);
			}else{
				m_player->setUpSpeed(0);
				playerRowNum = row;
				if(row == 7){
					m_player->setPositionY(230.4+64-45);
				}else if(row == 6){
					m_player->setPositionY(230.4+64+32-45);
				}else if(row == 5){
					m_player->setPositionY(230.4+64+64-45);
				}else if(row == 8){
					m_player->setPositionY(230.4+64-32-45);
				}else if(row == 9){
					m_player->setPositionY(230.4+64-64-45);
				}else if(row == 10){
					m_player->setPositionY(230.4+64-96-45);
				}
				int gid1 = 0;
				int gid2 = 0;
				for(int k = row-1;k>4;k--){
					gid1 = stairLayer->getTileGIDAt(Vec2(col-1,k));
					gid2 = stairLayer2->getTileGIDAt(Vec2(col-25,k));
					if((gid1>0 && gid1!=9) || (gid2>0 && gid2!=9)){
						playerRowNum --;
						m_player->setPositionY(m_player->getPositionY()+32);
					}else{
						break;
					}
				}
			}
			if((ceilGid1 != 9 && ceilGid1 != 0) || (ceilGid2 != 9 && ceilGid2 != 0)){
				needContiSlide = true;
				canJump = false;
			}else{
				if(ceilGid3 != 9 && ceilGid3 != 0){
					needContiSlide = true;
				}else{
					needContiSlide = false;
					if(!TollgateScene::isSliding){
						m_player->move();
					}
				}
				if((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid)){
					canJump = false;
					canSlide = false;
				}else{
					canJump = true;
					canSlide = true;
				}
			}
		}else if(col > 25){
			col = col - 25;
			auto stairLayer2 = nowmap2->getLayer("stair");
			int topLeftGid = stairLayer2->getTileGIDAt(Vec2(col-1,row-2));
			int topMiddleGid = stairLayer2->getTileGIDAt(Vec2(col,row-2));
			int topRightGid = stairLayer2->getTileGIDAt(Vec2(col+1,row-2));
			int bottomLeftGid = stairLayer2->getTileGIDAt(Vec2(col-1,row));
			int bottomMiddleGid = stairLayer2->getTileGIDAt(Vec2(col,row));
			int frontBottomGid = stairLayer2->getTileGIDAt(Vec2(col+1,row-1));
			int ceilGid1 = stairLayer2->getTileGIDAt(Vec2(col,row-3));
			int ceilGid2 = stairLayer2->getTileGIDAt(Vec2(col+1,row-3));
			int ceilGid3 = stairLayer2->getTileGIDAt(Vec2(col+2,row-3));
			if(topRightGid == 9 || frontBottomGid == 9){
				m_infoLayer->goldAddOne();
				goldAnim();
				int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
				int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
				if(Player::skillState != Player_Active){
					GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
					if(potentialGoldNum == potentialIndex*300){
						GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
						GAMEDATA::getInstance()->setActiveGoldNum(0);
						Player::skillState = Player_Active;
						m_player->quickMove();
					}
				}
				m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
				if(topRightGid == 9){
					stairLayer2->removeTileAt(Vec2(col+1,row-2));
				}else if(frontBottomGid == 9){
					stairLayer2->removeTileAt(Vec2(col+1,row-1));
				}
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}else if(topRightGid > 0 || frontBottomGid > 0){
				m_player->setPositionX(m_player->getPositionX()-speed);
			}else{
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}
			if((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid)){
				int upSpeed = m_player->getUpSpeed();
				m_player->setUpSpeed(upSpeed-speed_y);
			}else{
				m_player->setUpSpeed(0);
				playerRowNum = row;
				if(row == 7){
					m_player->setPositionY(230.4+64-45);
				}else if(row == 6){
					m_player->setPositionY(230.4+64+32-45);
				}else if(row == 5){
					m_player->setPositionY(230.4+64+64-45);
				}else if(row == 8){
					m_player->setPositionY(230.4+64-32-45);
				}else if(row == 9){
					m_player->setPositionY(230.4+64-64-45);
				}else if(row == 10){
					m_player->setPositionY(230.4+64-96-45);
				}
				int gid1 = 0;
				int gid2 = 0;
				for(int k = row-1;k>4;k--){
					gid1 = stairLayer2->getTileGIDAt(Vec2(col-1,k));
					gid2 = stairLayer2->getTileGIDAt(Vec2(col,k));
					if((gid1>0 && gid1!=9) || (gid2>0 && gid2!=9)){
						playerRowNum --;
						m_player->setPositionY(m_player->getPositionY()+32);
					}else{
						break;
					}
				}
			}
			if((ceilGid1 != 9 && ceilGid1 != 0) || (ceilGid2 != 9 && ceilGid2 != 0)){
				needContiSlide = true;
				canJump = false;
			}else{
				if(ceilGid3 != 9 && ceilGid3 != 0){
					needContiSlide = true;
				}else{
					needContiSlide = false;
					if(!TollgateScene::isSliding){
						m_player->move();
					}
				}
				if((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid)){
					canJump = false;
					canSlide = false;
				}else{
					canJump = true;
					canSlide = true;
				}
			}
		}else{
			int topLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row-2));
			int topMiddleGid = stairLayer->getTileGIDAt(Vec2(col,row-2));
			int topRightGid = stairLayer->getTileGIDAt(Vec2(col+1,row-2));
			int bottomLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row));
			int bottomMiddleGid = stairLayer->getTileGIDAt(Vec2(col,row));
			int ceilGid1 = stairLayer->getTileGIDAt(Vec2(col,row-3));
			int ceilGid2 = stairLayer->getTileGIDAt(Vec2(col+1,row-3));
			int ceilGid3 = 0;
			if(col == 23){
				auto stairLayer2 = nowmap2->getLayer("stair");
				ceilGid3 = stairLayer2->getTileGIDAt(Vec2(0,row-3));
			}else{
				ceilGid3 = stairLayer->getTileGIDAt(Vec2(col+2,row-3));
			}
			int frontBottomGid = stairLayer->getTileGIDAt(Vec2(col+1,row-1));
			if(topRightGid == 9 || frontBottomGid == 9){
				m_infoLayer->goldAddOne();
				goldAnim();
				int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
				int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
				if(Player::skillState != Player_Active){
					GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
					if(potentialGoldNum == potentialIndex*300){
						GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
						GAMEDATA::getInstance()->setActiveGoldNum(0);
						Player::skillState = Player_Active;
						m_player->quickMove();
					}
				}
				m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
				if(topRightGid == 9){
					stairLayer->removeTileAt(Vec2(col+1,row-2));
				}else if(frontBottomGid == 9){
					stairLayer->removeTileAt(Vec2(col+1,row-1));
				}
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}else if(topRightGid > 0 || frontBottomGid > 0){
				m_player->setPositionX(m_player->getPositionX()-speed);
			}else{
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}
			if((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid)){
				int upSpeed = m_player->getUpSpeed();
				m_player->setUpSpeed(upSpeed-speed_y);
			}else{
				m_player->setUpSpeed(0);
				playerRowNum = row;
				if(row == 7){
					m_player->setPositionY(230.4+64-45);
				}else if(row == 6){
					m_player->setPositionY(230.4+64+32-45);
				}else if(row == 5){
					m_player->setPositionY(230.4+64+64-45);
				}else if(row == 8){
					m_player->setPositionY(230.4+64-32-45);
				}else if(row == 9){
					m_player->setPositionY(230.4+64-64-45);
				}else if(row == 10){
					m_player->setPositionY(230.4+64-96-45);
				}
				int gid1 = 0;
				int gid2 = 0;
				for(int k = row-1;k>4;k--){
					gid1 = stairLayer->getTileGIDAt(Vec2(col-1,k));
					gid2 = stairLayer->getTileGIDAt(Vec2(col,k));
					if((gid1>0 && gid1!=9) || (gid2>0 && gid2!=9)){
						playerRowNum --;
						m_player->setPositionY(m_player->getPositionY()+32);
					}else{
						break;
					}
				}
			}
			if((ceilGid1 != 9 && ceilGid1 != 0) || (ceilGid2 != 9 && ceilGid2 != 0)){
				needContiSlide = true;
				canJump = false;
			}else{
				if(ceilGid3 != 9 && ceilGid3 != 0){
					needContiSlide = true;
				}else{
					needContiSlide = false;
					if(!TollgateScene::isSliding){
						m_player->move();
					}
				}
				if((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid)){
					canJump = false;
					canSlide = false;
				}else{
					canJump = true;
					canSlide = true;
				}
			}
		}
	}else{	
		bool beStop = false;
		auto stairLayer = nowmap1->getLayer("stair");
		int upSpeed = m_player->getUpSpeed();
		if(Player::jumpFromGround){
			Player::jumpFromGround = false;
			m_player->setPositionY(m_player->getPositionY()+((float)upSpeed)/3.0f+16);
		}else{
			if(upSpeed <= 0){
				m_player->setPositionY(m_player->getPositionY()+((float)upSpeed)/2.0f);
			}else{
				m_player->setPositionY(m_player->getPositionY()+((float)upSpeed)/3.0f);
			}
		}
		float px = m_player->getPositionX()-nowmap1->getPositionX();
		float py = m_player->getPositionY();
		int col = (int)px/32;
		int row = 14-(int)py/32;
		if(row < 2){
			int upSpeed = m_player->getUpSpeed();
			if(Player::skillState != Player_Fly && Player::skillState != Player_Active){
				m_player->setUpSpeed(upSpeed-speed_y);
			}
			if(col == 24){
				auto stairLayer2 = nowmap2->getLayer("stair");
				if(row == 1){
					int topLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row-1));
					int topMiddleGid = stairLayer->getTileGIDAt(Vec2(col,row-1));
					int topRightGid = stairLayer2->getTileGIDAt(Vec2(col-24,row-1));
					if(topLeftGid == 9 || topMiddleGid == 9 || topRightGid == 9){
						m_infoLayer->goldAddOne();
						goldAnim();
						int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
						int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
						if(Player::skillState != Player_Active){
							GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
							if(potentialGoldNum == potentialIndex*300){
								GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
								GAMEDATA::getInstance()->setActiveGoldNum(0);
								Player::skillState = Player_Active;
								m_player->quickMove();
							}
						}
						m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
						if(topLeftGid == 9){
							stairLayer->removeTileAt(Vec2(col-1,row-1));
						}else if(topMiddleGid == 9){
							stairLayer->removeTileAt(Vec2(col,row-1));
						}else if(topRightGid == 9){
							stairLayer2->removeTileAt(Vec2(col-24,row-1));
						}
					}
				}else if(row == 0){
					int frontMiddleGid = stairLayer2->getTileGIDAt(Vec2(col-24,row));
					int centerLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row));
					int centerMiddlerGid = stairLayer->getTileGIDAt(Vec2(col,row));
					if(frontMiddleGid == 9 || centerLeftGid == 9 || centerMiddlerGid == 9){
						m_infoLayer->goldAddOne();
						goldAnim();
						int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
						int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
						if(Player::skillState != Player_Active){
							GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
							if(potentialGoldNum == potentialIndex*300){
								GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
								GAMEDATA::getInstance()->setActiveGoldNum(0);
								Player::skillState = Player_Active;
								m_player->quickMove();
							}
						}
						m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
						if(frontMiddleGid == 9){
							stairLayer2->removeTileAt(Vec2(col-24,row));
						}else if(centerLeftGid == 9){
							stairLayer->removeTileAt(Vec2(col-1,row));
						}else if(centerMiddlerGid == 9){
							stairLayer->removeTileAt(Vec2(col,row));
						}
					}
				}
				int frontBottomGid = stairLayer2->getTileGIDAt(Vec2(col-24,row+1));
				if(frontBottomGid > 0 && frontBottomGid != 9){
					m_player->setPositionX(m_player->getPositionX()-speed);
				}
			}else if(col == 25){
				auto stairLayer2 = nowmap2->getLayer("stair");
				if(row == 1){
					int topLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row-1));
					int topMiddleGid = stairLayer2->getTileGIDAt(Vec2(col-25,row-1));
					int topRightGid = stairLayer2->getTileGIDAt(Vec2(col-24,row-1));
					if(topLeftGid == 9 || topMiddleGid == 9 || topRightGid == 9){
						m_infoLayer->goldAddOne();
						goldAnim();
						int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
						int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
						if(Player::skillState != Player_Active){
							GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
							if(potentialGoldNum == potentialIndex*300){
								GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
								GAMEDATA::getInstance()->setActiveGoldNum(0);
								Player::skillState = Player_Active;
								m_player->quickMove();
							}
						}
						m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
						if(topLeftGid == 9){
							stairLayer->removeTileAt(Vec2(col-1,row-1));
						}else if(topMiddleGid == 9){
							stairLayer2->removeTileAt(Vec2(col-25,row-1));
						}else if(topRightGid == 9){
							stairLayer2->removeTileAt(Vec2(col-24,row-1));
						}
					}
				}else if(row == 0){;
					int frontMiddleGid = stairLayer2->getTileGIDAt(Vec2(col-24,row));
					int centerLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row));
					int centerMiddlerGid = stairLayer2->getTileGIDAt(Vec2(col-25,row));
					if(frontMiddleGid == 9 || centerLeftGid == 9 || centerMiddlerGid == 9){
						m_infoLayer->goldAddOne();
						goldAnim();
						int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
						int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
						if(Player::skillState != Player_Active){
							GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
							if(potentialGoldNum == potentialIndex*300){
								GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
								GAMEDATA::getInstance()->setActiveGoldNum(0);
								Player::skillState = Player_Active;
								m_player->quickMove();
							}
						}
						m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
						if(frontMiddleGid == 9){
							stairLayer2->removeTileAt(Vec2(col-24,row));
						}else if(centerLeftGid == 9){
							stairLayer->removeTileAt(Vec2(col-1,row));
						}else if(centerMiddlerGid == 9){
							stairLayer2->removeTileAt(Vec2(col-25,row));
						}
					}
				}
				int frontBottomGid = stairLayer2->getTileGIDAt(Vec2(col-24,row+1));
				if(frontBottomGid > 0 && frontBottomGid != 9){
					m_player->setPositionX(m_player->getPositionX()-speed);
				}
			}else if(col > 25){
				auto stairLayer2 = nowmap2->getLayer("stair");
				if(row == 1){
					int topLeftGid = stairLayer2->getTileGIDAt(Vec2(col-1,row-1));
					int topMiddleGid = stairLayer2->getTileGIDAt(Vec2(col,row-1));
					int topRightGid = stairLayer2->getTileGIDAt(Vec2(col+1,row-1));
					if(topLeftGid == 9 || topMiddleGid == 9 || topRightGid == 9){
						m_infoLayer->goldAddOne();
						goldAnim();
						int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
						int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
						if(Player::skillState != Player_Active){
							GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
							if(potentialGoldNum == potentialIndex*300){
								GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
								GAMEDATA::getInstance()->setActiveGoldNum(0);
								Player::skillState = Player_Active;
								m_player->quickMove();
							}
						}
						m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
						if(topLeftGid == 9){
							stairLayer2->removeTileAt(Vec2(col-1,row-1));
						}else if(topMiddleGid == 9){
							stairLayer2->removeTileAt(Vec2(col,row-1));
						}else if(topRightGid == 9){
							stairLayer2->removeTileAt(Vec2(col+1,row-1));
						}
					}
				}else if(row == 0){
					int frontMiddleGid = stairLayer2->getTileGIDAt(Vec2(col+1,row));
					int centerLeftGid = stairLayer2->getTileGIDAt(Vec2(col-1,row));
					int centerMiddlerGid = stairLayer2->getTileGIDAt(Vec2(col,row));
					if(frontMiddleGid == 9 || centerLeftGid == 9 || centerMiddlerGid == 9){
						m_infoLayer->goldAddOne();
						goldAnim();
						int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
						int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
						if(Player::skillState != Player_Active){
							GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
							if(potentialGoldNum == potentialIndex*300){
								GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
								GAMEDATA::getInstance()->setActiveGoldNum(0);
								Player::skillState = Player_Active;
								m_player->quickMove();
							}
						}
						m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
						if(frontMiddleGid == 9){
							stairLayer2->removeTileAt(Vec2(col+1,row));
						}else if(centerLeftGid == 9){
							stairLayer2->removeTileAt(Vec2(col-1,row));
						}else if(centerMiddlerGid == 9){
							stairLayer2->removeTileAt(Vec2(col,row));
						}
					}
				}
				int frontBottomGid = stairLayer2->getTileGIDAt(Vec2(col+1,row+1));
				if(frontBottomGid > 0 && frontBottomGid != 9){
					m_player->setPositionX(m_player->getPositionX()-speed);
				}
			}else{
				if(row == 1){
					int topLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row-1));
					int topMiddleGid = stairLayer->getTileGIDAt(Vec2(col,row-1));
					int topRightGid = stairLayer->getTileGIDAt(Vec2(col+1,row-1));
					if(topLeftGid == 9 || topMiddleGid == 9 || topRightGid == 9){
						m_infoLayer->goldAddOne();
						goldAnim();
						int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
						int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
						if(Player::skillState != Player_Active){
							GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
							if(potentialGoldNum == potentialIndex*300){
								GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
								GAMEDATA::getInstance()->setActiveGoldNum(0);
								Player::skillState = Player_Active;
								m_player->quickMove();
							}
						}
						m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
						if(topLeftGid == 9){
							stairLayer->removeTileAt(Vec2(col-1,row-1));
						}else if(topMiddleGid == 9){
							stairLayer->removeTileAt(Vec2(col,row-1));
						}else if(topRightGid == 9){
							stairLayer->removeTileAt(Vec2(col+1,row-1));
						}
					}
				}else if(row == 0){
					int frontMiddleGid = stairLayer->getTileGIDAt(Vec2(col+1,row));
					int centerLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row));
					int centerMiddlerGid = stairLayer->getTileGIDAt(Vec2(col,row));
					if(frontMiddleGid == 9 || centerLeftGid == 9 || centerMiddlerGid == 9){
						m_infoLayer->goldAddOne();
						goldAnim();
						int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
						int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
						if(Player::skillState != Player_Active){
							GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
							if(potentialGoldNum == potentialIndex*300){
								GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
								GAMEDATA::getInstance()->setActiveGoldNum(0);
								Player::skillState = Player_Active;
								m_player->quickMove();
							}
						}
						m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
						if(frontMiddleGid == 9){
							stairLayer->removeTileAt(Vec2(col+1,row));
						}else if(centerLeftGid == 9){
							stairLayer->removeTileAt(Vec2(col-1,row));
						}else if(centerMiddlerGid == 9){
							stairLayer->removeTileAt(Vec2(col,row));
						}
					}
				}
				int frontBottomGid = stairLayer->getTileGIDAt(Vec2(col+1,row+1));
				if(frontBottomGid > 0 && frontBottomGid != 9){
					m_player->setPositionX(m_player->getPositionX()-speed);
				}
			}
			return false;
		}
		if(row > 12 && Player::skillState != Player_Fly && Player::skillState != Player_Active){
			GameStateInfo::getInstance()->setGameState(Game_End);
			return true;
		}
		if(col == 24){
			auto stairLayer2 = nowmap2->getLayer("stair");
			int topLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row-1));
			int topMiddleGid = stairLayer->getTileGIDAt(Vec2(col,row-1));
			int topRightGid = stairLayer2->getTileGIDAt(Vec2(col-24,row-1));
			int bottomLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row+2));
			int bottomMiddleGid = stairLayer->getTileGIDAt(Vec2(col,row+2));
			int frontMiddleGid = stairLayer2->getTileGIDAt(Vec2(col-24,row));
			int frontBottomGid = stairLayer2->getTileGIDAt(Vec2(col-24,row+1));
			int centerLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row));
			int centerMiddlerGid = stairLayer->getTileGIDAt(Vec2(col,row));
			int ceilGid1 = stairLayer->getTileGIDAt(Vec2(24,row-2));
			int ceilGid2 = stairLayer2->getTileGIDAt(Vec2(1,row-2));
			if(centerLeftGid == 9 || centerMiddlerGid == 9 || topLeftGid == 9 || topMiddleGid == 9){
				m_infoLayer->goldAddOne();
				goldAnim();
				int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
				int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
				if(Player::skillState != Player_Active){
					GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
					if(potentialGoldNum == potentialIndex*300){
						GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
						GAMEDATA::getInstance()->setActiveGoldNum(0);
						Player::skillState = Player_Active;
						m_player->quickMove();
					}
				}
				m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
				if(centerLeftGid == 9){
					stairLayer->removeTileAt(Vec2(col-1,row));
				}else if(centerMiddlerGid == 9){
					stairLayer->removeTileAt(Vec2(col,row));
				}else if(topLeftGid == 9){
					stairLayer->removeTileAt(Vec2(col-1,row-1));
				}else if(topMiddleGid == 9){
					stairLayer2->removeTileAt(Vec2(col,row-1));
				}
			}
			if(topRightGid == 9 || frontBottomGid == 9 || frontMiddleGid == 9){
				m_infoLayer->goldAddOne();
				goldAnim();
				int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
				int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
				if(Player::skillState != Player_Active){
					GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
					if(potentialGoldNum == potentialIndex*300){
						GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
						GAMEDATA::getInstance()->setActiveGoldNum(0);
						Player::skillState = Player_Active;
						m_player->quickMove();
					}
				}
				m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
				if(topRightGid == 9){
					stairLayer2->removeTileAt(Vec2(col-24,row-1));
				}else if(frontBottomGid == 9){
					stairLayer2->removeTileAt(Vec2(col-24,row+1));
				}else if(frontMiddleGid == 9){
					stairLayer2->removeTileAt(Vec2(col-24,row));
				}
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}else if(topRightGid > 0 || frontBottomGid > 0 || frontMiddleGid > 0){
				if(Player::skillState == Player_Normal || Player::skillState == Player_Magic){
					m_player->setPositionX(m_player->getPositionX()-speed);
					beStop = true;
				}else if(Player::skillState == Player_Transition_Fly || Player::skillState == Player_Transition_Super || Player::skillState == Player_Super){
					if(frontBottomGid > 0){
						m_player->setPositionX(m_player->getPositionX()-speed);
					}
				}
			}else{
				beStop = false;
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}
			if(((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid))){
				int upSpeed = m_player->getUpSpeed();
				if(Player::skillState != Player_Fly && Player::skillState != Player_Active){
					m_player->setUpSpeed(upSpeed-speed_y);
				}
			}else{
				playerRowNum = row;
				m_player->setUpSpeed(0);
				if(Player::skillState != Player_Fly && Player::skillState != Player_Active){
					if(row == 7){
						m_player->setPositionY(230.4);
					}else if(row == 6){
						m_player->setPositionY(230.4+32);
					}else if(row == 5){
						m_player->setPositionY(230.4+64);
					}else if(row == 8){
						m_player->setPositionY(230.4-32);
					}else if(row == 9){
						m_player->setPositionY(230.4-64);
					}else if(row == 10){
						m_player->setPositionY(230.4-96);
					}
					if(Player::state != Player_Run){
						Audio::getInstance()->playSound("Music/jump.mp3");
						m_player->move();
					}
					int gid1 = 0;
					int gid2 = 0;
					for(int k = row+1;k>4;k--){
						gid1 = stairLayer->getTileGIDAt(Vec2(col-1,k));
						gid2 = stairLayer->getTileGIDAt(Vec2(col,k));
						if((gid1>0 && gid1!=9) || (gid2>0 && gid2!=9)){
							playerRowNum --;
							m_player->setPositionY(m_player->getPositionY()+32);
						}else{
							break;
						}
					}
				}
			}			
			if((ceilGid1 != 9 && ceilGid1 != 0) || (ceilGid2 != 9 && ceilGid2 != 0)){
				canJump = false;
			}else{
				if((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid)){
					canJump = false;
					canSlide = false;
				}else{
					canJump = true;
					canSlide = true;
				}
			}
		}else if(col == 25){
			auto stairLayer2 = nowmap2->getLayer("stair");
			int topLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row-1));
			int topMiddleGid = stairLayer2->getTileGIDAt(Vec2(col-25,row-1));
			int topRightGid = stairLayer2->getTileGIDAt(Vec2(col-24,row-1));
			int bottomLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row+2));
			int bottomMiddleGid = stairLayer2->getTileGIDAt(Vec2(col-25,row+2));
			int frontMiddleGid = stairLayer2->getTileGIDAt(Vec2(col-24,row));
			int frontBottomGid = stairLayer2->getTileGIDAt(Vec2(col-24,row+1));
			int centerLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row));
			int centerMiddlerGid = stairLayer2->getTileGIDAt(Vec2(col-25,row));
			int ceilGid1 = stairLayer2->getTileGIDAt(Vec2(col-25,row-2));
			int ceilGid2 = stairLayer2->getTileGIDAt(Vec2(col-24,row-2));
			if(centerLeftGid == 9 || centerMiddlerGid == 9 || topLeftGid == 9 || topMiddleGid == 9){
				m_infoLayer->goldAddOne();
				goldAnim();
				int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
				int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
				if(Player::skillState != Player_Active){
					GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
					if(potentialGoldNum == potentialIndex*300){
						GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
						GAMEDATA::getInstance()->setActiveGoldNum(0);
						Player::skillState = Player_Active;
						m_player->quickMove();
					}
				}
				m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
				if(centerLeftGid == 9){
					stairLayer->removeTileAt(Vec2(col-1,row));
				}else if(centerMiddlerGid == 9){
					stairLayer2->removeTileAt(Vec2(col-25,row));
				}else if(topLeftGid == 9){
					stairLayer->removeTileAt(Vec2(col-1,row-1));
				}else if(topMiddleGid == 9){
					stairLayer2->removeTileAt(Vec2(col-25,row-1));
				}
			}
			if(topRightGid == 9 || frontBottomGid == 9 || frontMiddleGid == 9){
				m_infoLayer->goldAddOne();
				goldAnim();
				int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
				int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
				if(Player::skillState != Player_Active){
					GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
					if(potentialGoldNum == potentialIndex*300){
						GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
						GAMEDATA::getInstance()->setActiveGoldNum(0);
						Player::skillState = Player_Active;
						m_player->quickMove();
					}
				}
				m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
				if(topRightGid == 9){
					stairLayer2->removeTileAt(Vec2(col-24,row-1));
				}else if(frontBottomGid == 9){
					stairLayer2->removeTileAt(Vec2(col-24,row+1));
				}else if(frontMiddleGid == 9){
					stairLayer2->removeTileAt(Vec2(col-24,row));
				}
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}else if(topRightGid > 0 || frontBottomGid > 0 || frontMiddleGid > 0){
				if(Player::skillState == Player_Normal || Player::skillState == Player_Magic){
					m_player->setPositionX(m_player->getPositionX()-speed);
					beStop = true;
				}else if(Player::skillState == Player_Transition_Fly || Player::skillState == Player_Transition_Super || Player::skillState == Player_Super){
					if(frontBottomGid > 0){
						m_player->setPositionX(m_player->getPositionX()-speed);
					}
				}
			}else{
				beStop = false;
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}
			if(((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid))){
				int upSpeed = m_player->getUpSpeed();
				if(Player::skillState != Player_Fly && Player::skillState != Player_Active){
					m_player->setUpSpeed(upSpeed-speed_y);
				}
			}else{
				playerRowNum = row;
				m_player->setUpSpeed(0);
				if(Player::skillState != Player_Fly && Player::skillState != Player_Active){
					if(row == 7){
						m_player->setPositionY(230.4);
					}else if(row == 6){
						m_player->setPositionY(230.4+32);
					}else if(row == 5){
						m_player->setPositionY(230.4+64);
					}else if(row == 8){
						m_player->setPositionY(230.4-32);
					}else if(row == 9){
						m_player->setPositionY(230.4-64);
					}else if(row == 10){
						m_player->setPositionY(230.4-96);
					}
					if(Player::state != Player_Run){
						Audio::getInstance()->playSound("Music/jump.mp3");
						m_player->move();
					}
					int gid1 = 0;
					int gid2 = 0;
					for(int k = row+1;k>4;k--){
						gid1 = stairLayer->getTileGIDAt(Vec2(col-1,k));
						gid2 = stairLayer2->getTileGIDAt(Vec2(col-25,k));
						if((gid1>0 && gid1!=9) || (gid2>0 && gid2!=9)){
							playerRowNum --;
							m_player->setPositionY(m_player->getPositionY()+32);
						}else{
							break;
						}
					}
				}
			}
			if((ceilGid1 != 9 && ceilGid1 != 0) || (ceilGid2 != 9 && ceilGid2 != 0)){
				canJump = false;
			}else{
				if((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid)){
					canJump = false;
					canSlide = false;
				}else{
					canJump = true;
					canSlide = true;
				}
			}
		}else if(col > 25){
			col = col - 25;
			auto stairLayer2 = nowmap2->getLayer("stair");
			int topLeftGid = stairLayer2->getTileGIDAt(Vec2(col-1,row-1));
			int topMiddleGid = stairLayer2->getTileGIDAt(Vec2(col,row-1));
			int topRightGid = stairLayer2->getTileGIDAt(Vec2(col+1,row-1));
			int bottomLeftGid = stairLayer2->getTileGIDAt(Vec2(col-1,row+2));
			int bottomMiddleGid = stairLayer2->getTileGIDAt(Vec2(col,row+2));
			int frontMiddleGid = stairLayer2->getTileGIDAt(Vec2(col+1,row));
			int frontBottomGid = stairLayer2->getTileGIDAt(Vec2(col+1,row+1));
			int centerLeftGid = stairLayer2->getTileGIDAt(Vec2(col-1,row));
			int centerMiddlerGid = stairLayer2->getTileGIDAt(Vec2(col,row));
			int ceilGid1 = stairLayer2->getTileGIDAt(Vec2(col,row-2));
			int ceilGid2 = stairLayer2->getTileGIDAt(Vec2(col+1,row-2));
			if(centerLeftGid == 9 || centerMiddlerGid == 9 || topLeftGid == 9 || topMiddleGid == 9){
				m_infoLayer->goldAddOne();
				goldAnim();
				int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
				int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
				if(Player::skillState != Player_Active){
					GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
					if(potentialGoldNum == potentialIndex*300){
						GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
						GAMEDATA::getInstance()->setActiveGoldNum(0);
						Player::skillState = Player_Active;
						m_player->quickMove();
					}
				}
				m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
				if(centerLeftGid == 9){
					stairLayer2->removeTileAt(Vec2(col-1,row));
				}else if(centerMiddlerGid == 9){
					stairLayer2->removeTileAt(Vec2(col,row));
				}else if(topLeftGid == 9){
					stairLayer2->removeTileAt(Vec2(col-1,row-1));
				}else if(topMiddleGid == 9){
					stairLayer2->removeTileAt(Vec2(col,row-1));
				}
			}
			if(topRightGid == 9 || frontBottomGid == 9 || frontMiddleGid == 9){
				m_infoLayer->goldAddOne();
				goldAnim();
				int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
				int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
				if(Player::skillState != Player_Active){
					GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
					if(potentialGoldNum == potentialIndex*300){
						GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
						GAMEDATA::getInstance()->setActiveGoldNum(0);
						Player::skillState = Player_Active;
						m_player->quickMove();
					}
				}
				m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
				if(topRightGid == 9){
					stairLayer2->removeTileAt(Vec2(col+1,row-1));
				}else if(frontBottomGid == 9){
					stairLayer2->removeTileAt(Vec2(col+1,row+1));
				}else if(frontMiddleGid == 9){
					stairLayer2->removeTileAt(Vec2(col+1,row));
				}
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}else if(topRightGid > 0 || frontBottomGid > 0 || frontMiddleGid > 0){
				if(Player::skillState == Player_Normal || Player::skillState == Player_Magic){
					m_player->setPositionX(m_player->getPositionX()-speed);
					beStop = true;
				}else if(Player::skillState == Player_Transition_Fly || Player::skillState == Player_Transition_Super || Player::skillState == Player_Super){
					if(frontBottomGid > 0){
						m_player->setPositionX(m_player->getPositionX()-speed);
					}
				}
			}else{
				beStop = false;
				if(m_player->getPositionX() < 200){
					m_player->setPositionX(m_player->getPositionX()+speed_x);
				}
			}
			if(((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid))){
				int upSpeed = m_player->getUpSpeed();
				if(Player::skillState != Player_Fly && Player::skillState != Player_Active){
					m_player->setUpSpeed(upSpeed-speed_y);
				}
			}else{
				m_player->setUpSpeed(0);
				playerRowNum = row;
				if(Player::skillState != Player_Fly && Player::skillState != Player_Active){
					if(row == 7){
						m_player->setPositionY(230.4);
					}else if(row == 6){
						m_player->setPositionY(230.4+32);
					}else if(row == 5){
						m_player->setPositionY(230.4+64);
					}else if(row == 8){
						m_player->setPositionY(230.4-32);
					}else if(row == 9){
						m_player->setPositionY(230.4-64);
					}else if(row == 10){
						m_player->setPositionY(230.4-96);
					}
					if(Player::state != Player_Run){
						Audio::getInstance()->playSound("Music/jump.mp3");
						m_player->move();
					}
					int gid1 = 0;
					int gid2 = 0;
					for(int k = row+1;k>4;k--){
						gid1 = stairLayer2->getTileGIDAt(Vec2(col-1,k));
						gid2 = stairLayer2->getTileGIDAt(Vec2(col,k));
						if((gid1>0 && gid1!=9) || (gid2>0 && gid2!=9)){
							playerRowNum --;
							m_player->setPositionY(m_player->getPositionY()+32);
						}else{
							break;
						}
					}
				}
			}
			if((ceilGid1 != 9 && ceilGid1 != 0) || (ceilGid2 != 9 && ceilGid2 != 0)){
				canJump = false;
			}else{
				if((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid)){
					canJump = false;
					canSlide = false;
				}else{
					canJump = true;
					canSlide = true;
				}
			}
		}else{
			if(row >= 1 && col >= 2){
				int topLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row-1));
				int topMiddleGid = stairLayer->getTileGIDAt(Vec2(col,row-1));
				int topRightGid = stairLayer->getTileGIDAt(Vec2(col+1,row-1));
				int bottomLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row+2));
				int bottomMiddleGid = stairLayer->getTileGIDAt(Vec2(col,row+2));
				int frontMiddleGid = stairLayer->getTileGIDAt(Vec2(col+1,row));
				int frontBottomGid = stairLayer->getTileGIDAt(Vec2(col+1,row+1));
				int centerLeftGid = stairLayer->getTileGIDAt(Vec2(col-1,row));
				int centerMiddlerGid = stairLayer->getTileGIDAt(Vec2(col,row));
				int ceilGid1 = stairLayer->getTileGIDAt(Vec2(col,row-2));
				int ceilGid2 = stairLayer->getTileGIDAt(Vec2(col+1,row-2));
				int topGid = stairLayer->getTileGIDAt(Vec2(col-1,row-1));
				if(centerLeftGid == 9 || centerMiddlerGid == 9 || topLeftGid == 9 || topMiddleGid == 9){
					m_infoLayer->goldAddOne();
					goldAnim();
					int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
					int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
					if(Player::skillState != Player_Active){
						GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
						if(potentialGoldNum == potentialIndex*300){
							GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
							GAMEDATA::getInstance()->setActiveGoldNum(0);
							Player::skillState = Player_Active;
							m_player->quickMove();
						}
					}
					m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
					if(centerLeftGid == 9){
						stairLayer->removeTileAt(Vec2(col-1,row));
					}else if(centerMiddlerGid == 9){
						stairLayer->removeTileAt(Vec2(col,row));
					}else if(topLeftGid == 9){
						stairLayer->removeTileAt(Vec2(col-1,row-1));
					}else if(topMiddleGid == 9){
						stairLayer->removeTileAt(Vec2(col,row-1));
					}
				}
				if(topRightGid == 9 || frontBottomGid == 9 || frontMiddleGid == 9){
					m_infoLayer->goldAddOne();
					goldAnim();
					int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
					int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
					if(Player::skillState != Player_Active){
						GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
						if(potentialGoldNum == potentialIndex*300){
							GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
							GAMEDATA::getInstance()->setActiveGoldNum(0);
							Player::skillState = Player_Active;
							m_player->quickMove();
						}
					}
					m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
					if(topRightGid == 9){
						stairLayer->removeTileAt(Vec2(col+1,row-1));
					}else if(frontBottomGid == 9){
						stairLayer->removeTileAt(Vec2(col+1,row+1));
					}else if(frontMiddleGid == 9){
						stairLayer->removeTileAt(Vec2(col+1,row));
					}
					if(m_player->getPositionX() < 200){
						m_player->setPositionX(m_player->getPositionX()+speed_x);
					}
				}else if(topRightGid > 0 || frontBottomGid > 0 || frontMiddleGid > 0){
					if(Player::skillState == Player_Normal || Player::skillState == Player_Magic){
						m_player->setPositionX(m_player->getPositionX()-speed);
						beStop = true;
					}else if(Player::skillState == Player_Transition_Fly || Player::skillState == Player_Transition_Super || Player::skillState == Player_Super){
						if(frontBottomGid > 0){
							m_player->setPositionX(m_player->getPositionX()-speed);
						}
					}
				}else{
					beStop = false;
					if(m_player->getPositionX() < 200){
						m_player->setPositionX(m_player->getPositionX()+speed_x);
					}
				}
				if(((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid))){
					int upSpeed = m_player->getUpSpeed();
					if(Player::skillState != Player_Fly && Player::skillState != Player_Active){
						m_player->setUpSpeed(upSpeed-speed_y);
					}
				}else{
					m_player->setUpSpeed(0);
					playerRowNum = row;
					if(Player::skillState != Player_Fly && Player::skillState != Player_Active){
						if(row == 7){
							m_player->setPositionY(230.4);
						}else if(row == 6){
							m_player->setPositionY(230.4+32);
						}else if(row == 5){
							m_player->setPositionY(230.4+64);
						}else if(row == 8){
							m_player->setPositionY(230.4-32);
						}else if(row == 9){
							m_player->setPositionY(230.4-64);
						}else if(row == 10){
							m_player->setPositionY(230.4-96);
						}
						if(Player::state != Player_Run){
							Audio::getInstance()->playSound("Music/jump.mp3");
							m_player->move();
						}
						int gid1 = 0;
						int gid2 = 0;
						for(int k = row+1;k>4;k--){
							gid1 = stairLayer->getTileGIDAt(Vec2(col-1,k));
							gid2 = stairLayer->getTileGIDAt(Vec2(col,k));
							if((gid1>0 && gid1!=9) || (gid2>0 && gid2!=9)){
								playerRowNum --;
								m_player->setPositionY(m_player->getPositionY()+32);
							}else{
								break;
							}
						}
					}
				}
				if((ceilGid1 != 9 && ceilGid1 != 0) || (ceilGid2 != 9 && ceilGid2 != 0)){
					canJump = false;
				}else{
					if((bottomLeftGid == 9 || !bottomLeftGid) && (bottomMiddleGid == 9 || !bottomMiddleGid)){
						canJump = false;
						canSlide = false;
					}else{
						canJump = true;
						canSlide = true;
					}
				}
			}
		}
	}
	return false;
}

bool MonsterLayer::checkSpritesCollision(Node* sprite1,Node* sprite2){
	auto monster = (Monster*)sprite2;
	float w1 = sprite1->getContentSize().width;
	float h1 = sprite1->getContentSize().height;
	float w2 = sprite2->getContentSize().width;
	float h2 = sprite2->getContentSize().height;
	if(monster->getID() == 1){		
		if(monster->getCurrentFrame() == 0){
			return false;
		}else if(monster->getCurrentFrame() == 4){
			if(abs(sprite1->getPositionX(),sprite2->getPositionX())<w1/2+w2/2-50 && 
				abs(sprite1->getPositionY(),sprite2->getPositionY())<h1/2+h2*3/8-40){
				return true;
			}
		}else if(monster->getCurrentFrame() == 5){
			if(abs(sprite1->getPositionX(),sprite2->getPositionX())<w1/2+w2/2-50 && 
				abs(sprite1->getPositionY(),sprite2->getPositionY())<h1/2+h2*2/8-40){
				return true;
			}
		}else if(abs(sprite1->getPositionX(),sprite2->getPositionX())<w1/2+w2/2-50 && 
			abs(sprite1->getPositionY(),sprite2->getPositionY())<h1/2+h2*(monster->getCurrentFrame()+1)/8-40){
			return true;
		}	
	}else{
		if(abs(sprite1->getPositionX(),sprite2->getPositionX())<w1/2+w2/2-50 && abs(sprite1->getPositionY(),sprite2->getPositionY())<h1/2+h2/2-30){
			return true;
		}
	}
	return false;
}

float MonsterLayer::abs(float num1,float num2){
	if(num1 >= num2){
		return num1-num2;
	}else{
		return num2-num1;
	}
}

void MonsterLayer::magneticGold(Sprite* gold,int index){
	auto cp1 = Point(gold->getPositionX(),gold->getPositionY());
	Point cp2;
	if(Player::state == Player_Jump){
		if(m_player->getUpSpeed() > 50){
			cp2 = Point(m_player->getPositionX()+100,m_player->getPositionY()+120);
		}else if(m_player->getUpSpeed() > 40){
			cp2 = Point(m_player->getPositionX()+100,m_player->getPositionY()+80);
		}else if(m_player->getUpSpeed() > 30){
			cp2 = Point(m_player->getPositionX()+100,m_player->getPositionY()+30);
		}else if(m_player->getUpSpeed() > 20){
			cp2 = Point(m_player->getPositionX()+100,m_player->getPositionY()+24);
		}else if(m_player->getUpSpeed() > 10){
			cp2 = Point(m_player->getPositionX()+100,m_player->getPositionY()+10);
		}else if(m_player->getUpSpeed() > 0){
			cp2 = Point(m_player->getPositionX()+100,m_player->getPositionY());
		}else if(m_player->getUpSpeed() > -10){
			cp2 = Point(m_player->getPositionX()+100,m_player->getPositionY()-70);
		}else if(m_player->getUpSpeed() > -20){
			cp2 = Point(m_player->getPositionX()+100,m_player->getPositionY()-120);
		}else if(m_player->getUpSpeed() > -30){
			cp2 = Point(m_player->getPositionX()+100,m_player->getPositionY()-140);
		}else if(m_player->getUpSpeed() > -34){
			cp2 = Point(m_player->getPositionX()+100,m_player->getPositionY()-50);
		}else{
			cp2 = Point(m_player->getPositionX()+100,m_player->getPositionY()+10);
		}
	}else{
		if(Player::skillState == Player_Fly){
			cp2 = Point(m_player->getPositionX()+100,m_player->getPositionY());
		}else{
			cp2 = Point(m_player->getPositionX()+100,m_player->getPositionY());
		}
	}
	if(Player::skillState == Player_Active || Player::skillState == Player_Fly){	
		ccBezierConfig bezier;
		bezier.controlPoint_1 = Point(cp1.x-(cp1.x-cp2.x)/3,cp1.y-(cp1.y-cp2.y)/3);
		bezier.controlPoint_2 = Point(cp1.x-(cp1.x-cp2.x)*2/3,cp1.y-(cp1.y-cp2.y)*2/3);
		bezier.endPosition = cp2;
		auto bezierAction = BezierTo::create(0.05f, bezier);
		auto removeC = CallFunc::create([=](){
			gold->removeFromParentAndCleanup(true);
			m_infoLayer->goldAddOne();
			goldAnim();
			int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
			int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
			if(Player::skillState != Player_Active){
				GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
				if(potentialGoldNum == potentialIndex*300){
					GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
					GAMEDATA::getInstance()->setActiveGoldNum(0);
					Player::skillState = Player_Active;
					m_player->quickMove();
				}
			}
			m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
			if(index == 1){
				m_eatGold1.eraseObject(gold,false);
			}else{
				m_eatGold2.eraseObject(gold,false);
			}
		});
		Sequence* action = Sequence::create(bezierAction,removeC,NULL);
		gold->runAction(action);
	}else{
		ccBezierConfig bezier;
		bezier.controlPoint_1 = Point(cp1.x-(cp1.x-cp2.x)/3,cp1.y-(cp1.y-cp2.y)/3);
		bezier.controlPoint_2 = Point(cp1.x-(cp1.x-cp2.x)*2/3,cp1.y-(cp1.y-cp2.y)*2/3);
		bezier.endPosition = cp2;
		auto bezierAction = BezierTo::create(0.1f, bezier);
		auto removeC = CallFunc::create([=](){
			gold->removeFromParentAndCleanup(true);
			m_infoLayer->goldAddOne();
			goldAnim();
			int potentialIndex = GAMEDATA::getInstance()->getPotentialIndex();
			int potentialGoldNum = GAMEDATA::getInstance()->getActiveGoldNum();
			if(Player::skillState != Player_Active){
				GAMEDATA::getInstance()->setActiveGoldNum(potentialGoldNum+1);
				if(potentialGoldNum == potentialIndex*300){
					GAMEDATA::getInstance()->setPotentialIndex(potentialIndex+1);
					GAMEDATA::getInstance()->setActiveGoldNum(0);
					Player::skillState = Player_Active;
					m_player->quickMove();
				}
			}
			m_infoLayer->refreshProgress(potentialGoldNum,potentialIndex);
			if(index == 1){
				m_eatGold1.eraseObject(gold,false);
			}else{
				m_eatGold2.eraseObject(gold,false);
			}
		});
		Sequence* action = Sequence::create(bezierAction,removeC,NULL);
		gold->runAction(action);
	}
}

void MonsterLayer::pause(){
	for(auto monster : m_monsterVec){
		monster->getChildByTag(888)->pauseSchedulerAndActions();
	}
	for(auto gold : m_eatGold1){
		gold->pauseSchedulerAndActions();
	}
	for(auto gold : m_eatGold2){
		gold->pauseSchedulerAndActions();
	}
}

void MonsterLayer::resume(){
	for(auto monster : m_monsterVec){
		monster->getChildByTag(888)->resumeSchedulerAndActions();
	}
	for(auto gold : m_eatGold1){
		gold->resumeSchedulerAndActions();
	}
	for(auto gold : m_eatGold2){
		gold->resumeSchedulerAndActions();
	}
}

void MonsterLayer::goldAnim(){
	auto gold = Sprite::createWithSpriteFrameName("white_bg.png");
	gold->setPositionX(m_player->getPositionX()-10);
	gold->setPositionY(m_player->getPositionY()+45);
	this->addChild(gold);
	m_goldAnim.pushBack(gold);
	Vector<SpriteFrame*> m_goldFrames;
	SpriteFrame* frame;
	for(int i=0;i<5;i++){
		if(i == 4){
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("white_bg.png");
		}else{
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("gold_%d.png",i+1)->_string);
		}
		m_goldFrames.pushBack(frame);
	}
	auto goldAnimation = Animation::createWithSpriteFrames(m_goldFrames,0.06f);
	auto goldAnim = Animate::create(goldAnimation);
	gold->runAction(goldAnim);
}

bool MonsterLayer::isCanSlide(){
	return canSlide;
}

bool MonsterLayer::isCanJump(){
	return canJump;
}
	
bool MonsterLayer::isNeedContiSlide(){
	return needContiSlide;	
}
