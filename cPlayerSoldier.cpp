#include "DXUT.h"
#include "cPlayerSoldier.h"
#include "cEnemySoldier.h"

#include "cViewPointMover.h"
#include "cCastle.h"


cPlayerSoldier::cPlayerSoldier(float x, float y)
{
	info.m_pos.x = x;
	info.m_pos.y = y;
}


cPlayerSoldier::~cPlayerSoldier()
{
}

void cPlayerSoldier::Init()
{
	m_attack	 = new cAnimation("./image/Soldier/bAttack/", 41, 25);
	m_death		 = new cAnimation("./image/Soldier/bDeath/", 41, 25);
	m_lose		 = new cAnimation("./image/Soldier/bLose/B00", 41, 25, true);
	m_win		 = new cAnimation("./image/Soldier/bWin/E00", 21, 25, true);
	m_walk		 = new cAnimation("./image/Soldier/bWalk/C00", 41, 25, true);

	m_soldierState = e_walk;

	info.m_collider.left = info.m_pos.x - 50;
	info.m_collider.top = info.m_pos.y - 100;
	info.m_collider.right = info.m_pos.x + 50;
	info.m_collider.bottom = info.m_pos.y + 100;

	m_DyingTime = 0;
	m_DyingMin = 0;
}

void cPlayerSoldier::Update()
{
	AssistUpdate();

	for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_ENEMY_SOL))) {
		if(nIntersectRect(info.m_collider, iter->GetObjectInfo().m_collider)) {
			if (m_soldierState != e_death && m_soldierState != e_win &&  m_soldierState != e_lose && dynamic_cast<cEnemySoldier*>(iter)->GetSoldierState() != e_death)
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
		if (info.m_pos.x > 2800 - VIEWPOINT_X) {
			m_soldierState = e_attack;
		}
		else {
			info.m_pos.x += 70 * g_deltaTime;
		}
		break;
	case e_attack:
		if (info.m_pos.x > 2800 - VIEWPOINT_X) {
			int &enemyCastleHP = dynamic_cast<cCastle*>(OBJECTMANAGER->GetObjectList(OBJ_CASTLE)->back())->hp;
			if (enemyCastleHP > 1000)
				enemyCastleHP--;
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
		m_DyingMin = g_nowTime + 725;
	}
	if (m_DyingMin < g_nowTime) {
		if (m_DyingMin != 0) {
			DeleteObject();
			GAMEMANAGER->SetSoldierCount(true, GAMEMANAGER->GetSoldierCount(true) - 1);
		}
	}
}
