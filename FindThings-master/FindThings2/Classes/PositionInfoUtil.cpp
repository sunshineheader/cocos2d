#include "PositionInfoUtil.h"
#include "json/document.h"
#include "json/rapidjson.h"
#define RETURN_IF(cond)           if((cond)) return

PositionInfoUtil* PositionInfoUtil::m_instance = nullptr;

PositionInfoUtil::PositionInfoUtil(){
	init();
}

PositionInfoUtil::~PositionInfoUtil(){
	CC_SAFE_DELETE(m_instance);
}


PositionInfoUtil* PositionInfoUtil::getInstance(){
	if(m_instance == nullptr){
		m_instance = new PositionInfoUtil();
	}
	return m_instance;
}


void PositionInfoUtil::init(){
	string jsonStr = FileUtils::getInstance()->getStringFromFile("json/positionInfo.json");
	rapidjson::Document _mDoc;
	string mstr = jsonStr;
	RETURN_IF(NULL==mstr.c_str()||!mstr.compare(""));
	_mDoc.Parse<0>(mstr.c_str());
	RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
	const rapidjson::Value &pArr = _mDoc["position"];
	CCLOG("task object size = %d",pArr.Capacity());
	for(int i=0;i<pArr.Capacity();++i){
		const rapidjson::Value &temp = pArr[i];
		int key = temp["id"].GetInt();
		auto x = temp["x"].GetInt();
		auto y = temp["y"].GetInt();
		Point* pos = new Point(x,y);
		posMap.insert(make_pair(key,pos));
	}
	return;
}

Point* PositionInfoUtil::getPositionById(int id){
    auto it = posMap.find(id);
	CCASSERT(it!=posMap.end(),"can't get pos info of the id");
	return it->second;
}


std::map<int,Point*> PositionInfoUtil::getPositionList(){
	return posMap;
}