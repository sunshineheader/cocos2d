#ifndef GameStartLayer_H
#define GameStartLayer_H

#include "cocos2d.h"
#include "GameScene.h"
#include "GameShopLayer.h"
#include "GamePauseLayer.h"
#include "GameData.h"

class GameStart :public cocos2d::Layer {

public:
	virtual bool init();
	CREATE_FUNC(GameStart);
	void addBackgroundSprite();
	void showParticleSnow();
	void addPauseGameButton();
	void pauseGameCallback();
	void showCurrcertSorceSprite();
	void showCurrcertSorceNumber();
	void addTitleSprite();
	void addHistorySorceShow();
	void showHistorySorceNumber();
	void addMusicuButton();
	void musicPlayCallback();
	void addShoppingButton();
	void shoppingButtonCallback();
	cocos2d::Sprite * getStartGameButton();
	virtual bool onTouchBegan(cocos2d::Touch * touch ,cocos2d::Event *event);
	void initAminationTexture();

private:
	cocos2d::Sprite* startGameButton;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;





};
#endif