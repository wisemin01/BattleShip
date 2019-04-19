#include "DXUT.h"
#include "cTileExplode.h"



cTileExplode::cTileExplode(float x, float y, DWORD MaintenanceTime)
{
	info.m_pos = D3DXVECTOR2(x, y);
	m_MaintenanceTime = MaintenanceTime + g_nowTime;
}

cTileExplode::~cTileExplode()
{
}

void cTileExplode::Init()
{
	m_explode = new cAnimation("./image/effect/explode/", 9, 50);
	SOUNDMANAGER->pPlaySound(2);
}

void cTileExplode::Update()
{
	m_explode->Update();
	if (m_MaintenanceTime <= g_nowTime) {
		DeleteObject();
	}
}

void cTileExplode::Render()
{
	m_explode->CenterRender(info.m_pos.x + 49, info.m_pos.y);
}

void cTileExplode::Release()
{
	SAFE_DELETE(m_explode);
}
