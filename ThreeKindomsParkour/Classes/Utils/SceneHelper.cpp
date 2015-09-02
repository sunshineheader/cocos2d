#include "SceneHelper.h"
#include "Scenes/SceneBase.h"
#include "Scenes/SceneMain.h"
#include "Scenes/SceneLevelSelect.h"
#include "Scenes/SceneCharacterSelect.h"
#include "Scenes/ScenePropSelect.h"
#include "Scenes/SceneLoading.h"
#include "Scenes/SceneGame.h"
#include "Scenes/SceneSettlement.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;

const int kSceneCount = 7;


static SceneType s_startScene = SceneType::Main;
static SceneType s_previousScene = s_startScene;
static SceneType s_currentScene = s_startScene;

SceneBase* SceneHelper::createStartScene()
{
	return createScene(s_startScene);
}

void SceneHelper::gotoMainScene()
{
	s_previousScene = s_currentScene;
	auto scene = createScene(SceneType::Main);
	Director::getInstance()->replaceScene(scene);
	s_currentScene = SceneType::Main;
}

void SceneHelper::gotoLevelSelectScene()
{
	s_previousScene = s_currentScene;
	auto scene = createScene(SceneType::LevelSelect);
	Director::getInstance()->replaceScene(scene);
	s_currentScene = SceneType::LevelSelect;
}

void SceneHelper::gotoCharacterSelectScene()
{
	s_previousScene = s_currentScene;
	auto scene = createScene(SceneType::CharacterSelect);
	Director::getInstance()->replaceScene(scene);
	s_currentScene = SceneType::CharacterSelect;
}

void SceneHelper::gotoPropSelectScene()
{
	s_previousScene = s_currentScene;
	auto scene = createScene(SceneType::PropSelect);
	Director::getInstance()->replaceScene(scene);
	s_currentScene = SceneType::PropSelect;
}

void SceneHelper::gotoLoadingScene()
{
	s_previousScene = s_currentScene;
	auto scene = createScene(SceneType::Main);
	Director::getInstance()->replaceScene(scene);
	s_currentScene = SceneType::Main;
}

void SceneHelper::gotoGameScene()
{
	s_previousScene = s_currentScene;
	auto scene = createScene(SceneType::Game);
	Director::getInstance()->replaceScene(scene);
	s_currentScene = SceneType::Game;
}

void SceneHelper::gotoSettlementScene()
{
	s_previousScene = s_currentScene;
	auto scene = createScene(SceneType::Settlement);
	Director::getInstance()->replaceScene(scene);
	s_currentScene = SceneType::Settlement;
}

void SceneHelper::gotoPreviousScene()
{
	
}

SceneBase* SceneHelper::createScene(SceneType type)
{
	SceneBase *scene = nullptr;
	switch (type)
	{
	case SceneType::Main:
		scene = createScene("CsbRes/SceneMain.csb");	
		break;

	case SceneType::LevelSelect:
		scene = createScene("CsbRes/SceneLevelSelect.csb");	
		break;

	case SceneType::CharacterSelect:
		scene = SceneCharacterSelect::create();			
		break;

	case SceneType::PropSelect:
		scene = ScenePropSelect::create();
		break;

	case SceneType::Loading:
		scene = SceneLoading::create();
		break;

	case SceneType::Game:
		scene = createScene("CsbRes/SceneGame.csb");
		break;

	case SceneType::Settlement:
		scene = SceneSettlement::create();
		break;

	default:
		break;
	}

	setAllButtonsPressedAtionEnabled(scene, -0.05f);

	return scene;
}

SceneBase* SceneHelper::createScene(const string &filename)
{
	auto node = CSLoader::createNode(filename);
	auto scene = dynamic_cast<SceneBase*>(node);
	scene->initAfterCreate();
	
	return scene;
}

void SceneHelper::setAllButtonsPressedAtionEnabled(Node *root, float zoomScale)
{
	if (root == nullptr)
		return;

	auto button = dynamic_cast<Button*>(root);
	if (button != nullptr)
	{
		button->setZoomScale(zoomScale);
		button->setPressedActionEnabled(true);
	}

	for (auto node : root->getChildren())
	{
		SceneHelper::setAllButtonsPressedAtionEnabled(node, zoomScale);
	}
}