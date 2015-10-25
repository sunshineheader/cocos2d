#include "GameStartLayer.h"
USING_NS_CC;

bool GameStart::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	addBackgroundSprite();
	showParticleSnow();
	addPauseGameButton();
	showCurrcertSorceSprite();
	addTitleSprite();
	addHistorySorceShow();
	addMusicuButton();
	addShoppingButton();
	initAminationTexture();
	startGameButton = getStartGameButton();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameStart::onTouchBegan,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, startGameButton);
	return true;
}

void GameStart::addBackgroundSprite()
{
	auto backgroundSprite = Sprite::create("beijing.png");
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(backgroundSprite,-1);
}
void GameStart::showParticleSnow()
{
	ParticleSnow* effect = ParticleSnow::create();
	effect->setTotalParticles(100);
	addChild(effect);
}
void GameStart::addPauseGameButton()
{
	MenuItemImage * pauseGameButton = MenuItemImage::create("anniu_zt.png", "anniu_zt.png", CC_CALLBACK_0(GameStart::pauseGameCallback, this));
	Menu * pauseGameMenu = Menu::create(pauseGameButton, nullptr);
	pauseGameMenu->setPosition(Vec2(visibleSize.width / 2 - 200, visibleSize.height / 2 + 330));
	addChild(pauseGameMenu);
}
void GameStart::pauseGameCallback()
{
	startGameButton->stopAllActions();
	addChild(GamePause::create());
}
void GameStart::showCurrcertSorceSprite()
{
	auto sorcce = Sprite::create("yx_defen.png");
	sorcce->setPosition(Vec2(visibleSize.width / 2 + 120, visibleSize.height / 2 + 330));
	addChild(sorcce);
	showCurrcertSorceNumber();
}
void GameStart::showCurrcertSorceNumber()
{
	// GameData
	int currcertSorce = GameData::getInstance()->getCurrcertSorce();
	LabelAtlas * CurrcertSorce = LabelAtlas::create(String::createWithFormat("%d", currcertSorce)->_string, "yx_shuzi.png", 18, 24, 48);
	CurrcertSorce->setAnchorPoint(Vec2(0.0, 0.5));
	CurrcertSorce->setPosition(Vec2(visibleSize.width / 2 + 120, visibleSize.height / 2 + 330));
	addChild(CurrcertSorce);
}
void GameStart::addTitleSprite()
{
	auto title = Sprite::create("biaoti.png");
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2+200));
	addChild(title);
}
void GameStart::addHistorySorceShow()
{
	auto history = Sprite::create("js_lishi.png");
	history->setPosition(Vec2(visibleSize.width / 2 - 50, visibleSize.height / 2 - 150));
	addChild(history);
	showHistorySorceNumber();
}
void GameStart::showHistorySorceNumber()
{
	// Game Data
	int sorceNumber = 100;
	LabelAtlas * labelNumber = LabelAtlas::create(String::createWithFormat("%d",sorceNumber)->_string,"fh_shuzi.png",22,32,48);
	labelNumber->setAnchorPoint(Vec2(0.0, 0.5));
	labelNumber->setPosition(Vec2(visibleSize.width / 2 + 50, visibleSize.height / 2 - 150));
	addChild(labelNumber);
}
void GameStart::addMusicuButton()
{
	MenuItemImage * musicButtonOn = MenuItemImage::create("anniu_shengyin1.png","anniu_shengyin2.png");
	MenuItemImage * musicButtonOff = MenuItemImage::create("anniu_shengyin2.png", "anniu_shengyin1.png");
	MenuItemToggle* musicButtonToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_0(GameStart::musicPlayCallback,this), musicButtonOn, musicButtonOff, nullptr);
	Menu * musicEffectMenu = Menu::create(musicButtonToggle,nullptr);
	musicEffectMenu->setPosition(Vec2(visibleSize.width / 2 - 150, visibleSize.height / 2 - 300));
	addChild(musicEffectMenu);
}
void GameStart::musicPlayCallback()
{

}

void GameStart::addShoppingButton()
{
	MenuItemImage *shoppingGame = MenuItemImage::create("anniu_sc.png", "anniu_sc.png",CC_CALLBACK_0(GameStart::shoppingButtonCallback,this));
	Menu * shoppingMenu = Menu::create(shoppingGame, nullptr);
	shoppingMenu->setPosition(Vec2(visibleSize.width / 2 + 150, visibleSize.height / 2 - 300));
	addChild(shoppingMenu);
}
void GameStart::shoppingButtonCallback()
{
	addChild(GameShopLayer::create());
}
cocos2d::Sprite * GameStart::getStartGameButton()
{
	auto startGameButton = Sprite::create("anniu_kaishi.png");
	startGameButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(startGameButton);
	auto scaleSmall = ScaleTo::create(0.8f, 0.7f);
	auto scaleBigger = ScaleTo::create(0.8f, 1.0f);
	auto delayTime = DelayTime::create(0.0f);
	auto seqActiom = Sequence::create(scaleSmall, delayTime, scaleBigger, delayTime->clone(), nullptr);
	startGameButton->runAction(RepeatForever::create(seqActiom));
	return startGameButton;
}

bool GameStart::onTouchBegan(Touch * touch, Event *event)
{
	if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::create()));
	}
	return false;
}
void GameStart::initAminationTexture()
{
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Monster.plist", "Monster.png");
	log("initAminationTexture s");
}
