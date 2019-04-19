#include "DXUT.h"
#include "cScroolMap.h"


cScroolMap::cScroolMap()
{
	m_scroolMap = IMAGEMANAGER->FindImage("backGround");
}

cScroolMap::cScroolMap(texture * text)
{
	m_scroolMap = text;
}

cScroolMap::~cScroolMap()
{
}

void cScroolMap::Init()
{
	//m_topUIBase = IMAGEMANAGER->FindImage("topUIBase");
	//m_smoke = new cAnimation("./image/Effects/smoke", 3, 160);
	info.m_pos.x = 0;
	info.m_pos.y = 0;
}

void cScroolMap::Update()
{
	//m_smoke->Update();
}

void cScroolMap::Render()
{
	m_scroolMap->Render(info.m_pos.x, info.m_pos.y,info.m_size);
	//m_smoke->Render(info.m_pos.x + 100, info.m_pos.y + 120, info.m_size);
	//m_topUIBase->Render(0,0, info.m_size);
}

void cScroolMap::Release()
{
	//SAFE_DELETE(m_smoke);
}
