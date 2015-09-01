#ifndef _IMAGE_INFO_UTIL_
#define _IMAGE_INFO_UTIL_
#include "ImageInfo.h"
#include "cocos2d.h"
#include <map>
using namespace cocos2d;
class ImageInfoUtil{
public:
	static ImageInfoUtil* getInstance();
	ImageInfo getInfoById(int id);
private:
	void init();
	ImageInfoUtil();
	~ImageInfoUtil();
private:
	static ImageInfoUtil* m_instance;
	std::map<int,ImageInfo> infoMap;

};
#endif