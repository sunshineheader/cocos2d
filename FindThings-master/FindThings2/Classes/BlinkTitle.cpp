#include "BlinkTitle.h"

BlinkTitle::BlinkTitle()
{}

BlinkTitle* BlinkTitle::create(const std::string& fileName){
	BlinkTitle* ret = new BlinkTitle();
	if(ret && ret->init(fileName)){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool BlinkTitle::init(const std::string& fileName){
	if(!Node::init())	return false;
	
	ClippingNode* cliper = ClippingNode::create();
	Sprite* content = Sprite::create(fileName);
	Sprite* stencil = content;

	Sprite* spark = Sprite::create("spark.png");
	spark->setPosition(-content->getContentSize().width/2,0);

	cliper->setAlphaThreshold(0.5f);
	cliper->setStencil(stencil);
	cliper->addChild(content);
	cliper->addChild(spark);

	this->addChild(cliper);

	MoveTo* moveTo = MoveTo::create(2.0f,Point(content->getContentSize().width,0));
	MoveTo* moveBack = MoveTo::create(2.0f,Point(-content->getContentSize().width,0));
	Sequence* seq = Sequence::create(moveTo,moveBack,NULL);
	RepeatForever* action = RepeatForever::create(seq);
	spark->runAction(action);

	return true;
}