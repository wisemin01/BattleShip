#include "DXUT.h"
#include "cEnemySoldier.h"
#include "cPlayerSoldier.h"

#include "cViewPointMover.h"
#include "cCastle.h"

cEnemySoldier::cEnemySoldier(float x, float y)
{
	info.m_pos.x = x;
	info.m_pos.y = y;
}


cEnemySoldier::~cEnemySoldier()
{
}

void cEnemySoldier::Init()
{
	m_attack	= new cAnimation("./image/Soldier/rAttack/C00", 41, 25, true);
	m_death		= new cAnimation("./image/Soldier/rDeath/E00", 41, 25, true);
	m_lose		= new cAnimation("./image/Soldier/rLose/D00", 41, 25, true);
	m_win		= new cAnimation("./image/Soldier/rWin/B00", 21, 25, true);
	m_walk		= new cAnimation("./image/Soldier/rWalk/A00", 41, 25, true);

	m_soldierState = e_walk;

	info.m_collider.left = info.m_pos.x - 50;
	info.m_collider.top = info.m_pos.y - 100;
	info.m_collider.right = info.m_pos.x + 50;
	info.m_collider.bottom = info.m_pos.y + 100;

	m_DyingTime = 0;
	m_DyingMin = 0;
}

void cEnemySoldier::Update()
{
	AssistUpdate();

	for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_PLAYER_SOL))) {
		if (nIntersectRect(info.m_collider, iter->GetObjectInfo().m_collider)) {
			if (m_soldierState != e_death && m_soldierState != e_win && m_soldierState != e_lose && dynamic_cast<cPlayerSoldier*>(iter)->GetSoldierState() != e_death)
				m_soldierState = e_attack;
			break;
		}
		else {
			if (m_soldierState != e_death && m_soldierState != e_win && m_soldierState != e_lose)
				m_soldierState = e_walk;
		}
	}
	
	switch (m_soldierState) {
	case e_walk:
		if (info.m_pos.x <= 1000 - VIEWPOINT_X) {
			m_soldierState = e_attack;
		}
		else {
			info.m_pos.x -= 70 * g_deltaTime;
		}
		break;
	case e_attack:
		if (info.m_pos.x <= 1000 - VIEWPOINT_X) {
			int &playerCastleHP = dynamic_cast<cCastle*>(OBJECTMANAGER->GetObjectList(OBJ_CASTLE)->front())->hp;
			if (playerCastleHP > 1000)
				playerCastleHP--;
		}
		else
			m_DyingTime++;
		break;
	case e_death:
		m_DyingTime++;
		break;
	case e_win:
		if (m_CheeringTime < g_nowTime)
			m_soldierState = e_walk;
		break;
	case e_lose:
		if (m_SadTime < g_nowTime)
			m_soldierState = e_walk;
		break;
	}

	if (m_DyingTime == 250) {
		m_soldierState = e_death;
		m_death->SetFrame(0);
		m_DyingMin = g_nowTime + 575;
	}
	if (m_DyingMin < g_nowTime) {
		if (m_DyingMin != 0) {
			DeleteObject();
			GAMEMANAGER->SetSoldierCount(false, GAMEMANAGER->GetSoldierCount(false) - 1);
		}
	}
}
