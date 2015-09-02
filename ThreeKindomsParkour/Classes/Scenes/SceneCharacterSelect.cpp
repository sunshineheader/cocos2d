#include "SceneCharacterSelect.h"
#include "Utils/SceneHelper.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;


SceneCharacterSelect::SceneCharacterSelect()
{
}

SceneCharacterSelect::~SceneCharacterSelect()
{
}

bool SceneCharacterSelect::init()
{
	if (!SceneBase::init())
	{
		return false;
	}

	auto root = CSLoader::createNode("CsbRes/SceneCharacterSelect.csb");
	addChild(root);

	auto top = root->getChildByName("Container")->getChildByName("TopBar");
	auto close = dynamic_cast<Button*>(top->getChildByName("Btn_Close"));
	close->addTouchEventListener([](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->popScene();
		}
	});


	return true;
}

void SceneCharacterSelect::initAfterCreate()
{

}

void SceneCharacterSelect::initCallbackMap()
{

}

void SceneCharacterSelect::onKeyBackReleased()
{
	Director::getInstance()->popScene();
}