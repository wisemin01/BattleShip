#include "DXUT.h"
#include "cTextManager.h"


cTextManager::cTextManager()
{
	Init();
}


cTextManager::~cTextManager()
{
	m_font->Release();
}

void cTextManager::Init()
{
	D3DXFONT_DESC desc = {
		50,0
		, FW_BOLD, 1, TRUE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE
		, TEXT("Fixedsys")
	};

	D3DXCreateFontIndirect(g_device, &desc, &m_font);
}

void cTextManager::drawText(string str, D3DXVECTOR2 pos, FLOAT fontSize, D3DXCOLOR color)
{
	const char* all = str.c_str();
	int len = 1 + strlen(all);
	wchar_t* t = new wchar_t[len];

	if (NULL == t)
		throw std::bad_alloc();

	mbstowcs(t, all, len);

	TCHAR* txt = (TCHAR*)t;

	RECT rcFont = { 0 };

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,
		pos.x,
		pos.y,
		0);

	IMAGEMANAGER->GetM_Sprite()->SetTransform(&matTrans);
	m_font->DrawTextW(IMAGEMANAGER->GetM_Sprite(), txt, lstrlen(txt), &rcFont, DT_NOCLIP, color);
	SAFE_DELETE(txt);
}

void cTextManager::drawNumber(int Number,int TotalNum, D3DXVECTOR2 pos, D3DXCOLOR color)
{
	string str = "";
	for (int i = 0; i < TotalNum - strlen(to_string(Number).c_str()); i++) {
		str += "0";
	}
	str += to_string(Number);

	const char* all = str.c_str();
	int len = 1 + strlen(all);
	wchar_t* t = new wchar_t[len];

	if (NULL == t)
		throw std::bad_alloc();

	mbstowcs(t, all, len);

	TCHAR* txt = (TCHAR*)t;

	RECT rcFont = { 0 };

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,
		pos.x,
		pos.y,
		0);

	IMAGEMANAGER->GetM_Sprite()->SetTransform(&matTrans);
	m_font->DrawTextW(IMAGEMANAGER->GetM_Sprite(), txt, lstrlen(txt), &rcFont, DT_NOCLIP, color);
	SAFE_DELETE(txt);
}
