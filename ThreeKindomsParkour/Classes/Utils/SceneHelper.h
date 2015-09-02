#ifndef __TKP_SCENE_HELPER_H__
#define __TKP_SCENE_HELPER_H__

#include "cocos2d.h"
#include <string>

class SceneBase;

extern const int kSceneCount;

enum class SceneType 
{
	Main,
	LevelSelect,
	CharacterSelect,
	PropSelect,
	Loading,
	Game,
	Settlement
};

class SceneHelper
{
public:
	static SceneBase* createStartScene();

	static void gotoMainScene();
	static void gotoLevelSelectScene();
	static void gotoCharacterSelectScene();
	static void gotoPropSelectScene();
	static void gotoLoadingScene();
	static void gotoGameScene();
	static void gotoSettlementScene();

	static void gotoPreviousScene();

	static SceneBase* createScene(SceneType type);

private:

	static SceneBase* createScene(const std::string &filename);
	static void setAllButtonsPressedAtionEnabled(cocos2d::Node *root, float zoomScale);
};
#endif // __TKP_SCENE_HELPER_H__