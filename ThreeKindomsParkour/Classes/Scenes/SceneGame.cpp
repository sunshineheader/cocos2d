#include "SceneGame.h"
#include "SceneSettlement.h"
#include "SceneLevelSelect.h"
#include "Utils/SceneHelper.h"
#include "Utils/UserData.h"
#include "Utils/Properties.h"
#include "Game/GameMap.h"

#include "Game/Quests/CollectionQuest.h"
#include "Game/Quests/EndlessQuest.h"
#include "Game/Quests/KillQuest.h"
#include "Game/Quests/RacingQuest.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;


SceneGame::SceneGame()
: _gameState(GameState::Running)

, _quest(nullptr)
{
}

SceneGame::~SceneGame()
{
	CC_SAFE_DELETE(_quest);
}

bool SceneGame::init()
{
	if (!SceneBase::init())
	{
		return false;
	}

	scheduleUpdate();

	return true;
}

void SceneGame::initAfterCreate()
{
	createQuest();
	createWorld();
	initGui();
}

void SceneGame::initCallbackMap()
{
	registerCallback("onShowPauseDialog", CC_CALLBACK_2(SceneGame::onShowPauseDialog, this));

	registerCallback("onBackHome", CC_CALLBACK_2(SceneGame::onBackHome, this));
	registerCallback("onAudioOff", CC_CALLBACK_2(SceneGame::onAudioOff, this));
	registerCallback("onAudioOn", CC_CALLBACK_2(SceneGame::onAudioOn, this));
	registerCallback("onContinue", CC_CALLBACK_2(SceneGame::onContinue, this));

	registerCallback("onExitConfirm", CC_CALLBACK_2(SceneGame::onExitConfirm, this));
	registerCallback("onExitCancel", CC_CALLBACK_2(SceneGame::onExitCancel, this));
}

void SceneGame::onKeyBackReleased()
{
	auto gui = getChildByName("GUI");
	auto exitDialog = gui->getChildByName("ExitDialog");
	
	if (exitDialog->isVisible())
	{
		onExitCancel(nullptr, Widget::TouchEventType::ENDED);
		return;
	}

	auto pauseDialog = gui->getChildByName("PauseDialog");
	if (pauseDialog->isVisible())
	{
		onContinue(nullptr, Widget::TouchEventType::ENDED);
	}
	else
	{
		onShowPauseDialog(nullptr, Widget::TouchEventType::ENDED);
	}
}

void SceneGame::update(float delta)
{
    updateGui();

    checkQuestCompleted();

    checkGameOver();

    checkGameFinished();
}

void SceneGame::onShowPauseDialog(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	auto pauseDialog = getChildByName("GUI")->getChildByName("PauseDialog");
	auto pauseButton = getChildByName("GUI")->getChildByName("Btn_Pause");
	pauseDialog->runAction(Sequence::createWithTwoActions(Show::create(), FadeIn::create(0.35f)));
	pauseButton->runAction(FadeOut::create(0.25f));

    pauseGame();
}

void SceneGame::onBackHome(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	auto exitDialog = getChildByName("GUI")->getChildByName("ExitDialog");
	exitDialog->runAction(Sequence::createWithTwoActions(Show::create(), FadeIn::create(0.35f)));
}

void SceneGame::onAudioOff(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	UserData::getInstance()->setAudioOn(true);
	setAudioOn(true);
}

void SceneGame::onAudioOn(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	UserData::getInstance()->setAudioOn(false);
	setAudioOn(false);
}

void SceneGame::onContinue(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	auto pauseDialog = getChildByName("GUI")->getChildByName("PauseDialog");
	auto pauseButton = getChildByName("GUI")->getChildByName("Btn_Pause");
	pauseDialog->runAction(Sequence::createWithTwoActions(FadeOut::create(0.35f), Hide::create()));
	pauseButton->runAction(FadeIn::create(0.25f));

    resumeGame();
}

void SceneGame::onExitConfirm(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	Director::getInstance()->replaceScene(SceneHelper::createScene(SceneType::Main));
}

void SceneGame::onExitCancel(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
{
	auto exitDialog = getChildByName("GUI")->getChildByName("ExitDialog");
	exitDialog->runAction(Sequence::createWithTwoActions(FadeOut::create(0.35f), Hide::create()));
}

void SceneGame::setAudioOn(bool isAudioOn)
{
	auto pauseDialog = getChildByName("GUI")->getChildByName("PauseDialog");
	auto audioOn = pauseDialog->getChildByName("Btn_AudioOn");
	auto audioOff = pauseDialog->getChildByName("Btn_AudioOff");
	audioOn->setVisible(isAudioOn);
	audioOff->setVisible(!isAudioOn);
}

void SceneGame::createWorld()
{
	_gameMap = GameMap::create();
	getChildByName("World")->addChild(_gameMap);
}

void SceneGame::createQuest()
{
	if (UserData::getInstance()->getGameMode() == GameMode::StageMode)
	{
		_quest = createCollectionQuest();
	}
	else
	{
		_quest = new EndlessQuest;
	}

	_quest->init(this);
}

Quest* SceneGame::createCollectionQuest()
{
	Properties data("Data/Quest.json");

	Quest *quest = nullptr;
	auto level = UserData::getInstance()->getCurrentLevel();

	if (level > 17)
	{
		level = 1;
		UserData::getInstance()->setCurrentLevel(1);
	}

	if (level == 1)
	{
		int num = 10;
		auto newQuest = new CollectionQuest;
		newQuest->setIconName("Icons/Coin.png");
		auto questName = String::createWithFormat(data.getStringForKey("ScoreItem_SmallCoin").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setCollectedTypeName("ScoreItem_SmallCoin");
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 2)
	{
		int num = 1;
		auto newQuest = new CollectionQuest;
		newQuest->setIconName("Icons/Prop_CiTie.png");
		auto questName = String::createWithFormat(data.getStringForKey("PropItem_CiTie").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setCollectedTypeName("PropItem_CiTie");
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 3)
	{
		int num = 1;
		auto newQuest = new CollectionQuest;
		newQuest->setIconName("Icons/Prop_BaGuaDun.png");
		auto questName = String::createWithFormat(data.getStringForKey("PropItem_BaGuaDun").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setCollectedTypeName("PropItem_BaGuaDun");
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 4)
	{
		int num = 1;
		auto newQuest = new CollectionQuest;
		newQuest->setIconName("Icons/Prop_FeiNiao.png");
		auto questName = String::createWithFormat(data.getStringForKey("PropItem_FeiNiao").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setCollectedTypeName("PropItem_FeiNiao");
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 5)
	{
		int num = 1;
		auto newQuest = new CollectionQuest;
		newQuest->setIconName("Icons/Prop_FeiXingGuai.png");
		auto questName = String::createWithFormat(data.getStringForKey("PropItem_FeiXingGuai").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setCollectedTypeName("PropItem_FeiXingGuai");
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 6)
	{
		int num = 2;
		auto newQuest = new CollectionQuest;
		newQuest->setIconName("Icons/Prop_JiaSu.png");
		auto questName = String::createWithFormat(data.getStringForKey("PropItem_JiaSu").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setCollectedTypeName("PropItem_JiaSu");
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 7)
	{
		int num = 2000;
		auto newQuest = new RacingQuest;
		newQuest->setIconName("Icons/Diamond.png");
		auto questName = String::createWithFormat(data.getStringForKey("RacingQuest_Distance").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setRacingType(RacingQuest::RacingType::Distance);
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 8)
	{
		int num = 3000;
		auto newQuest = new RacingQuest;
		newQuest->setIconName("Icons/Diamond.png");
		auto questName = String::createWithFormat(data.getStringForKey("RacingQuest_Score").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setRacingType(RacingQuest::RacingType::Score);
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 9)
	{
		int num = 1;
		auto newQuest = new RacingQuest;
		newQuest->setIconName("Icons/Diamond.png");
		auto questName = String::createWithFormat(data.getStringForKey("RacingQuest_Fever").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setRacingType(RacingQuest::RacingType::Fever);
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 10)
	{
		int num = 20;
		auto newQuest = new RacingQuest;
		newQuest->setIconName("Icons/Diamond.png");
		auto questName = String::createWithFormat(data.getStringForKey("RacingQuest_DoubleJump").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setRacingType(RacingQuest::RacingType::DoubleJump);
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 11)
	{
		int num = 5;
		auto newQuest = new CollectionQuest;
		newQuest->setIconName("Icons/Diamond.png");
		auto questName = String::createWithFormat(data.getStringForKey("Kill_LiangChe").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setCollectedTypeName("Kill_LiangChe");
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 12)
	{
		int num = 5;
		auto newQuest = new CollectionQuest;
		newQuest->setIconName("Icons/Diamond.png");
		auto questName = String::createWithFormat(data.getStringForKey("Kill_SharpBall").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setCollectedTypeName("Kill_SharpBall");
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 13)
	{
		int num = 5;
		auto newQuest = new CollectionQuest;
		newQuest->setIconName("Icons/Diamond.png");
		auto questName = String::createWithFormat(data.getStringForKey("Kill_FireBall").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setCollectedTypeName("Kill_FireBall");
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 14)
	{
		int num = 5;
		auto newQuest = new CollectionQuest;
		newQuest->setIconName("Icons/Diamond.png");
		auto questName = String::createWithFormat(data.getStringForKey("Kill_SpearSoldier").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setCollectedTypeName("Kill_SpearSoldier");
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 15)
	{
		int num = 5;
		auto newQuest = new CollectionQuest;
		newQuest->setIconName("Icons/Diamond.png");
		auto questName = String::createWithFormat(data.getStringForKey("Kill_ShieldSoldier").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setCollectedTypeName("Kill_ShieldSoldier");
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 16)
	{
		int num = 5;
		auto newQuest = new CollectionQuest;
		newQuest->setIconName("Icons/Diamond.png");
		auto questName = String::createWithFormat(data.getStringForKey("Kill_Block").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setCollectedTypeName("Kill_Block");
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}
	else if (level == 17)
	{
		int num = 5;
		auto newQuest = new CollectionQuest;
		newQuest->setIconName("Icons/Diamond.png");
		auto questName = String::createWithFormat(data.getStringForKey("Kill_Spiling").c_str(), num)->getCString();
		newQuest->setQuestName(questName);
		newQuest->setCollectedTypeName("Kill_Spiling");
		newQuest->setTargetNumber(num);

		quest = newQuest;
	}

	return quest;
}

void SceneGame::initGui()
{
	setAudioOn(UserData::getInstance()->isAudioOn());

	auto questStats = getChildByName("GUI")->getChildByName("QuestStats");
	questStats->setVisible(UserData::getInstance()->getGameMode() == GameMode::StageMode);
}

void SceneGame::updateGui()
{
	updateScore();
	updateQuestStats();
	updateFeverState();
}

string formatScoreNumber(int value)
{
	//string result;
	//while (value > 999)
	//{
	//	result = String::createWithFormat("%d,", value % 1000)->getCString() + result;
	//	value % 1000;
	//}
	return String::createWithFormat("%d", value)->getCString();
}

void SceneGame::updateScore()
{
	auto score = getChildByName("GUI")->getChildByName("Score");
	auto number = dynamic_cast<Text*>(score->getChildByName("Number"));
	auto value = _gameMap->getScore();
	number->setString(formatScoreNumber(_gameMap->getScore()));
}

void SceneGame::updateQuestStats()
{
	if (_quest != nullptr)
	{
		_quest->update(this);
	}
}

void SceneGame::updateFeverState()
{
	auto fever = getChildByName("GUI")->getChildByName("Fever");
	auto feverProgress = dynamic_cast<LoadingBar*>(fever->getChildByName("Progress"));
	feverProgress->setPercent(_gameMap->getFeverPointsPercent());
	if (_gameMap->isInFever())
	{
		_gameMap->addNumFever();
	}
}

void SceneGame::checkQuestCompleted()
{
    if (_quest->isCompleted() && _gameState != GameState::QuestCompleted) 
	{
        _gameState = GameState::QuestCompleted;

        _gameMap->pauseMove();

		auto stats = getChildByName("GUI")->getChildByName("QuestStats");
        stats->getChildByName("Quest")->setVisible(false);
        stats->getChildByName("Completed")->setVisible(true);

        auto success = getChildByName("GUI")->getChildByName("Banner_Success");
        success->setVisible(true);
    }
}

void SceneGame::checkGameOver()
{
    if (_gameMap->isZhuGongDead() && _gameState != GameState::GameOver) {
        _gameState = GameState::GameOver;

        _gameMap->pauseMove();

        auto failure = getChildByName("GUI")->getChildByName("Banner_Failure");
        failure->setVisible(true);
    }
}

void SceneGame::checkGameFinished()
{
    if (_gameState == GameState::GameFinished)
        return;

    if (_gameState == GameState::GameOver 
        || _gameState == GameState::QuestCompleted)
    {
        _gameState = GameState::GameFinished;

        auto number = _gameMap->getScore();
        runAction(Sequence::createWithTwoActions(DelayTime::create(1.0f),
            CallFunc::create([=]()
        {
			if (_quest->isCompleted())
			{
				UserData::getInstance()->addOneLevel();
			}

            auto scene = dynamic_cast<SceneSettlement*>(SceneHelper::createScene(SceneType::Settlement));
            scene->setFinished(_gameState == GameState::QuestCompleted);
            scene->setScore(number);
            Director::getInstance()->replaceScene(scene);

			
        })));
    }
}


void SceneGame::pauseGame()
{
    _gameState = GameState::Paused;
    _gameMap->pauseMove();
}

void SceneGame::resumeGame()
{
    _gameState = GameState::Running;
    _gameMap->resumeMove();
}

GameMap* SceneGame::getGameMap() const
{
	return _gameMap;
}