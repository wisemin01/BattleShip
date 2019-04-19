#include "DXUT.h"
#include "cHpBar.h"


cHpBar::cHpBar(const string & path, int & hp,D3DXVECTOR2 pos)
	:hp(hp)
{
	info.m_pos = pos;
	m_hpbar = new cAnimation(path, 6, 1000);
}

cHpBar::~cHpBar()
{
}

void cHpBar::Init()
{
}

void cHpBar::Update()
{
}

void cHpBar::Render()
{
	m_hpbar->FrameRender(info.m_pos.x, info.m_pos.y, 6 - (int)((float)hp*0.001));
}

void cHpBar::Release()
{
	SAFE_DELETE(m_hpbar);
}
