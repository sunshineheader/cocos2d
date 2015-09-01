#include "GuideInfoUtil.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "Guideinfo.h"
#define RETURN_IF(cond)           if((cond)) return

GuideInfoUtil* GuideInfoUtil::m_instance = nullptr;

GuideInfoUtil::GuideInfoUtil(){
	init();
}

GuideInfoUtil::~GuideInfoUtil(){
	CC_SAFE_DELETE(m_instance);
}


GuideInfoUtil* GuideInfoUtil::getInstance(){
	if(m_instance == nullptr){
		m_instance = new GuideInfoUtil();
	}
	return m_instance;
}


void GuideInfoUtil::init(){
	string jsonStr = FileUtils::getInstance()->getStringFromFile("json/guideInfo.json");
	rapidjson::Document _mDoc;
	string mstr = jsonStr;
	guideinfo = new GuideInfo();
	RETURN_IF(NULL==mstr.c_str()||!mstr.compare(""));
	_mDoc.Parse<0>(mstr.c_str());
	RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
	const rapidjson::Value &temp = _mDoc["guide"];
	guideinfo->taskid = temp["taskid"].GetInt();
	if(temp["list"].IsArray()){
		auto size=temp["list"].Capacity();
		CCLOG("ids size = %d",size);
		for(int j=0;j<size;j++){
			int type = temp["list"][j]["id"].GetInt();
			guideinfo->idList.push_back(Value(type));
		}
	}
	return;
}


GuideInfo* GuideInfoUtil::getGuideInfo(){
	return guideinfo;
}