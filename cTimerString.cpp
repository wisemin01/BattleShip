#include "DXUT.h"
#include "cTimerString.h"


cTimerString::cTimerString(const string & str, DWORD timer, D3DXVECTOR2 pos, INT size)
	: str(str), timer(timer + g_nowTime)
{
	info.m_pos = pos;
	size = size;
}

cTimerString::~cTimerString()
{
}

void cTimerString::Init()
{
}

void cTimerString::Update()
{
	if (g_nowTime >= timer) {
		DeleteObject();
	}
}

void cTimerString::Render()
{
	TEXTMANAGER->drawText(str, info.m_pos, size);
}

void cTimerString::Release()
{
}
