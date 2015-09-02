#include "SceneGameReader.h"
#include "Scenes/SceneGame.h"

static SceneGameReader *_instance = nullptr;

SceneGameReader* SceneGameReader::getInstance()
{
	if (!_instance) {
		_instance = new SceneGameReader();
	}
	return _instance;
}

void SceneGameReader::purge()
{
	CC_SAFE_DELETE(_instance);
}

cocos2d::Node* SceneGameReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
	SceneGame *node = SceneGame::create();
	setPropsWithFlatBuffers(node, nodeOptions);
	return node;
}