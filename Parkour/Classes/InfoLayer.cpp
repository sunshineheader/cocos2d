#include "InfoLayer.h"
#include "GAMEDATA.h"
#include "PlayerState.h"
#include "Player.h"
#include "cocos-ext.h" 
#include "Chinese.h"
#include "Audio.h"
#include "GameState.h"
#include "GameStateInfo.h"
#include "GameResultInfo.h"

USING_NS_CC_EXT;

bool InfoLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	m_goldNum = 0;
	m_distance = 0;

	auto scoreBg = Scale9Sprite::create("game_info_bg_2.png");
	scoreBg->setContentSize(Size(200,53));
	scoreBg->setPosition(120,visibSize.height-29);
	this->addChild(scoreBg);

	auto scoreTxt = Sprite::createWithSpriteFrameName("game_score.png");
	scoreTxt->setPosition(57,visibSize.height-27);
	this->addChild(scoreTxt);

	ttf_gold = LabelAtlas::create("0","score_num.png",15,30,48);
	ttf_gold->setAnchorPoint(Point(0.5,0.5));
	ttf_gold->setPosition(134.5,visibSize.height-27);
	this->addChild(ttf_gold);

	auto fenTxt = Sprite::createWithSpriteFrameName("game_fen.png");
	fenTxt->setPosition(197,visibSize.height-27);
	this->addChild(fenTxt);

	auto distanceBg = Scale9Sprite::create("game_info_bg_2.png");
	distanceBg->setContentSize(Size(180,53));
	distanceBg->setPosition(325,visibSize.height-29);
	this->addChild(distanceBg);

	auto distanceTxt = Sprite::createWithSpriteFrameName("game_distance.png");
	distanceTxt->setPosition(275,visibSize.height-27);
	this->addChild(distanceTxt);

	ttf_distance = LabelAtlas::create("0","distance_num.png",15,30,48);
	ttf_distance->setAnchorPoint(Point(0.5,0.5));
	ttf_distance->setPosition(340.5,visibSize.height-27);
	this->addChild(ttf_distance);

	auto miTxt = Sprite::createWithSpriteFrameName("game_mi.png");
	miTxt->setPosition(393,visibSize.height-27);
	this->addChild(miTxt);

	auto progressBg = Sprite::createWithSpriteFrameName("game_progress_bg.png");
	progressBg->setPosition(395,59*visibSize.height/480);
	this->addChild(progressBg);

	if(GAMEDATA::getInstance()->getPlayerLevel() < 29){
		auto missionBg = Scale9Sprite::create("game_info_bg_2.png");
		missionBg->setContentSize(Size(240,53));
		missionBg->setPosition(550,visibSize.height-29);
		this->addChild(missionBg);

		auto mission = LabelBMFont::create(ChineseWord(String::createWithFormat("mission_%d",
			GAMEDATA::getInstance()->getPlayerLevel())->_string.c_str()),"game_mission.fnt");
		mission->setPosition(550,visibSize.height-21);
		this->addChild(mission);

		missionProgress = LabelBMFont::create(String::createWithFormat("0/%d",
			GAMEDATA::getInstance()->getCurrentMissionNum())->_string.c_str(),"game_mission.fnt");
		missionProgress->setPosition(550,visibSize.height-37);
		this->addChild(missionProgress);
	}

	progress = Sprite::create("game_progress.png",Rect(437,0,0,74));
	progress->setAnchorPoint(Point(0,0.5));
	progress->setPosition(240,59*visibSize.height/480);
	this->addChild(progress);

	return true;
}

void InfoLayer::refreshMission(){
	if(GAMEDATA::getInstance()->getPlayerLevel() < 29){
		if(GameStateInfo::getInstance()->getGameState() == Game_End && GameResultInfo::getInstance()->getGameResult() == 1){
			missionProgress->setString(String::createWithFormat("%d/%d",
				GAMEDATA::getInstance()->getHasFinishedNum(),
				GAMEDATA::getInstance()->getLastMissionNum())->_string);
		}else{
			missionProgress->setString(String::createWithFormat("%d/%d",
				GAMEDATA::getInstance()->getHasFinishedNum(),
				GAMEDATA::getInstance()->getCurrentMissionNum())->_string);
		}
	}
}

void InfoLayer::refreshProgress(int potentialGoldNum,int potentialIndex){
	float width = ((float)(potentialGoldNum))/potentialIndex/300*374;
	if(Player::skillState == Player_Active){
		progress->setTextureRect(Rect(68,0,374,74));
	}else{
		progress->setTextureRect(Rect(437-width,0,width,74));
	}
}

void InfoLayer::goldAddOne()
{
	Audio::getInstance()->playSound("Music/gold.mp3");
	int eatGoldNum = GAMEDATA::getInstance()->getEatGoldNum();
	GAMEDATA::getInstance()->setEatGlodNum(eatGoldNum+1);
	m_goldNum++;

	if(Player::skillState == Player_Magic){
		GAMEDATA::getInstance()->setEatGoldByMagneticNums(GAMEDATA::getInstance()->getEatGoldByMagneticNums()+1);
	}
}
void InfoLayer::distanceAddOne()
{
	m_distance++;
	std::string s;
	s = String::createWithFormat("%d",m_distance)->_string;
	ttf_distance->setString(s);
	std::string s2;
	if(m_goldNum/100 == 0){
		s2 = String::createWithFormat("%d",m_distance)->_string;
		GAMEDATA::getInstance()->setGameScore(m_distance);
	}else{
		s2 = String::createWithFormat("%d",m_goldNum/100*m_distance)->_string;
		GAMEDATA::getInstance()->setGameScore(m_goldNum/100*m_distance);
	}
	ttf_gold->setString(s2);
}

int InfoLayer::getGoldNum()
{
	return m_goldNum;
}

int InfoLayer::getDisNum()
{
	return m_distance;
}
