#include "GameLayer.h"
#include "GameResultScene.h"
#include "Chinese.h"
#include "InfoLayer.h"

bool GameLayer::init()
{
 if (!Layer::init())
 {
  return false;
 }
 //随机种子的初始化
 srand((unsigned)time(NULL));
 
 auto visibleSize = Director::getInstance()->getVisibleSize();
 auto origin = Director::getInstance()->getVisibleOrigin();


 //添加地面缓冲
 m_batchNode = SpriteBatchNode::create("wall.png",50);
 m_batchNode->setAnchorPoint(Point::ZERO);
 m_batchNode->setPosition(ccp(0, 0));
 this->addChild(m_batchNode);
 //添加金币缓冲
 m_goldBatchNode = SpriteBatchNode::create("gold.png", 50);
 m_goldBatchNode->setAnchorPoint(Point::ZERO);
 m_goldBatchNode->setPosition(Point::ZERO);
 this->addChild(m_goldBatchNode);
 //添加墙壁缓冲
 m_wallBatchNode = SpriteBatchNode::create("wall.png", 50);
 m_wallBatchNode->setAnchorPoint(Point::ZERO);
 m_wallBatchNode->setPosition(Point::ZERO);
 this->addChild(m_wallBatchNode);


 //在地面缓冲中添加精灵，即开始时地面
 for (int i = 0; i < 30; i++)
 {
  auto walls = Sprite::create("wall.png");
  walls->setAnchorPoint(Point::ZERO);
  walls->setPosition(ccp(i * 32, 32));
  m_batchNode->addChild(walls);
  m_Vector.push_back(walls);
 }
  //建立人物 
 //player = Player::getInstance();
 player->setAnchorPoint(ccp(0,0)); 
 player->setPosition(ccp(100,160));
 //player->setPlayState(STATE_PLAYER_RUN);
 this->addChild(player); 

 gameInfo = InfoLayer::create();
 this->addChild(gameInfo);

 //触摸建立
 auto listener = EventListenerTouchOneByOne::create();
 listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
 auto dispatcher = Director::getInstance()->getEventDispatcher();
 dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
 
 TMXTiledMap* map = TMXTiledMap::create("test.tmx");
 TMXLayer* background = map->layerNamed("ground");
 background->setAnchorPoint(ccp(0, 0));
 this->addChild(map);

 this->schedule(schedule_selector(GameLayer::timeCallBcak),0.016f,kRepeatForever,0);
 this->schedule(schedule_selector(GameLayer::distanceCallBack),0.1f,kRepeatForever,0);
 //碰撞定时器
 this->schedule(schedule_selector(GameLayer::bobCallBcak), 0.016);

 this->schedule(schedule_selector(GameLayer::toResultScene), 10,0,0);

 return true;
}

bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("on touch begin");
	//player->setSpeed(DEFLAUT_SPEEDY);
	//player->setPlayState(STATE_PLAYER_JUMP);
	return false;
}

void GameLayer::distanceCallBack(float f)
{
	gameInfo->distanceAddOne();
}

void GameLayer::timeCallBcak(float f)//地图物体的移动
{
	//墙壁的移动
	int n = m_Vector.size();//容器的遍历
	for (int i = 0; i < n; i++)
	{
		m_Vector[i]->setPositionX(m_Vector[i]->getPositionX() - MOVING_GAP);
		if (m_Vector[i]->getPositionX() <= -m_Vector[i]->getContentSize().width)//跑出屏幕左边则清除同时在最左边随机生成
		{
			m_batchNode->removeChild(m_Vector[i], true);
			m_Vector.erase(m_Vector.begin() + i);
			int i = rand() % 10;//清除后添加
			CCLOG("i=%d", i);
			if (i>0)//在最后添加一个地面块
			{
				auto walls = Sprite::create("wall.png");
				walls->setAnchorPoint(Point::ZERO);
				walls->setPosition(ccp((*(m_Vector.end() - 1))->getPositionX() + 32, 32));//加到最后
				m_batchNode->addChild(walls);
				m_Vector.push_back(walls);
			}
			else//空2格再添加地面块（1/10的概率）
			{
				auto walls = Sprite::create("wall.png");
				walls->setAnchorPoint(Point::ZERO);
				walls->setPosition(ccp((*(m_Vector.end() - 1))->getPositionX() + 3 * 32, 32));//加到最后
				m_batchNode->addChild(walls);
				m_Vector.push_back(walls);


			}
			//右边将要出现的物品
			//右边将要产生墙壁
			auto produceWall = rand() % 10;//出现墙壁概率
			auto wallHigh = rand() % 4;//墙壁高度
			if (produceWall == 0)
			{
				for (int j = 0; j < wallHigh; j++)
				{
					auto wall = Sprite::create("wall.png");
					wall->setAnchorPoint(Point::ZERO);
					wall->setPosition(ccp((*(m_Vector.end() - 1))->getPositionX(), 32 * (j + 2)));
					m_wallVector.push_back(wall);
					m_wallBatchNode->addChild(wall);
				}
			}
			// 1.产生金币 1/5的概率
			auto produceGold = rand() % 5;
			if (produceGold == 0)
			{
				auto goldHigh = rand() % 3 + 3;//金币高度
				if (produceWall == 0) goldHigh = wallHigh + 2;//金币在墙壁的上方
				auto gold = Sprite::create("gold.png");
				gold->setAnchorPoint(Point::ZERO);
				gold->setPosition(ccp((*(m_Vector.end() - 1))->getPositionX(), 32 * goldHigh));
				m_goldVector.push_back(gold);
				m_goldBatchNode->addChild(gold);
			}
			


		}
	}
	//金币的移动
		for (auto i = 0; i < m_goldVector.size();)
		{
			m_goldVector[i]->setPositionX(m_goldVector[i]->getPositionX() - MOVING_GAP);
			if (m_goldVector[i]->getPositionX() < -m_goldVector[i]->getContentSize().width)
			{
				m_goldBatchNode->removeChild(m_goldVector[i], true);
				m_goldVector.erase(m_goldVector.begin() + i);
				


			}
			else
			{
				i++;
			}
		}
	//墙壁的移动
		for (auto i = 0; i < m_wallVector.size();)
		{
			m_wallVector[i]->setPositionX(m_wallVector[i]->getPositionX() - MOVING_GAP);
			if (m_wallVector[i]->getPositionX() < -m_wallVector[i]->getContentSize().width)
			{
				m_wallBatchNode->removeChild(m_wallVector[i], true);
				m_wallVector.erase(m_wallVector.begin() + i);
			}
			else i++;
		}
}


void GameLayer::bobCallBcak(float f)//碰撞检测
{
	if (IscollWithDown())//人物和下方有接触
	{
		//if (player->getPlayState() == STATE_PLAYER_DOWN)
		//{
		//	player->setPlayState(STATE_PLAYER_RUN);
		//}
	}
	else
	{
		//if (player->getPlayState()==STATE_PLAYER_RUN)
		//	player->setPlayState(STATE_PLAYER_DOWN);
	}
	if (IscollWithUp())//人物和上方有接触
	{
		//if (player->getPlayState() == STATE_PLAYER_JUMP)player->setPlayState(STATE_PLAYER_RUN);
	}
	if (IscollWithRight())//人物和右边有接触
	{
		this->schedule(schedule_selector(GameLayer::playerCallBcak), 0.1);
	}
	else
	{
		this->unschedule(schedule_selector(GameLayer::playerCallBcak));
	}
	IscollWithLeft();
	
	IscollWithGold();//移到主界面去了，为了和信息界面交互
}

void GameLayer::playerCallBcak(float f)
{
	player->setPositionX(player->getPositionX() - MOVING_GAP);
	if (player->getPositionX() < 0)
	{
		CCLOG("Game over");
	}
}

bool GameLayer::IsDie()//判断人物是否死亡
{
	return false;
}

bool GameLayer::IscollWithGold()//是否与金币碰撞
{
	for (int i = 0; i < m_goldVector.size(); )//遍历
	{
		if (m_goldVector[i]->getBoundingBox().intersectsRect(player->getBoundingBox()))
		{
			m_goldBatchNode->removeChild(m_goldVector[i], true);//发生碰撞则移除并返回
			m_goldVector.erase(m_goldVector.begin() + i);
			gameInfo->goldAddOne();
			return true;
		}
		else i++;//无碰撞则往后遍历
	}
	return false;


}

bool GameLayer::IscollWithDown()
{
	Point point;//中间点
	point.x = player->getBoundingBox().getMidX();
	point.y = player->getBoundingBox().getMinY();
	//增加碰厨点
	Point point1;//左边点
	point1.x = player->getBoundingBox().getMinX();
	point1.y = player->getBoundingBox().getMinY();
	Point point2;//右边点
	point2.x = player->getBoundingBox().getMaxX()-10;
	point2.y = player->getBoundingBox().getMinY();

	//是否与地面接触
	for (int i = 0; i < m_Vector.size(); i++)
	{
		if (m_Vector[i]->getBoundingBox().containsPoint(point)
			//|| m_Vector[i]->getBoundingBox().containsPoint(point1)
			|| m_Vector[i]->getBoundingBox().containsPoint(point2))
		{
			return true;
		}
	}
	//是否与wall碰撞
	for (int i = 0; i < m_wallVector.size(); i++)
	{
		if (m_wallVector[i]->getBoundingBox().containsPoint(point)
			//|| m_wallVector[i]->getBoundingBox().containsPoint(point1)
			|| m_wallVector[i]->getBoundingBox().containsPoint(point2))
		{
			return true;
		}
	}
	return false;
}

bool GameLayer::IscollWithUp()
{
	Point point1,point2,point3;
	point1.x = player->getBoundingBox().getMinX();
	point1.y = player->getBoundingBox().getMaxY();
	point2.x = player->getBoundingBox().getMidX();
	point2.y = player->getBoundingBox().getMaxY();
	point3.x = player->getBoundingBox().getMaxX();
	point3.y = player->getBoundingBox().getMaxY();
	for (int i = 0; i < m_Vector.size(); i++)
	{
		if (//m_Vector[i]->getBoundingBox().containsPoint(point1)//头发可以穿过
			 m_Vector[i]->getBoundingBox().containsPoint(point2)
			| m_Vector[i]->getBoundingBox().containsPoint(point3)
			)
		{
			return true;
		}
		else if (m_Vector[i]->getPositionX() > point1.x)
		{
			return false;
		}
	}
	return false;
}

bool GameLayer::IscollWithRight()
{
	Point point;
	point.x = player->getBoundingBox().getMaxX();
	point.y = player->getBoundingBox().getMinY()+10;
	Point point1;
	point1.x = player->getBoundingBox().getMaxX();
	point1.y = player->getBoundingBox().getMidY();
	Point point2;
	point2.x = player->getBoundingBox().getMaxX();
	point2.y = player->getBoundingBox().getMaxY();
	//判断是否与右侧地面碰撞
	for (int i = 0; i < m_Vector.size(); i++)
	{
		if (m_Vector[i]->getBoundingBox().containsPoint(point)//无法在地面上走动，y向上移动一点
			|| m_Vector[i]->getBoundingBox().containsPoint(point1)
			|| m_Vector[i]->getBoundingBox().containsPoint(point2))
		{
			return true;
		}
		/*else if (m_vector[i]->getpositionx() > point.x)//当添加墙壁后应去除
		{
			return false;
		}*/
	}
	//判断是否与右边墙壁碰撞
	for (int i = 0; i < m_wallVector.size(); i++)
	{
		if (m_wallVector[i]->getBoundingBox().containsPoint(point)
			|| m_wallVector[i]->getBoundingBox().containsPoint(point1)
			|| m_wallVector[i]->getBoundingBox().containsPoint(point2))
		{
			return true;
		}
	}
	return false;
}

bool GameLayer::IscollWithLeft()
{
	Point point;
	point.x = player->getBoundingBox().getMinX();
	point.y = player->getBoundingBox().getMidY();
	for (int i = 0; i < m_Vector.size(); i++)
	{
		if (m_Vector[i]->getBoundingBox().containsPoint(point))
		{
			return true;
		}
		else if (m_Vector[i]->getPositionX() > point.x)
		{
			return false;
		}
	}
	return false;
}

void GameLayer::toResultScene(float dt) {
	Director::getInstance()->replaceScene(
			TransitionSlideInR::create(1, GameResultScene::create()));
}