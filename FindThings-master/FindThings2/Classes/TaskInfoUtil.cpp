#include "TaskInfoUtil.h"
#include "json/document.h"
#include "json/rapidjson.h"
#define RETURN_IF(cond)           if((cond)) return

TaskInfoUtil* TaskInfoUtil::m_instance = nullptr;

TaskInfoUtil::TaskInfoUtil(){
	init();
}

TaskInfoUtil::~TaskInfoUtil(){
	CC_SAFE_DELETE(m_instance);
}


TaskInfoUtil* TaskInfoUtil::getInstance(){
	if(m_instance == nullptr){
		m_instance = new TaskInfoUtil();
	}
	return m_instance;
}


void TaskInfoUtil::init(){
	string jsonStr = FileUtils::getInstance()->getStringFromFile("json/taskInfo.json");
	rapidjson::Document _mDoc;
	string mstr = jsonStr;
	RETURN_IF(NULL==mstr.c_str()||!mstr.compare(""));
	_mDoc.Parse<0>(mstr.c_str());
	RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
	const rapidjson::Value &pArr = _mDoc["task"];
	CCLOG("task object size = %d",pArr.Capacity());
	for(int i=0;i<pArr.Capacity();++i){
		TaskInfo* info=new TaskInfo();
		const rapidjson::Value &temp = pArr[i];
		int key = temp["id"].GetInt();
		info->id = key;
		info->name=temp["name"].GetString();
		info->imageName = temp["image"].GetString();
		std::string str = temp["thingIds"].GetString();
		vector<std::string> things = split(str,",");
		//读取属性数组
		if(things.size()>0){
			for(int j=0;j<things.size();j++){
				info->thingsId.push_back(things.at(j));
			}
		}
		infoMap.insert(make_pair(key,info));
	}
	return;
}

TaskInfo* TaskInfoUtil::getTaskById(int id){
	auto it = infoMap.find(id);
	CCASSERT(it!=infoMap.end(),"can't get task info of the id");
	return it->second;
}

std::map<int,TaskInfo*> TaskInfoUtil::getAllTask(){
    return infoMap;
}


//字符串分割函数  
std::vector<std::string> TaskInfoUtil::split(std::string str,std::string pattern)  
{  
    std::string::size_type pos;  
    std::vector<std::string> result;  
    str+=pattern;//扩展字符串以方便操作  
    int size=str.size();  
  
    for(int i=0; i<size; i++)  
    {  
        pos=str.find(pattern,i);  
        if(pos<size)  
        {  
            std::string s=str.substr(i,pos-i);  
            result.push_back(s);  
            i=pos+pattern.size()-1;  
        }  
    }  
    return result;  
}  