#ifndef _MUSIC_INFO_UTIL_
#define _MUSIC_INFO_UTIL_
#include "cocos2d.h"
#include <map>
using namespace cocos2d;
using namespace std;
class MusicInfoUtil{
public:
	static MusicInfoUtil* getInstance();
	map <int, string> getMusicInfo(int type);

private:
	void init();
	MusicInfoUtil();
	~MusicInfoUtil();

	static MusicInfoUtil* _instance;
	
	map <int, string> infoMap_0;
	map <int, string> infoMap_1;
	map <int, string> infoMap_2;
	map <int, string> infoMap_3;
	map <int, string> infoMap_4;
	map <int, string> infoMap_5;
	map <int, string> infoMap_6;
};

#endif