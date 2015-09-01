#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include "cocos2d.h"
#pragma once
#include "cocos2d.h"
#include "Player.h"//角色的加入
#include "Def.h"
#include <vector>
#include "InfoLayer.h"

using namespace cocos2d;
using namespace std;
USING_NS_CC;
class GameLayer : public Layer
{
public:
 bool init();
 CREATE_FUNC(GameLayer);
 bool onTouchBegan(Touch *touch, Event *unused_event);
 Player* player;
 InfoLayer* gameInfo;
 Sprite *wall;
 CCTMXTiledMap *tileMap;//载入地图、废弃
 CCTMXLayer *tileLay;//废弃
 CCTMXObjectGroup *tileObject;//废弃
 void timeCallBcak(float f);//地图物体移动
 void bobCallBcak(float f);//碰撞检测
 void playerCallBcak(float f);//右边有障碍主角移动
 void distanceCallBack(float f);
 SpriteBatchNode *m_batchNode;//地面砖块缓冲池
 SpriteBatchNode *m_goldBatchNode;//金币缓冲池
 SpriteBatchNode *m_wallBatchNode;//墙壁缓冲池
 vector< Sprite* > m_Vector;//存放地面容器
 vector< Sprite* > m_goldVector;//存放金币容器
 vector< Sprite* > m_wallVector;//存放墙壁容器
 bool IscollWithUp();
 bool IscollWithDown();
 bool IscollWithRight();
 bool IscollWithLeft();
 bool IscollWithGold();
 bool IsDie();
 void DownLogic();
 void UpLogic();
 void RightLogic();
 void LeftLogic();
 void toResultScene(float dt);
};
#endif
