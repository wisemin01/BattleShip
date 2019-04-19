#include "DXUT.h"
#include "cEnemyCastle.h"

#include "cEnemySoldier.h"
#include "cPlayerSoldier.h"
#include "cViewPointMover.h"

#include "cImageUI.h"
#include "cScoreBoard.h"

cEnemyCastle::cEnemyCastle(D3DXVECTOR2 pos)
	:cCastle(pos)
{
}


cEnemyCastle::~cEnemyCastle()
{
}

void cEnemyCastle::Init()
{
	m_castleImage = IMAGEMANAGER->FindImage("enemyCastle");
	m_spawnTime = g_nowTime + 1000;
	m_imageUI = nullptr;
	isCreate = false;
	isCreate2 = false;
}

void cEnemyCastle::Update()
{
	HPUpdate();
	if (GAMEMANAGER->GetEnemyMapDestroyPercent() < 100) {
		if (g_nowTime > m_spawnTime) {
			if (GAMEMANAGER->GetSoldierCount(false) < 15) {
				OBJECTMANAGER->AddObject(new cEnemySoldier(2900 - dynamic_cast<cViewPointMover*>(OBJECTMANAGER->GetObjectList(OBJ_VIEWER)->front())->GetViewPointX(), 840), OBJ_ENEMY_SOL);
				m_spawnTime = g_nowTime + 2000 + GAMEMANAGER->GetEnemyMapDestroyPercent() * 25;
				GAMEMANAGER->SetSoldierCount(false, GAMEMANAGER->GetSoldierCount(false) + 1);
			}
		}
	}
}

void cEnemyCastle::Render()
{
	m_castleImage->Render(info.m_pos.x, info.m_pos.y);
}

void cEnemyCastle::Release()
{
}

void cEnemyCastle::HPUpdate()
{
	if (hp <= 1000) {
		for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_PLAYER_SOL))) {
			dynamic_cast<cPlayerSoldier*>(iter)->SetSoldierState(cSoldier::e_win);
			dynamic_cast<cPlayerSoldier*>(iter)->SetCheeringTime(g_nowTime + 50000);
		}
		for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_ENEMY_SOL))) {
			dynamic_cast<cEnemySoldier*>(iter)->SetSoldierState(cSoldier::e_lose);
			dynamic_cast<cEnemySoldier*>(iter)->SetSadTime(g_nowTime + 50000);
		}
		if (!isCreate)
			m_imageUI = dynamic_cast<cImageUI*>(OBJECTMANAGER->AddObject(new cImageUI(IMAGEMANAGER->FindImage("win"), D3DXVECTOR2(WINSIZEX / 2, WINSIZEY / 2), TRUE), OBJ_GUI));
		isCreate = true;
		GAMEMANAGER->SetWiner(1);
	}
	if (m_imageUI)
		if (GETKEY_DOWN(VK_LBUTTON)) {
			m_imageUI->SetIsRender(false);
			if(!isCreate2)
			OBJECTMANAGER->AddObject(new cScoreBoard(), OBJ_GUI);
			isCreate2 = true;
		}
}
