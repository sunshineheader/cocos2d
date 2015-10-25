#include "GameScrollView.h"
#include "ui\UIScrollView.h"
#include "ui\UIButton.h"
#include "ui\UIImageView.h"
using namespace ui;
Scene* GameScrollView::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScrollView::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool GameScrollView::init()
{
	if (!Layer::init())
	{
		return false;
	}


	return true;
}