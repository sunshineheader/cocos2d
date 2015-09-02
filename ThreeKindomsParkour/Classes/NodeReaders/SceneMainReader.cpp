#include "SceneMainReader.h"
#include "Scenes/SceneMain.h"

static SceneMainReader *_instance = nullptr;

SceneMainReader* SceneMainReader::getInstance()
{
	if (!_instance) {
		_instance = new SceneMainReader();
	}
	return _instance;
}

void SceneMainReader::purge()
{
	CC_SAFE_DELETE(_instance);
}

cocos2d::Node* SceneMainReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
	SceneMain *node = SceneMain::create();
	setPropsWithFlatBuffers(node, nodeOptions);
	return node;
}