#include "ScenePropSelect.h"
#include "Utils/SceneHelper.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;


ScenePropSelect::ScenePropSelect()
{
}

ScenePropSelect::~ScenePropSelect()
{
}

bool ScenePropSelect::init()
{
	if (!SceneBase::init())
	{
		return false;
	}

	auto root = CSLoader::createNode("CsbRes/ScenePropSelect.csb");
	addChild(root);

	auto container = root->getChildByName("Container");
	auto panel = container->getChildByName("PanelBg");
	auto back = dynamic_cast<Button*>(panel->getChildByName("Btn_Back"));
	auto forward = dynamic_cast<Button*>(panel->getChildByName("Btn_Forward"));

	back->addTouchEventListener([=](Ref *sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED) {
			Director::getInstance()->replaceScene(SceneHelper::createScene(SceneType::LevelSelect));
		}
	});
	forward->addTouchEventListener([=](Ref *sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED) {
			Director::getInstance()->replaceScene(SceneHelper::createScene(SceneType::Loading));
		}
	});

	return true;
}

void ScenePropSelect::initAfterCreate()
{

}

void ScenePropSelect::initCallbackMap()
{

}

void ScenePropSelect::onKeyBackReleased()
{
	Director::getInstance()->replaceScene(SceneHelper::createScene(SceneType::LevelSelect));
}