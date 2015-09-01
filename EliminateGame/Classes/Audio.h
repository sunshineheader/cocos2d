#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>

//定义音效的路径
#define BACKGORUND_MUSIC "music/bg_music.mp3"//背景音乐
#define CLICK "music/click.ogg"//点击音效


class Audio{
public:
	static Audio* getInstance();
	//播放背景音
	void playBGM(char* soundName);
	//播放音效
	void playSound(char* soundName);
	void prepare();
private:
	static Audio* m_instance;
};
#endif