#pragma once
#include "singleton.h"
class cTextManager :
	public singleton <cTextManager>
{
private:
	LPD3DXFONT m_font;
public:
	cTextManager();
	virtual ~cTextManager();

	void Init();
	void drawText(string str, D3DXVECTOR2 pos,FLOAT fontSize, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	void drawNumber(int Number,int TotalNum, D3DXVECTOR2 pos, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
};

#define TEXTMANAGER cTextManager::GetInstance()