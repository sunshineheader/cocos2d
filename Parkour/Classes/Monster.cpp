#include "Monster.h"
#include "ObjectTag.h"

Monster::Monster()
{
}
 
Monster::~Monster()
{
}
 
Monster* Monster::create(int ID)
{
    auto monster = new Monster();
    
    if(monster && monster->init(ID)) 
    {
    monster->autorelease();
    }
    else
    {
    CC_SAFE_DELETE(monster);
    }
    
    return monster;
}
 
bool Monster::init(int ID)
{
	animTime = 0;
	startAnim = false;
    this->m_ID = ID;
 
    if (ID == 1)
    {
        m_sModelPath = Value("thorns_1.png");
    }
    else if (ID == 2)
    {
        m_sModelPath = Value("monster.png");
    }
	else if(ID == 3){
		m_sModelPath = Value("game_prop_magnetic.png");
	}
	else if(ID == 4){
		m_sModelPath = Value("game_prop_potential.png");
	}
	else if(ID == 5){
		m_sModelPath = Value("game_prop_super.png");
	}
	else if(ID == 6){
		m_sModelPath = Value("prop_gift.png");
	}
    return true;
}

void Monster::joinToMap(Node* parent)
{
	Sprite* sp = Sprite::createWithSpriteFrameName(m_sModelPath.asString().c_str());
	sp->setTag(888);
	this->addChild(sp);
	if(m_ID == 1){
		this->setContentSize(Size(sp->getContentSize().width*0.1f,sp->getContentSize().height*0.5f));
	}else{		
		this->setContentSize(sp->getContentSize()*0.5f);
	}
	this->setPosition(this->m_iPosX+10,this->m_iPosY+10);
	parent->addChild(this,20);	
	
	if(m_ID == 1){
		Vector<SpriteFrame*> m_thornFrames;
		SpriteFrame* frame1;
		for(int i=0;i<6;i++){
			if(i == 4){
				frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("thorns_3.png");
			}else if(i == 5){
				frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("thorns_2.png");
			}else{
				frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("thorns_%d.png",i+1)->_string);
			}
			m_thornFrames.pushBack(frame1);
		}
		auto animation1 = Animation::createWithSpriteFrames(m_thornFrames,0.3f);
		auto thornAnimate = RepeatForever::create(Animate::create(animation1));
		startAnim = true;
		sp->runAction(thornAnimate);
	}
}

int Monster::getCurrentFrame(){
	CCLOG("animTime=%f",animTime);
	return ((int)(animTime/0.3f))%6;
}

void Monster::logic(float dt){
	if(startAnim){
		animTime += dt;
	}
}
