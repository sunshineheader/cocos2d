#ifndef _GUIDE_INFO_UTIL_
#define _GUIDE_INFO_UTIL_
#include "cocos2d.h"
#include "Guideinfo.h"
#include <map>

using namespace cocos2d;
using namespace std;

class GuideInfoUtil{
public:
	static GuideInfoUtil* getInstance();
	GuideInfo* getGuideInfo();
	GuideInfo* guideinfo;
private:
	void init();
	GuideInfoUtil();
	~GuideInfoUtil();
private:
	static GuideInfoUtil* m_instance;
};
#endif