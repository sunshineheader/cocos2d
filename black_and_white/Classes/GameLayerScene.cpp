#include "GameLayerScene.h"
#include "GameCountLabel.h"
#include "GameOverScenecpp.h"
#include "GameBlocks.h"
#include "GameDefinition.h"
#include "GameBlocks.h"
#include "GameData.h"
#include "GameAudio.h"
#include "BlockParticle.h"
#include "ChineseWorld.h"
#include "BlockParticle.h"
#include "PayForGame.h"
#include"cocos2d.h"
#include <iostream>
using namespace cocos2d;


//static int RebornNumber = GameData::getInstance()->get_currcert_life();

Scene*GameLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = GameLayer::create();

	auto countLayer = GameCountLabel::create();

	scene->addChild(layer);

	scene->addChild(countLayer);

	return scene;
}
bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//GameCountLabel::getInstance()->reset();
	GameData::getInstance()->gameTimes += 1;

	GameData::getInstance()->reStart = false;
	GameData::getInstance()->gotoResult = false;
	game_counts = 0;
	index=0;
	tag = 1;
	countVar = 1;
	currcert_speed = 10;
	currcert_tag = 1;
	newspeed = 0.0;
	error_nbumer = 0;
	mytime = 0.0;
	distance = 0.0;
	add_new = 0.0;
	back_posititon_y = 0.0;
	length = 600;
	myTag = 1;
	GameAudio::getInstance()->init();
	layer_position_y = this->getPositionY();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	white_texture = Director::getInstance()->getTextureCache()->addImage("white.png");
	black_texture = Director::getInstance()->getTextureCache()->addImage("black.png");
	gray_texture = Director::getInstance()->getTextureCache()->addImage("gray.png");
	red_texture = Director::getInstance()->getTextureCache()->addImage("red.png");
	yellow_texture = Director::getInstance()->getTextureCache()->addImage("yellow.png");

	auto  listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	EveryThreeCallBack();
	EveryTwoCallBack();
	startGame();
	scheduleUpdate();
	return true;
}


void GameLayer::addYellowBlock()
{
	for (int i = 0; i < 4; i++)
	{	auto yellowblock = Sprite::createWithTexture(yellow_texture);
		yellowblock->setAnchorPoint(Vec2(0,0));
		yellowblock->setPosition(i*BLOCK_WITDH,0);
		addChild(yellowblock,100);
	}
}
void GameLayer::startGame()
{
	sprite_vec.clear();
	addYellowBlock();
	srand(time(NULL));
	pos_x =BLOCK_WITDH;
	pos_y = BLOCK_HEIGTH;
	for (int j = 0; j < COL_NUMBER; j++)
	{   
		int currcert_random_number = rand() % 4;
		for (int i = 0; i < ROW_NUMBER; i++)
		{
			if (currcert_random_number == i)
			{
				if (tag == 1)
				{
				  std::string start_gamne_string = ChineseWord("start");
				  start = Label::create();
				  start->setAnchorPoint(Vec2(0, 0));
				  start->setString(start_gamne_string);
				  start->setPosition(i*pos_x + 10, j*pos_y + 250);
				  start->setSystemFontSize(48);
				  addChild(start,2);
				  
				}
				 block = Sprite::createWithTexture(black_texture);
				 block->setAnchorPoint(Vec2(0, 0));
				 block->setTag(tag);
				 block->setColor(Color3B::BLACK);
				 block->setPosition(i*pos_x, j* pos_y+200);
				 addChild(block,1);
				 sprite_vec.pushBack(block);
				 tag++;
			}
			else
			{
			    block = Sprite::createWithTexture(white_texture);
				block->setAnchorPoint(Vec2(0, 0));
				block->setColor(Color3B::WHITE);
				block->setPosition(i*pos_x, j*pos_y+200);
				addChild(block,1);
				sprite_vec.pushBack(block);
			}
			
		}
	}

}

void GameLayer::reStartGame(float dt){
	//Director::getInstance()->pause();
	PauseGame = false;
	GameData::getInstance()->set_currcert_life(GameData::getInstance()->get_currcert_life()-1);
	
	
}

void GameLayer::gameFail(float dt){
	Director::getInstance()->pushScene(GameOver::createScene());
}


void GameLayer::update(float dt)
{
	if (GameData::getInstance()->reStart){
		GameData::getInstance()->reStart = false;
		//当前可点击黑块显示开始两字
		start->setVisible(true);
		error_nbumer = 0;
		int nextBlack = currentClick_count + 1;
		while (sprite_vec.at(nextBlack)->getColor() != Color3B::BLACK)
		{
			nextBlack++;
		}
		start->setPosition(sprite_vec.at(nextBlack)->getPositionX() + 10, sprite_vec.at(nextBlack)->getPositionY() + 50);
		scheduleOnce(schedule_selector(GameLayer::reStartGame), 0.3f);
	}

	if (GameData::getInstance()->gotoResult){
		GameData::getInstance()->gotoResult = false;
		scheduleOnce(schedule_selector(GameLayer::gameFail), 0.3f); //在1.0f之后执行，并且只执行一次。
	}
	//game over
	if (200 * (myTag + 1) + distance<-198)
	{
		// 暂停游戏
		PauseGame = true;
		startPlayGame = false;
		//TODO:整个layer上移400动画
		this->setPositionY(this->getPositionY() + 400);
		distance += 400;
		startTag = currcert_tag;
		//Director::getInstance()->pause();
		if (GameData::getInstance()->get_currcert_life()>0)
		{
			//当前可点击黑块显示开始两字
			start->setVisible(true);
			error_nbumer = 0;
			int nextBlack = currentClick_count + 1;
			while (sprite_vec.at(nextBlack)->getColor() != Color3B::BLACK)
			{
				nextBlack++;
			}
			start->setPosition(sprite_vec.at(nextBlack)->getPositionX() + 10, sprite_vec.at(nextBlack)->getPositionY() + 50);
			scheduleOnce(schedule_selector(GameLayer::reStartGame), 0.3f);
		}
		else{
			CCLOG("do revivor pay");
			//TODO:计费点
			PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_2);
			PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_8);
			PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_5);
			PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_6);
			PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_7);
		}
		return;
	}

	if ((!PauseGame) && startPlayGame){
		distance -= currcert_speed;
		this->setPositionY(layer_position_y + distance);
		add_new -= currcert_speed;
		if (add_new < -800)
		{
			index++;
			addNewBlock();
			add_new += 800;
		}
		this->getPosition();
	}
	

}
bool GameLayer::onTouchBegan(Touch*touch, Event*event)
{
	if (PauseGame){
		return true;
	}
	Vector<Sprite*>::iterator iter;
	for (iter = sprite_vec.begin(); iter != sprite_vec.end(); iter++)
	{
		s = (Sprite*)(*iter);
		if (s->getColor() == Color3B::BLACK &&  s->getBoundingBox().containsPoint(Vec2(touch->getLocation().x, touch->getLocation().y - distance)) && s->getTag() == currcert_tag)
		{
			myTag = s->getTag();
			currentClick_count = sprite_vec.getIndex(s);
			if (s->getTag() == startTag)
			{
				
				startPlayGame = true;
				currcert_tag++;
				Vec2 con = s->getContentSize();
				gary = Sprite::createWithTexture(gray_texture);
				gary->setPosition(Vec2(s->getPosition() + (con / 2)));
				addChild(gary, 10);

				game_counts=1;
				GameAudio::getInstance()->playsounds();
				GameData::getInstance()->set_currcert_sorce(game_counts);

				start->setVisible(false);
			}
			else 
			{
				currcert_tag++;
				Vec2 con = s->getContentSize();
				gary = Sprite::createWithTexture(gray_texture);
				gary->setPosition(Vec2(s->getPosition() + (con / 2)));
				addChild(gary, 2);
				game_counts++;
				removeChildByTag(currcert_tag);
				if (GameData::getInstance()->get_xiao_guo()){
					showParticleEffect(Vec2(s->getPosition()), this);
				}
				
			
				GameAudio::getInstance()->playsounds();
				GameData::getInstance()->set_currcert_sorce(game_counts);

			}
			
			break;
    	}   
		else if (s->getColor() == Color3B::WHITE &&  s->getBoundingBox().containsPoint(Vec2(touch->getLocation().x, touch->getLocation().y - distance)))
			{
				Vec2 con = s->getContentSize();
				red = Sprite::createWithTexture(red_texture);
				red->setPosition(Vec2(s->getPosition() + (con / 2)));
				addChild(red, 10);
				GameAudio::getInstance()->playerror();
				//购买过容错道具
				if (GameData::getInstance()->get_error_number()>0){
					if (error_nbumer<3){
						error_nbumer++;
						return true;
					}
					else{
						// 暂停游戏
						PauseGame = true;
						startPlayGame = false;
						startTag = currcert_tag;
						//处理复活逻辑
						if (GameData::getInstance()->get_currcert_life()>0)
						{
							//当前可点击黑块显示开始两字
							start->setVisible(true);
							error_nbumer = 0;
							int nextBlack = currentClick_count+1;
							while (sprite_vec.at(nextBlack)->getColor() != Color3B::BLACK)
							{
								nextBlack++;
							}
							start->setPosition(sprite_vec.at(nextBlack)->getPositionX() + 10, sprite_vec.at(nextBlack)->getPositionY() + 50);
							scheduleOnce(schedule_selector(GameLayer::reStartGame), 0.3f);
						}
						else{
							//TODO:计费点
							PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_2);
							PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_8);
							PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_5);
							PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_6);
							PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_7);
						}
					}
				}
				else{
					PauseGame = true;
					startPlayGame = false;
					startTag = currcert_tag;
					//处理复活逻辑
					if (GameData::getInstance()->get_currcert_life()>0)
					{
						//当前可点击黑块显示开始两字
						start->setVisible(true);
						error_nbumer = 0;
						int nextBlack = currentClick_count + 1;
						while (sprite_vec.at(nextBlack)->getColor() != Color3B::BLACK)
						{
							nextBlack++;
						}
						start->setPosition(sprite_vec.at(nextBlack)->getPositionX() + 10, sprite_vec.at(nextBlack)->getPositionY() + 50);
						scheduleOnce(schedule_selector(GameLayer::reStartGame),0.3f);
					}
					else{
						//TODO:计费点
						PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_2);
						PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_8);
						PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_5);
						PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_6);
						PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_7);
					}

				}
				break;
			}
		}
	
	return false;
}
void GameLayer::addNewBlock()
{
	//sprite_vec.clear();
	srand(time(NULL));
	//scheduleUpdate();
	pos_x = BLOCK_WITDH;
	pos_y = BLOCK_HEIGTH;

	for (int j = 0; j < 4; j++)
	{
		int currcert_random_number = rand() % 4;
		for (int i = 0; i < ROW_NUMBER; i++)
		{
			if (currcert_random_number == i)
			{
				auto block = Sprite::createWithTexture(black_texture);
				block->setAnchorPoint(Vec2(0, 0));
				block->setTag(tag);
				block->setColor(Color3B::BLACK);
				block->setPosition(i*pos_x, j* pos_y +200+ 1600+(index - 1) * 800);
				addChild(block, 1);
				sprite_vec.pushBack(block);
				tag++;
			}
			else
			{
				auto block = Sprite::createWithTexture(white_texture);
				block->setAnchorPoint(Vec2(0, 0));
				//block->setTag(tag);
				block->setColor(Color3B::WHITE);
				block->setPosition(i*pos_x, j*pos_y+200+1600+(index-1)*800);
				addChild(block, 1);
				sprite_vec.pushBack(block);
			}
		
		}
	}
}

void GameLayer::EveryThreeCallBack()
{
	if (GameData::getInstance()->gameTimes%3==0&&GameData::getInstance()->get_error_number()==0){
		PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_3);
	}
}

void GameLayer::EveryTwoCallBack()
{
	if ((GameData::getInstance()->gameTimes + 1) % 3 == 0 &&!GameData::getInstance()->get_xiao_guo()){
		PayForGame::getInstance()->payformoney_callback(PAYFORGAME_EVENT_4);
	}

}


