#include "DXUT.h"
#include "cSoldier.h"

cSoldier::cSoldier()
{
	m_CheeringTime = 0;
	m_SadTime = 0;
	isCollision = false;
}

cSoldier::~cSoldier()
{
}


void cSoldier::Render()
{
	switch (m_soldierState) {
	case e_attack:
		m_attack->CenterRender(info.m_pos.x,info.m_pos.y);
		break;
	case e_death:
		m_death->CenterRender(info.m_pos.x, info.m_pos.y);
		break;
	case e_walk:
		m_walk->CenterRender(info.m_pos.x, info.m_pos.y);
		break;
	case e_win:
		m_win->CenterRender(info.m_pos.x, info.m_pos.y);
		break;
	case e_lose:
		m_lose->CenterRender(info.m_pos.x, info.m_pos.y);
		break;
	}
}

void cSoldier::Release()
{
	SAFE_DELETE(m_attack);
	SAFE_DELETE(m_death);
	SAFE_DELETE(m_lose);
	SAFE_DELETE(m_win);
	SAFE_DELETE(m_walk);
}

void cSoldier::AssistUpdate()
{
	m_attack->Update();
	m_death->Update();
	m_lose->Update();
	m_win->Update();
	m_walk->Update();

	info.m_collider.left = info.m_pos.x - 50;
	info.m_collider.top = info.m_pos.y - 100;
	info.m_collider.right = info.m_pos.x + 50;
	info.m_collider.bottom = info.m_pos.y + 100;
}

void cSoldier::SetSoldierState(INT newState)
{
	if (m_soldierState == newState)
		return;

	m_soldierState = newState;

	if (m_soldierState == e_death)
		m_death->SetFrame(0);

	if (m_soldierState == e_win)
		m_win->SetFrame(0);

	if (m_soldierState == e_lose)
		m_lose->SetFrame(0);

}
