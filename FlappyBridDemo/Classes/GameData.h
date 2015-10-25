#pragma once
class GameData {

public:
	GameData();
	~GameData();
	static GameData * getInstance();
	static void   destoryInstance();
public:
	inline void setCurrcertSource(int CurrcertSource){ m_CurrcertSource = CurrcertSource; };
	inline int  getCurrcertSource(){ return m_CurrcertSource; };
	inline void setHistorySource(int HistorySource){ m_HistorySource = HistorySource; };
	inline int  getHistorySource(){ return m_HistorySource; };
	inline void setCurrcertRank(int CurrcertRank){ m_CurrcertRank = CurrcertRank; };
	inline int  getCurrcertRank(){ return m_CurrcertRank; };
	inline void setHistoryRank(int HistoryRank){ m_HistoryRank = HistoryRank; };
	inline int  getHistoryRank(){ return m_HistoryRank; };
	inline void setGoldNumber(int GoldNumber){ m_GoldNumber = GoldNumber; };
	inline int  getGoldNumber(){ return m_GoldNumber; };
	inline void setMoveSpeed(int MoveSpeed){ m_MoveSpeed = MoveSpeed; };
	inline int getMoveSpeed(){ return m_MoveSpeed; };
	inline void setMusicState(bool state){ m_MusicState = state; };
	inline bool  getMusicState(){ return m_MusicState; };
	inline void setSoundState(bool state){ m_SoundState = state; };
	inline bool getSoundState(){ return m_SoundState; };
public:
	void SaveCurrcertSource();
	void SaveHistorySource();
	void SaveCurrcertRank();
	void SaveHistoryRank();
	void SaveCurrcertGoldNumber();
	void SaveAllGoldNumber();
	void SaveCurrcertSpeed();
	void SaveMusicState();
	void SaveSoundState();
public:
	int CompareSorce();
	int CompareRank();
public:
	int SaveAllGolds();
private:
	static GameData * m_Instance;
	int m_CurrcertSource;
	int m_HistorySource;
	int m_CurrcertRank;
	int m_HistoryRank;
	int m_GoldNumber;
	int m_MoveSpeed;
	int m_AllGoldNumber;
	bool m_MusicState;
	bool m_SoundState;

};