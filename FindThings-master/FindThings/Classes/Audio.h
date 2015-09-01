#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>

#define BACKGORUNDMUSIC "music/game_bgm.ogg"
#define COUNTDOWN "music/count_down.ogg"
#define CLICK "music/click.ogg"
#define FINISHTASK "music/finish_task.ogg"
#define QUICKFIND "music/quick_find.ogg"
#define REVIVE "music/revive.ogg"
#define SELECTCORRECT "music/select_correct.ogg"
#define SELECTERROR "music/select_error.ogg"
#define SELECTTIME "music/select_time.ogg"
#define SHOWPAYPOINT "music/show_pay_point.ogg"

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