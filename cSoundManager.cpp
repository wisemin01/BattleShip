#include "DXUT.h"
#include "cSoundManager.h"

#pragma comment(lib,"winmm.lib")

cSoundManager::cSoundManager()
{
	wDeviceID = 0;

	bgm_index = 0;
	bgm_time = 0;
	change_time = 0;
}


cSoundManager::~cSoundManager()
{
	int i = 1;
	for (auto iter : m_sounds) {
		mciSendCommand(i++, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	}
	m_sounds.clear();
}

void cSoundManager::Update()
{
	if (bgm_index != 0) {
		if (change_time < g_nowTime) {
			pPlaySound(bgm_index);
			change_time = g_nowTime + bgm_time;
		}
	}
}

DWORD cSoundManager::LoadWAV(HWND hWnd, LPCTSTR lpszWave)
{
	DWORD result;

	m_mciopen.lpstrDeviceType = L"WaveAudio";

	m_mciopen.lpstrElementName = lpszWave;

	result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&m_mciopen);

	if (result)
		return result;

	wDeviceID = m_mciopen.wDeviceID;

	m_mciplay.dwCallback = (DWORD)(hWnd);

	if (result)
		return result;

	return 0;
}

DWORD cSoundManager::LoadMp3(HWND hWnd, LPCTSTR lpszMp3)
{
	DWORD result;

	m_mciopen.lpstrDeviceType = L"MPEGVideo";

	m_mciopen.lpstrElementName = lpszMp3;

	result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&m_mciopen);

	if (result)
		return result;

	wDeviceID = m_mciopen.wDeviceID;

	m_mciplay.dwCallback = (DWORD)(hWnd);

	if (result)
		return result;

	return 0;
}

void cSoundManager::AddSound(LPCTSTR lpszWave)
{
	m_sounds.push_back(LoadWAV(DXUTGetHWND(),lpszWave));
}

void cSoundManager::pPlayBgm(int index, DWORD ch_time)
{
	if (bgm_index != 0) {
		m_sounds[index - 1] = mciSendCommand(index, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&m_mciplay);
		m_sounds[index - 1] = mciSendCommand(index, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciplay);
	}
	bgm_index = index;
	bgm_time = ch_time + 1000;
	
	change_time = 0;

	//change_time = g_nowTime + bgm_time;
}


void cSoundManager::pPlaySound(int index)
{
	m_sounds[index - 1] = mciSendCommand(index, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&m_mciplay);
	m_sounds[index - 1] = mciSendCommand(index, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciplay);
}

void cSoundManager::pStopSound(int index)
{
	m_sounds[index - 1] = mciSendCommand(index, MCI_SEEK, MCI_SEEK_TO_END, (DWORD)(LPVOID)&m_mciplay);
}
