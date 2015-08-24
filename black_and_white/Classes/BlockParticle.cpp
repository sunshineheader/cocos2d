#include"BlockParticle.h"
#include "GameBlocks.h"

void showParticleEffect(Point position,Node* node)
{
	log("Particle Particle Particle");
	ParticleExplosion* effect = ParticleExplosion::create();
	effect->setTexture(Director::getInstance()->getTextureCache()->addImage("star.png"));
	effect->setTotalParticles(100);
	effect->setStartColor(getColor4F());
	effect->setStartColorVar(Color4F(0,0,0,1));
	effect->setEndColor(getColor4F());
	effect->setEndColorVar(Color4F(0,0,0,1));
	effect->setStartSize(20.0f);	
	effect->setGravity(Point(0,-400));
	effect->setDuration(0.2f);
	effect->setLife(0.9f);
	effect->setSpeed(100.0f);
	effect->setSpeedVar(10);
	effect->setPosition(position.x+60,position.y+100);
	//effect->setAnchorPoint(Vec2(0.5,0.5));
	log("getPosition %f , %f", effect->getPosition().x, effect->getPosition().y);
	node->addChild(effect,100);
	log("node getPosition %f , %f", node->getPosition().x, node->getPosition().y);
}
Color4F getColor4F()
{
	return Color4F(1.0,1.0,1.0,0.0);
}
