#ifndef __TKP_TMX_MAP_HELPER_H__
#define __TKP_TMX_MAP_HELPER_H__

#include "cocos2d.h"
#include "Math/Polygon.h"

class TmxMapHelper
{
public:

	static void objectToVertices(int mapHeihgt, int groupHeight, 
		cocos2d::ValueMap &object, std::vector<float> &vertices);
};



#endif // __TKP_TMX_MAP_HELPER_H__