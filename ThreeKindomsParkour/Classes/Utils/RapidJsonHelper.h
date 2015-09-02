#ifndef __TKP_RAPID_JSON_HELPER_H__
#define __TKP_RAPID_JSON_HELPER_H__

#include "cocos2d.h"

class RapidJsonHelper
{
public:
	static void parsePropertiesFromFile(const std::string &filepath, cocos2d::ValueMap &properties);

};

#endif // __TKP_RAPID_JSON_HELPER_H__