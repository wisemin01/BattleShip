#include "DXUT.h"
#include "cInputManager.h"


cInputManager::cInputManager()
{
	memset(m_keyMap, 0, sizeof(m_keyMap));
	m_mouseOnTile = false;
}


cInputManager::~cInputManager()
{
}

void cInputManager::KeyInputUpdate()
{
	memcpy(m_OldKeyState, m_CurKeyState, 256);
	memset(m_CurKeyState, e_key_none, sizeof(m_CurKeyState));

	GetKeyboardState(m_CurKeyState);

	for (int i = 0; i < 256; i++) {
		BYTE vKey = m_CurKeyState[i] & 0x80;
		m_CurKeyState[i] = (vKey) ? 1 : 0;

		INT nOld = m_OldKeyState[i];
		INT nCur = m_CurKeyState[i];

		if (nOld == 1 && nCur == 1) m_keyMap[i] = e_key_retain;
		else if (nOld == 0 && nCur == 1) m_keyMap[i] = e_key_down;
		else if (nOld == 1 && nCur == 0) m_keyMap[i] = e_key_up;
		else m_keyMap[i] = e_key_none;
	}

	POINT pt;

	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);

	m_mousePos = D3DXVECTOR2(pt.x, pt.y);
}

INT cInputManager::GetKeyRetain(INT key_num)
{
	return (m_keyMap[key_num] == e_key_retain);
}

INT cInputManager::GetKeyDown(INT key_num)
{
	return (m_keyMap[key_num] == e_key_down);
}

INT cInputManager::GetKeyUp(INT key_num)
{
	return (m_keyMap[key_num] == e_key_up);
}
