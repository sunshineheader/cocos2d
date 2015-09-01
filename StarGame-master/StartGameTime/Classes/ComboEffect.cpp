#include "ComboEffect.h"
#include "Audio.h"
void showComboEffect(int size,Node* node){
	if(size<5)
		return;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* comboSprite;
	if(size>=9){
		Audio::getInstance()->playCombo(size);
		comboSprite = Sprite::create("combo_3.png");
	}else if(size>=7){
		Audio::getInstance()->playCombo(size);
		comboSprite = Sprite::create("combo_2.png");
	}else{
		Audio::getInstance()->playCombo(size);
		comboSprite = Sprite::create("combo_1.png");
	}

	comboSprite->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	node->addChild(comboSprite);

	Blink* blink = Blink::create(1.0f,5);
	CallFunc* remove = CallFunc::create([=](){comboSprite->removeFromParentAndCleanup(true);});
	Sequence* action = Sequence::create(blink,remove,nullptr);
	comboSprite->runAction(action);
}
