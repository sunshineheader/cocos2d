#include "GameParticle.h"

void showGameParticleEffect(int color,Point position,Node* node){
	ParticleExplosion* effect = ParticleExplosion::create();
	effect->setTotalParticles(1000);
	effect->setStartColor(getColor4F(color));
	effect->setStartColorVar(Color4F(0,0,0,1));
	effect->setEndColor(getColor4F(color));
	effect->setEndColorVar(Color4F(0,0,0,1));
	effect->setStartSize(25.0f);	// 初始化粒子元素的尺寸
	effect->setGravity(Point(0,-400));
	effect->setDuration(0.2f);
	effect->setLife(2.0f);
	effect->setSpeed(300.0f);
	effect->setSpeedVar(10);
	effect->setPosition(position);
	node->addChild(effect);
}

Color4F getColor4F(int color){
	switch(color){
	case 0:
		return Color4F(0.74,0.30,0.99,1);
	case 1:
		return Color4F(84/255.0f,203/255.0f,254/255.0f,1);
	case 2:
		return Color4F(253/255.0f,80/255.0f,126/255.0f,1);
	case 3:
		return Color4F(253/255.0f,234/255.0f,84/255.0f,1);
	case 4:
		return Color4F(132/255.0f,226/255.0f,111/255.0f,1);
	}
	return Color4F(1,1,1,0);
}
