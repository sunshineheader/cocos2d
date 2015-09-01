#include "ImageInfoUtil.h"
#include "json/document.h"
#include "json/rapidjson.h"
#define RETURN_IF(cond)           if((cond)) return

ImageInfoUtil* ImageInfoUtil::m_instance = nullptr;

ImageInfoUtil::ImageInfoUtil(){
	init();
}

ImageInfoUtil::~ImageInfoUtil(){
	CC_SAFE_DELETE(m_instance);
}


ImageInfoUtil* ImageInfoUtil::getInstance(){
	if(m_instance == nullptr){
		m_instance = new ImageInfoUtil();
	}
	return m_instance;
}


void ImageInfoUtil::init(){
	string jsonStr = FileUtils::getInstance()->getStringFromFile("json/imageInfo.json");
	rapidjson::Document _mDoc;
	string mstr = jsonStr;
	RETURN_IF(NULL==mstr.c_str()||!mstr.compare(""));
	_mDoc.Parse<0>(mstr.c_str());
	RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
	const rapidjson::Value &pArr = _mDoc["image"];
	CCLOG("image size = %d",pArr.Capacity());
	for(int i=0;i<pArr.Capacity();++i){
		ImageInfo info;
		const rapidjson::Value &temp = pArr[i];
		int key = temp["id"].GetInt();
		info.id = key;
		info.image_name=temp["name"].GetString();
		info.special = temp["special"].GetInt();
		infoMap.insert(make_pair(key,info));
	}
	return;
}

ImageInfo ImageInfoUtil::getInfoById(int id){
	auto it = infoMap.find(id);
	CCASSERT(it!=infoMap.end(),"can't get image info of the id");
	return it->second;
}


