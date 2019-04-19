#pragma once
#include "singleton.h"
class cInputManager :
	public singleton <cInputManager>
{
private:
	enum {
		e_key_retain,
		e_key_down,
		e_key_up,
		e_key_none
	};

	D3DXVECTOR2 m_mousePos;
	D3DXVECTOR2 m_mouseOnTilePos;

	BOOL m_mouseOnTile;

	BYTE m_keyMap[256];
	BYTE m_CurKeyState[256];
	BYTE m_OldKeyState[256];
public:
	cInputManager();
	~cInputManager();

	void KeyInputUpdate();

	INT GetKeyRetain(INT key_num);
	INT GetKeyDown(INT key_num);
	INT GetKeyUp(INT key_num);

	D3DXVECTOR2 GetMousePos() { return m_mousePos; }

	void SetMouseOnTilePos(D3DXVECTOR2 pos) { m_mouseOnTilePos = pos; }
	D3DXVECTOR2 GetMouseOnTilePos() { return m_mouseOnTilePos; }

	void SetMouseOnTile(BOOL b) { m_mouseOnTile = b; }
	BOOL GetMouseOnTile() { return m_mouseOnTile; }
};

#define INPUTMANAGER cInputManager::GetInstance()

#define GETKEY_RETAIN(key) INPUTMANAGER->GetKeyRetain(key)
#define GETKEY_DOWN(key) INPUTMANAGER->GetKeyDown(key)
#define GETKEY_UP(key) INPUTMANAGER->GetKeyUp(key)