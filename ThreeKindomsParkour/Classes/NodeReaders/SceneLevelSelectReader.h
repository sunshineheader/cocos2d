#ifndef __TKP_SCENE_LEVEL_SELECT_READER_H__
#define __TKP_SCENE_LEVEL_SELECT_READER_H__

#include "cocos2d.h"
#include "cocostudio\CocosStudioExport.h"
#include "cocostudio\WidgetReader\NodeReader\NodeReader.h"

class SceneLevelSelectReader : public cocostudio::NodeReader
{
public:
	static SceneLevelSelectReader* getInstance();
	static void purge();
	cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions);


};

#endif // __TKP_SCENE_LEVEL_SELECT_READER_H__