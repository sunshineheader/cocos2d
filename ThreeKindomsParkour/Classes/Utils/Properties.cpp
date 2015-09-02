#include "Properties.h"
#include "RapidJsonHelper.h"

USING_NS_CC;
using namespace std;

Properties::Properties(const std::string &filepath)
{
	auto content = FileUtils::getInstance()->getStringFromFile(filepath);
	_doc.Parse<0>(content.c_str());
	if (_doc.HasParseError())
	{
		CCLOG("<RapidJsonHelper>: PARSE %s ERROR!", filepath.c_str());
	}
}

Properties::~Properties()
{
}

bool Properties::getBoolForKey(const char *key, bool defaultValue) const
{
	return _doc.HasMember(key) ? _doc[key].GetBool() : defaultValue;
}

int Properties::getIntegerForKey(const char *key, int defaultValue) const
{
	return _doc.HasMember(key) ? _doc[key].GetInt() : defaultValue;
}

double Properties::getDoubleForKey(const char *key, double defaultValue) const
{
	return _doc.HasMember(key) ? _doc[key].GetDouble() : defaultValue;
}

string Properties::getStringForKey(const char *key, const string &defaultValue) const
{
	return _doc.HasMember(key) ? _doc[key].GetString() : defaultValue;
}