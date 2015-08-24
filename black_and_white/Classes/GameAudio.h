#ifndef GameAudio_H
#define GameAudio_H
#include "cocos2d.h"
#include "json\reader.h"
#include "json\document.h"
#include "json\writer.h"
#include "json\stringbuffer.h"
using  namespace cocos2d;
class GameAudio{
public:
	GameAudio();
	static GameAudio * getInstance();
	void  init();
	void prepare();
	void playsounds();
	void playerror();
public:
	static GameAudio*_instance;
	int music_index;//记录到当前歌曲的第几个音符
	int currentMusic_Type;//0,1,2,3,4,5,6对应长度：269，57，152，295，86，135，114 
};
#endif