#ifndef __TKP_SCENE_GAME_READER_H__
#define __TKP_SCENE_GAME_READER_H__

#include "cocos2d.h"
#include "cocostudio\CocosStudioExport.h"
#include "cocostudio\WidgetReader\NodeReader\NodeReader.h"

class SceneGameReader : public cocostudio::NodeReader
{
public:
	static SceneGameReader* getInstance();
	static void purge();
	cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions);
};

#endif // __TKP_SCENE_GAME_READER_H__