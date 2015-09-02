#ifndef __TKP_PROPERTIES_H__
#define __TKP_PROPERTIES_H__

#include "cocos2d.h"
#include "json/document.h"
#include "json/rapidjson.h"

class Properties
{
public:
	explicit Properties(const std::string &filepath);
	~Properties();

	bool getBoolForKey(const char *key, bool defaultValue = false) const;
	int getIntegerForKey(const char *key, int defaultValue = 0) const;
	double getDoubleForKey(const char *key, double defaultValue = 0.0) const;
	std::string getStringForKey(const char *key, const std::string &defaultValue = "") const;

protected:
	CC_DISALLOW_COPY_AND_ASSIGN(Properties);

private:
	rapidjson::Document _doc;
};

#endif // __TKP_PROPERTIES_H__