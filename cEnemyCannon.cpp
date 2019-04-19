#include "DXUT.h"
#include "cEnemyCannon.h"

#include "cTileMap.h"
#include "cTileExplode.h"

#include "cViewPointMover.h"
#include "cEnemySoldier.h"

cEnemyCannon::cEnemyCannon()
{
}


cEnemyCannon::~cEnemyCannon()
{
}

void cEnemyCannon::Init()
{
	m_pivotTile = nullptr;
	m_nowTile = nullptr;

	m_AIMode = E_HUNT;
	m_TargetDir = E_NOSEARCH;

	m_AttackTime = 0;
	m_prevAttack = 0;
}

void cEnemyCannon::Update()
{
	if (m_prevAttack != GAMEMANAGER->GetTurnOwner())
		m_AttackTime = g_nowTime + 2500;

	if (GAMEMANAGER->GetWiner() == 2)
		Attack();

	m_prevAttack = GAMEMANAGER->GetTurnOwner();
}

void cEnemyCannon::Render()
{

}

void cEnemyCannon::Release()
{
}

void cEnemyCannon::Attack()
{
	if (GAMEMANAGER->GetTurnOwner() != TRUE)
		return;

	if (m_AttackTime > g_nowTime)
		return;
	
	m_AttackTime = g_nowTime + 500;

	if (m_AIMode == E_HUNT)
		HuntAttack();

	else if (m_AIMode == E_TARGET)
		TargetAttack();
}

void cEnemyCannon::HuntAttack()
{
	INT RandomX = RandomNumber(0, 9);
	INT RandomY = RandomNumber(0, 9);

	auto PlayerTileArray = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->front())->GetMapTile();

	if (PlayerTileArray[RandomX][RandomY]->GetIsDestroy() == TRUE)
		return;

	if (PlayerTileArray[RandomX][RandomY]->GetOnUnit()) {
		m_AIMode = E_TARGET;

		PlayerTileArray[RandomX][RandomY]->SetDestroy(true);
		GAMEMANAGER->SetPlayerScore(GAMEMANAGER->GetPlayerScore() - 5);
		OBJECTMANAGER->AddObject(new cTileExplode(PlayerTileArray[RandomX][RandomY]->GetPos().x,
			PlayerTileArray[RandomX][RandomY]->GetPos().y), OBJ_EFFECT);

		m_pivotTile = PlayerTileArray[RandomX][RandomY];
		m_nowTile = m_pivotTile;
	}
	else {
		PlayerTileArray[RandomX][RandomY]->SetDestroy(true);
		OBJECTMANAGER->AddObject(new cTileExplode(PlayerTileArray[RandomX][RandomY]->GetPos().x,
			PlayerTileArray[RandomX][RandomY]->GetPos().y), OBJ_EFFECT);

		GAMEMANAGER->SetTurnOwner(FALSE);
	}
}

void cEnemyCannon::TargetAttack()
{
	auto PlayerTileArray = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->front())->GetMapTile();

	switch (m_TargetDir)
	{

	case E_NOSEARCH:

		m_TargetDir = E_BOTTOM;

		break;

		
	case E_BOTTOM:

		if (m_nowTile->GetArrayXPos() > 9 || m_nowTile->GetArrayYPos() + 1 > 9) {
			m_nowTile = m_pivotTile;
			m_TargetDir = E_LEFT;
			return;
		}

		if (PlayerTileArray[m_nowTile->GetArrayYPos() + 1][m_nowTile->GetArrayXPos()]->GetIsDestroy()) {
			m_nowTile = m_pivotTile;
			m_TargetDir = E_LEFT;
			return;
		}

		m_nowTile = PlayerTileArray[m_nowTile->GetArrayYPos() + 1][m_nowTile->GetArrayXPos()];
		m_nowTile->SetDestroy(true);

		OBJECTMANAGER->AddObject(new cTileExplode(m_nowTile->GetPos().x,
			m_nowTile->GetPos().y), OBJ_EFFECT);

		if (m_nowTile->GetOnUnit()) {
			GAMEMANAGER->SetPlayerScore(GAMEMANAGER->GetPlayerScore() - 5);
			GAMEMANAGER->SetTurnOwner(TRUE);
		}
		else {
			m_nowTile = m_pivotTile;
			m_TargetDir = E_LEFT;
			GAMEMANAGER->SetTurnOwner(FALSE);
		}

		break;

		
	case E_LEFT:

		if (m_nowTile->GetArrayXPos() - 1 < 0) {
			m_nowTile = m_pivotTile;
			m_TargetDir = E_TOP;
			return;
		}

		if (PlayerTileArray[m_nowTile->GetArrayYPos()][m_nowTile->GetArrayXPos() - 1]->GetIsDestroy()) {
			m_nowTile = m_pivotTile;
			m_TargetDir = E_TOP;
			return;
		}

		m_nowTile = PlayerTileArray[m_nowTile->GetArrayYPos()][m_nowTile->GetArrayXPos() - 1];
		m_nowTile->SetDestroy(true);

		OBJECTMANAGER->AddObject(new cTileExplode(m_nowTile->GetPos().x,
			m_nowTile->GetPos().y), OBJ_EFFECT);

		if (m_nowTile->GetOnUnit()) {
			GAMEMANAGER->SetPlayerScore(GAMEMANAGER->GetPlayerScore() - 5);
			GAMEMANAGER->SetTurnOwner(TRUE);
		}
		else {
			m_nowTile = m_pivotTile;
			m_TargetDir = E_TOP;
			GAMEMANAGER->SetTurnOwner(FALSE);
		}

		break;


	case E_TOP:

		if (m_nowTile->GetArrayYPos() - 1 > 0) {
			m_nowTile = m_pivotTile;
			m_TargetDir = E_RIGHT;
			return;
		}

		if (PlayerTileArray[m_nowTile->GetArrayYPos() - 1][m_nowTile->GetArrayXPos()]->GetIsDestroy()) {
			m_nowTile = m_pivotTile;
			m_TargetDir = E_RIGHT;
			return;
		}

		m_nowTile = PlayerTileArray[m_nowTile->GetArrayYPos() - 1][m_nowTile->GetArrayXPos()];
		m_nowTile->SetDestroy(true);

		OBJECTMANAGER->AddObject(new cTileExplode(m_nowTile->GetPos().x,
			m_nowTile->GetPos().y), OBJ_EFFECT);

		if (m_nowTile->GetOnUnit()) {
			GAMEMANAGER->SetPlayerScore(GAMEMANAGER->GetPlayerScore() - 5);
			GAMEMANAGER->SetTurnOwner(TRUE);
		}
		else {
			m_nowTile = m_pivotTile;
			m_TargetDir = E_RIGHT;
			GAMEMANAGER->SetTurnOwner(FALSE);
		}

		break;


	case E_RIGHT:

		if (m_nowTile->GetArrayXPos() + 1 > 9) {
			m_AIMode = E_HUNT;
			m_TargetDir = E_NOSEARCH;
			return;
		}

		if (PlayerTileArray[m_nowTile->GetArrayYPos()][m_nowTile->GetArrayXPos() + 1]->GetIsDestroy()) {
			m_AIMode = E_HUNT;
			m_TargetDir = E_NOSEARCH;
			return;
		}

		m_nowTile = PlayerTileArray[m_nowTile->GetArrayYPos()][m_nowTile->GetArrayXPos() + 1];
		m_nowTile->SetDestroy(true);

		OBJECTMANAGER->AddObject(new cTileExplode(m_nowTile->GetPos().x,
			m_nowTile->GetPos().y), OBJ_EFFECT);

		if (m_nowTile->GetOnUnit()) {
			GAMEMANAGER->SetPlayerScore(GAMEMANAGER->GetPlayerScore() - 5);
			GAMEMANAGER->SetTurnOwner(TRUE);
		}
		else {
			m_nowTile = m_pivotTile;
			m_TargetDir = E_NOSEARCH;
			GAMEMANAGER->SetTurnOwner(FALSE);
		}

		break;
	}
}

void cEnemyCannon::CannonShoot(D3DXVECTOR2 startPos)
{
}

bool cEnemyCannon::Shot()
{
	return false;
}
