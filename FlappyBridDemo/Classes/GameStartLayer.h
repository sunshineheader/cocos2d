#pragma once
#include "cocos2d.h"
#include "Brid.h"
#include "GameScene.h"
#include "GameData.h"
#include "GamePauseLayer.h"
#include "BlinkTitle.h"
using namespace cocos2d;

class GameStart :public Layer {

public:
	static Scene * createScene();
	virtual bool init();
	void initWithTexture();
	void addBackgroundSprite();
	void addTitleSprite();
	void showParticleSnow();
	void showGoldSprite();
	void showGoldNumber();
	void addBridAimation();
	void addUIButton();
	void setMusicIndex(MenuItemToggle* toggle);
	void setSoundIndex(MenuItemToggle* toggle);
	void startGameCallBack();
	void pauseGameCallBack();
	void pauseGame();
	void introductationGameCallBack();
	void exitGameCallBack();
	void musicGameCallBack(Ref *psender);
	void soundGameCallBack(Ref *psender);
	void playerBackGroungMusic();
	void playerSoundMusic();
public:
	void addProgressTimer();
	CREATE_FUNC(GameStart);
	void upadte(float dt);
private:
	Size visibleSize;
	Vec2 origin;
};