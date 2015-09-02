#include "RapidJsonHelper.h"

#include "json/document.h"
#include "json/rapidjson.h"

USING_NS_CC;
using namespace std;

void RapidJsonHelper::parsePropertiesFromFile(const string &filepath, ValueMap &properties)
{
	auto content = FileUtils::getInstance()->getStringFromFile(filepath);
	rapidjson::Document doc;
	doc.Parse<0>(content.c_str());

	if (doc.HasParseError())
	{
		CCLOG("<RapidJsonHelper>: PARSE %s ERROR!", filepath.c_str());
		return;
	}
}