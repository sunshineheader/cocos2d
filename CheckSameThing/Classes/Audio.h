#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>

#define BACKGORUNDMUSIC "bg_music.mp3"
#define COUNTDOWN "music/count_down.ogg"
#define CLICK "raw/game_conn_4.ogg"
#define ELECTRICITY "raw/game_conn_shine.ogg"
#define TIMEOVER "raw/time_over.mp3"
#define readyGo "raw/game_go.wav"
#define HITITEM "paddle_hit.wav"

class Audio{
public:
	static Audio* getInstance();
	void playBGM();
	void playReadyGo();
	void playBtnEffect();
	void cleanitem();
	void playSound(char* soundName);
	void prepare();
	void hititems();
	void timeover();
private:
	static Audio* m_instance;
};
#endif