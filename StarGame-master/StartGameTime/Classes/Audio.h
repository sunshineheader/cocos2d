#ifndef _AUDIO_H_
#define _AUDIO_H_
class Audio{
public:
	static Audio* getInstance();
	void playBGM();
	void playReadyGo();
	void playClick();
	void playScore();
	void playPop();
	void playCombo(int size);
	void playClear();//清除
	void playNextGameRound();//进入下一回合
	void playPropBomb();//道具炸弹
	void playPropRainbow();//道具彩虹
	void playPropPlusTime();//道具加时
	void playBeep();//倒计时
	void playLanding();//加载
	void prepare();
	void playUpgrade();
	void playSignin();
private:
	static Audio* m_instance;
	int scoreId;
};
#endif
