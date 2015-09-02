#ifndef __TKP_USER_DATA_H__
#define __TKP_USER_DATA_H__

#include "Scenes/SceneGame.h"

#include "cocos2d.h"

class UserData
{
public:
	static UserData* getInstance();

	void reloadData();
	void saveData();

	bool isAudioOn() const;
	void setAudioOn(bool isAudioOn);

	void setCurrentLevel(int index);
	void addOneLevel();
	int getCurrentLevel() const;


	void setGameMode(SceneGame::GameMode gameMode);
	SceneGame::GameMode getGameMode() const;

protected:
	UserData();
	~UserData();
	CC_DISALLOW_COPY_AND_ASSIGN(UserData);

private:
	bool _isAudioOn;
	int _currentLevel;

	SceneGame::GameMode _gameMode;
};

#endif // __USER_DATA_H__