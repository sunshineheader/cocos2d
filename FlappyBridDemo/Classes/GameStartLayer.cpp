#include "GameStartLayer.h"
#include "GameAudio.h"
Scene* GameStart::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = GameStart::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameStart::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//FileUtils::getInstance()->removeFile(UserDefault::getInstance()->getXMLFilePath());
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
	scheduleUpdate();
	initWithTexture();
	addBackgroundSprite();
	addTitleSprite();
	showParticleSnow();
	showGoldSprite();
	addBridAimation();
	addUIButton();
	addProgressTimer();
	playerBackGroungMusic();
	//playerSoundMusic();
	// ÕìÌý¼üÅÌÊÂ¼þ
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			Director::getInstance()->end();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			Director::getInstance()->end();
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
void GameStart::initWithTexture()
{
	auto frameCache=SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("Brid.plist", "Brid.png");
	//frameCache->addSpriteFramesWithFile("GameObject.plist", "GameObject.png");
}
void GameStart::addBackgroundSprite()
{
	auto backgroundSprite = Sprite::create("background.png");
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(backgroundSprite, -1);
}
void GameStart::addTitleSprite()
{
	BlinkTitle * title = BlinkTitle::create("title.png");
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2+150));
	addChild(title);
}
void GameStart::showParticleSnow()
{
	ParticleSnow * snow = ParticleSnow::createWithTotalParticles(100);
	snow->setSpeed(10);
	snow->setSpeedVar(5);
	addChild(snow);
}
void GameStart::showGoldSprite()
{
	auto goldSprite = Sprite::create("gold.png");
	goldSprite->setPosition(Vec2(visibleSize.width / 2 + 135, visibleSize.height / 2 + 290));
	addChild(goldSprite);
	showGoldNumber();
}
void GameStart::showGoldNumber()
{
	//Game Data
	GameData::getInstance()->setCurrcertSource(0);
	int gpldNumber = GameData::getInstance()->getCurrcertSource();
	LabelAtlas * gold = LabelAtlas::create(String::createWithFormat("%d", gpldNumber)->_string, "balck.png",19,38,48);
	gold->setAnchorPoint(Vec2(0.0f, 0.0f));
	gold->setPosition(Vec2(visibleSize.width / 2 + 135, visibleSize.height / 2 + 272));
	addChild(gold);
}
void GameStart::addBridAimation()
{
	Brid *brid = Brid::create();
	brid->setPosition(Vec2(visibleSize.width / 2-110, visibleSize.height / 2 + 180));
	//brid->initBridAmination();
	addChild(brid);
	auto scaleSmall = ScaleTo::create(0.8f,0.8f);
	auto scaleBigger = ScaleTo::create(0.8f, 1.2f);
	auto delay = DelayTime::create(0.0f);
	auto squence = Sequence::create(scaleSmall, delay, scaleBigger, delay->clone(), nullptr);
	brid->runAction(RepeatForever::create(squence));
}
void GameStart::addUIButton()
{
	// ÔÝÍ£ÓÎÏ·
	auto pauseGameButton = MenuItemImage::create("btnPause.png", "btnPause_active.png", CC_CALLBACK_0(GameStart::pauseGameCallBack, this));
	pauseGameButton->setPosition(visibleSize.width / 2 - 170, visibleSize.height / 2 + 290);
	// ¿ªÊ¼ÓÎÏ·
	auto startGameButton = MenuItemImage::create("start_normal.png", "start_selected.png", CC_CALLBACK_0(GameStart::startGameCallBack, this));
	startGameButton->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	// ÓÎÏ·½éÉÜ
	auto introductationGameButton = MenuItemImage::create("introuction_normal.png", "introuction_selected.png", CC_CALLBACK_0(GameStart::introductationGameCallBack, this));
	introductationGameButton->setPosition(visibleSize.width / 2, visibleSize.height / 2-100);
	// ÍË³öÓÎÏ·
	auto exitGameButton = MenuItemImage::create("exit_normal.png", "exit_select.png", CC_CALLBACK_0(GameStart::exitGameCallBack, this));
	exitGameButton->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);
	// ÒôÀÖ
	MenuItemImage* musicOn = MenuItemImage::create("btnMusic.png", "btnMusic_off_active.png");
	MenuItemImage* musicOff = MenuItemImage::create("btnMusic_off_active.png", "btnMusic.png");
	MenuItemToggle* musicToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameStart::musicGameCallBack, this), musicOn, musicOff,nullptr);
	musicToggle->setScale(0.6f, 0.6f);
	setMusicIndex(musicToggle);
	musicToggle->setPosition(visibleSize.width / 2 - 165, visibleSize.height / 2 - 280);
	// ÒôÐ§
	MenuItemImage* soundOn = MenuItemImage::create("btnSound.png", "btnSound_off_active.png");
	MenuItemImage* soundOff = MenuItemImage::create("btnSound_off_active.png", "btnSound.png");
	MenuItemToggle* soundToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameStart::soundGameCallBack, this), soundOn, soundOff, nullptr);
	soundToggle->setScale(0.6f, 0.6f);
	//setSoundIndex(soundToggle);
	soundToggle->setPosition(visibleSize.width / 2 + 165, visibleSize.height / 2 - 280);

	auto gameMenu = Menu::create(pauseGameButton, startGameButton, introductationGameButton, exitGameButton, musicToggle, soundToggle, nullptr);
	gameMenu->setPosition(Vec2::ZERO);
	addChild(gameMenu);

}

void GameStart::setMusicIndex(MenuItemToggle* toggle)
{
	bool state = UserDefault::getInstance()->getBoolForKey("MusicState");
	if (state == true)
	{
		toggle->setSelectedIndex(0);
	}
	else
	{
		toggle->setSelectedIndex(1);
	}
}
void GameStart::setSoundIndex(MenuItemToggle* toggle)
{
	bool state = UserDefault::getInstance()->getBoolForKey("SoundState");
	if (state == true)
	{
		toggle->setSelectedIndex(0);
	}
	else
	{
		toggle->setSelectedIndex(1);
	}
}

void GameStart::startGameCallBack()
{
	auto scene = GameScene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -98.0f));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = GameLayer::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}
void GameStart::pauseGameCallBack()
{
	pauseGame();
	//GameStart::pause();
}
void GameStart::pauseGame()
{
	addChild(GamePauseLayer::create());
	Director::getInstance()->pause();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this, true);
}
void GameStart::introductationGameCallBack()
{
}

void GameStart::exitGameCallBack()
{
	Director::getInstance()->end();
}

void GameStart::musicGameCallBack(Ref *psender)
{
	MenuItemToggle *music = (MenuItemToggle*)psender;
	if (music->getSelectedIndex() == 0)
	{
		GameAudio::getInstance()->playBackgroundMusic();
		GameData::getInstance()->setMusicState(true);
		GameData::getInstance()->SaveMusicState();
	}
	else
	{
		GameAudio::getInstance()->stopBackgroundMusic();
		GameData::getInstance()->setMusicState(false);
		GameData::getInstance()->SaveMusicState();
	}
}
void GameStart::soundGameCallBack(Ref* psender)
{
	MenuItemToggle *sound = (MenuItemToggle*)psender;
	if (sound->getSelectedIndex() == 0)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
		GameData::getInstance()->setSoundState(true);
		GameData::getInstance()->SaveSoundState();
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		GameData::getInstance()->setSoundState(false);
		GameData::getInstance()->SaveSoundState();
	}
}
void GameStart::playerBackGroungMusic()
{
	//GameData::getInstance()->setMusicState(true);
	bool state=UserDefault::getInstance()->getBoolForKey("MusicState");
	if (state == true)
	{
		GameAudio::getInstance()->playBackgroundMusic();
	}
	else
	{
		GameAudio::getInstance()->stopBackgroundMusic();
	}

}
void GameStart::playerSoundMusic()
{
	bool state = UserDefault::getInstance()->getBoolForKey("SoundState");
	if (state == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	}

}
void GameStart::addProgressTimer()
{
	auto progressTimerBg = Sprite::create("progress_bg.png");
	progressTimerBg->setPosition(visibleSize.width / 2 , visibleSize.height / 2 + 185);
	addChild(progressTimerBg);
	auto progressTimerUp = Sprite::create("progress.png");
	ProgressTimer * progroessTimer = ProgressTimer::create(progressTimerUp);
	progroessTimer->setType(ProgressTimerType::BAR);
	progroessTimer->setMidpoint(Vec2(0, 0));
	progroessTimer->setBarChangeRate(Vec2(1, 0));
	progroessTimer->setPosition(visibleSize.width / 2 , visibleSize.height / 2 + 185);
	addChild(progroessTimer);
	progroessTimer->setPercentage(20.0f);
}
void GameStart::upadte(float dt)
{
}
