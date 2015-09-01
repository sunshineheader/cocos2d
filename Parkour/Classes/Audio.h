#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>
class Audio{
public:
	static Audio* getInstance();
	void playBGM(char* soundName);
	void playSound(char* soundName);
	void prepare();
private:
	static Audio* m_instance;
};
#endif