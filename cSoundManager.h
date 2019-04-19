#pragma once
#include "singleton.h"
class cSoundManager :
	public singleton<cSoundManager>
{
private:
	MCI_OPEN_PARMS m_mciopen;
	MCI_PLAY_PARMS m_mciplay;
	MCI_STATUS_PARMS m_mcistate;

	UINT wDeviceID;

	vector<DWORD> m_sounds;

	INT bgm_index;

	DWORD bgm_time;
	DWORD change_time;
public:
	cSoundManager();
	~cSoundManager();

	void Update();

	DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave);
	DWORD LoadMp3(HWND hWnd, LPCTSTR lpszMp3);

	void AddSound(LPCTSTR lpszWave);
	void pPlayBgm(int index,DWORD ch_time);
	void pPlaySound(int index);
	void pStopSound(int index);
};

#define SOUNDMANAGER cSoundManager::GetInstance()