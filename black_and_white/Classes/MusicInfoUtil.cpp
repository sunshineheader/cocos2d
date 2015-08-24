#include "MusicInfoUtil.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "GameDefinition.h"
#define RETURN_IF(cond)   if((cond)) return

MusicInfoUtil* MusicInfoUtil::_instance = nullptr;

MusicInfoUtil::MusicInfoUtil(){
	CCLOG("MusicInfoUtil");
	init();
}

MusicInfoUtil::~MusicInfoUtil(){
	CC_SAFE_DELETE(_instance);
}

MusicInfoUtil* MusicInfoUtil::getInstance(){
	if (_instance == nullptr){
		_instance = new MusicInfoUtil();
	}
	return _instance;
}

void MusicInfoUtil::init(){
	string musicName0 = "music/Dream Wedding.json";
	for (int j = 0; j<7;j++){
		switch (j)
		{
		case 0:
			//CCLOG("music/Dream Wedding.json");
			musicName0 = "music/Dream Wedding.json";
			break;
		case 1:
			musicName0 = "music/Edelweiss.json";
			break;
		case 2:
			musicName0 = "music/Fairy Tale.json";
			break;
		case 3:
			musicName0 = "music/For Alice.json";
			break;
		case 4:
			musicName0 = "music/Jingle Bell .json";
			break;
		case 5:
			musicName0 = "music/Merry Christmas.json";
			break;
		case 6:
			musicName0 = "music/Moon Represents My Heart.json";
			break;
		default:
			musicName0 = "music/Dream Wedding.json";
			break;
		}

		string jsonStr = FileUtils::getInstance()->getStringFromFile(musicName0);
		rapidjson::Document _mDoc;
		std::string mstr = jsonStr;
		//CCLOG(mstr.c_str());

		RETURN_IF(NULL == mstr.c_str() || !mstr.compare(""));
		_mDoc.Parse<0>(mstr.c_str());
		RETURN_IF(_mDoc.HasParseError());
		RETURN_IF(!_mDoc.IsObject());
		
		const rapidjson::Value &pArr = _mDoc["Music"];
		for (int i = 0; i<pArr.Capacity(); ++i){
			const rapidjson::Value &temp = pArr[i];
			string name= temp["value"].GetString();
			switch (j)
			{
			case 0:
				infoMap_0.insert(make_pair(i, name));
				break;
			case 1:
				infoMap_1.insert(make_pair(i, name));
				break;
			case 2:
				infoMap_2.insert(make_pair(i, name));
				break;
			case 3:
				infoMap_3.insert(make_pair(i, name));
				break;
			case 4:
				infoMap_4.insert(make_pair(i, name));
				break;
			case 5:
				infoMap_5.insert(make_pair(i, name));
				break;
			case 6:
				infoMap_6.insert(make_pair(i, name));
				break;
			default:
				break;
			}
		}
		

	}

	return;
}


map <int, string> MusicInfoUtil::getMusicInfo(int type){
	switch (type)
	{
	case 0:
		//CCLOG("return music length %d", infoMap_0.size());
		return infoMap_0;
	case 1:
		return infoMap_1;
	case 2:
		return infoMap_2;
	case 3:
		return infoMap_3;
	case 4:
		return infoMap_4;
	case 5:
		return infoMap_5;
	case 6:
		return infoMap_6;
	default:
		break;
	}
	return infoMap_1;

}
