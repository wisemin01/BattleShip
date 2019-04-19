#include "DXUT.h"
#include "cImageUI.h"


cImageUI::cImageUI(texture * text, D3DXVECTOR2 pos, bool flag, DWORD DestroyTime)
{
	m_image = text;
	info.m_pos = pos;
	IsCenterRender = flag;

	m_destoyTime = DestroyTime;
}

cImageUI::~cImageUI()
{
}

void cImageUI::Init()
{
	IsRender = true;
}

void cImageUI::Update()
{
	if (m_destoyTime != 0 && m_destoyTime < g_nowTime) {
		DeleteObject();
	}
}

void cImageUI::Render()
{
	if (IsRender) {
		if (!IsCenterRender)
			m_image->Render(info.m_pos.x, info.m_pos.y);
		else
			m_image->CenterRender(info.m_pos.x, info.m_pos.y);
	}
}

void cImageUI::Release()
{
}

