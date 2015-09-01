#include "BackgroundLayer.h"
#include "cocos2d.h"
#include "ObjectTag.h"
#include "Player.h"
#include "PlayerState.h"
#include "TollgateScene.h"

USING_NS_CC;
BackgroundLayer::BackgroundLayer(){
}

BackgroundLayer::~BackgroundLayer()
{
}

bool BackgroundLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    m_bg1 = Sprite::create("background.jpg");
    m_bg1->setPosition(Point(0, visibleSize.height * 0.5f));
    this->addChild(m_bg1);
    m_bg2 = Sprite::create("background.jpg");
    m_bg2->setPosition(Point(visibleSize.width-1, visibleSize.height * 0.5f));
    this->addChild(m_bg2);
    return true;
}

void BackgroundLayer::logic(float dt){
	float posX1 = m_bg1->getPositionX(); 
    float posX2 = m_bg2->getPositionX(); 
    float iSpeed = speed;  
	if(Player::skillState == Player_Active || Player::skillState == Player_Fly){
		iSpeed = iSpeed*TollgateScene::level*2;
	}else{
		iSpeed =iSpeed*TollgateScene::level;
	}
    posX1 -= iSpeed;
    posX2 -= iSpeed;
	int iVisibleWidth = Director::getInstance()->getVisibleSize().width;
    if (posX1 < -iVisibleWidth * 0.5f) {
		posX2 = iVisibleWidth*0.5f;
        posX1 = iVisibleWidth*1.5f-1;
    }
    if (posX2 < -iVisibleWidth * 0.5f) {
        posX1 = iVisibleWidth * 0.5f;
        posX2 = iVisibleWidth * 1.5f-1;
    }
    m_bg1->setPositionX(posX1);
    m_bg2->setPositionX(posX2);
}

void BackgroundLayer::setBackGroudSpeed(float speed){
	this->speed=speed;
}

Sprite* BackgroundLayer::createBorder(Point pos)
{
    auto border = Sprite::create("border.png");
	border->setTag(ObjectTag_Border);
    Size borderSize = border->getContentSize();
    auto body = PhysicsBody::createBox(borderSize);
    body->setDynamic(false);
    body->setCategoryBitmask(1);    // 0001
    body->setCollisionBitmask(1);   // 0001
    body->setContactTestBitmask(1); // 0001
    border->setPhysicsBody(body);
    border->setPosition(pos);
    return border;
}
