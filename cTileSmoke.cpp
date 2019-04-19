#include "DXUT.h"
#include "cTileSmoke.h"


cTileSmoke::cTileSmoke(float x,float y)
{
	info.m_pos.x = x;
	info.m_pos.y = y;
}


cTileSmoke::~cTileSmoke()
{
}

void cTileSmoke::Init()
{
	m_smoke = new cAnimation("./image/effect/smoke/", 5, 100);
}

void cTileSmoke::Update()
{
	m_smoke->Update();
}

void cTileSmoke::Render()
{
	m_smoke->Render(info.m_pos.x, info.m_pos.y, 1.0, 0, D3DCOLOR_ARGB(150, 255, 255, 255));
}

void cTileSmoke::Release()
{
	SAFE_DELETE(m_smoke);
}
