#include "SceneLevelSelectReader.h"
#include "Scenes/SceneLevelSelect.h"

static SceneLevelSelectReader *_instance = nullptr;

SceneLevelSelectReader* SceneLevelSelectReader::getInstance()
{
	if (!_instance) {
		_instance = new SceneLevelSelectReader();
	}
	return _instance;
}

void SceneLevelSelectReader::purge()
{
	CC_SAFE_DELETE(_instance);
}

cocos2d::Node* SceneLevelSelectReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
	SceneLevelSelect *node = SceneLevelSelect::create();
	setPropsWithFlatBuffers(node, nodeOptions);
	return node;
}