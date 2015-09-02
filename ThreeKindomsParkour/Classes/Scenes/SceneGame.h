#ifndef __TKP_SCENE_GAME_H__
#define __TKP_SCENE_GAME_H__

#include "SceneBase.h"
#include "Game/Quests/Quest.h"
#include "cocos2d.h"

class GameMap;

class SceneGame : public SceneBase
{
public:
    enum class GameState {
        Running,
        Paused,
        QuestCompleted,
        GameOver ,
        GameFinished
    };

	enum class GameMode {
		StageMode,
		ClassicMode
	};

public:
	CREATE_FUNC(SceneGame);

	virtual void update(float delta) override;
	virtual void initAfterCreate() override;

	GameMap* getGameMap() const;

protected:
	SceneGame();
	~SceneGame();
	CC_DISALLOW_COPY_AND_ASSIGN(SceneGame);

	virtual bool init() override;
	virtual void initCallbackMap() override;
	virtual void onKeyBackReleased() override;

protected:
	void onShowPauseDialog(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void onBackHome(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onAudioOff(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onAudioOn(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onContinue(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

	void onExitConfirm(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void onExitCancel(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);

private:
	void createWorld();
	void createQuest();
	void initGui();
	void setAudioOn(bool isAudioOn);

	Quest* createCollectionQuest();

    void updateGui();
	void updateScore();
	void updateQuestStats();
	void updateFeverState();

    void checkQuestCompleted();
    void checkGameOver();
    void checkGameFinished();

    void pauseGame();
    void resumeGame();

private:
	GameMap *_gameMap;
    GameState _gameState;
	Quest *_quest;
};



#endif // __TKP_SCENE_GAME_H__