#include "DXUT.h"
#include "cGameManager.h"

#include "cTileMap.h"
#include "cPlayerSoldier.h"
#include "cEnemySoldier.h"

#include "cViewPointMover.h"
#include "cImageUI.h"

cGameManager::cGameManager()
{
	m_TurnOwner = false;

	m_gameWiner = e_nobodyWin;
	m_PlayerScore = 0;
	m_playerPlusScore = 0;

	m_playerMapDestroyPercent = 0;
	m_enemyMapDestroyPercent = 0;

	m_playerSoldierCount = 0;
	m_enemySoldierCount = 0;

	m_TurnChangeTime = 16;
	m_curnTime = 0;

	m_InputHelpFlag = false;
	m_InfoFlag = false;
}


cGameManager::~cGameManager()
{
}

void cGameManager::Update()
{
	if (g_nowTime > m_curnTime) {
		if (m_gameWiner == e_nobodyWin) {
			m_TurnChangeTime--;
			m_curnTime = g_nowTime + 1000;
			if (m_TurnChangeTime == 0) {
				m_TurnChangeTime = 15;
				m_TurnOwner = !m_TurnOwner;
				if(m_TurnOwner == false)
					GAMEMANAGER->SetPlayerScore(GAMEMANAGER->GetPlayerScore() - 1);
			}
		}
	}

	m_playerMapDestroyPercent = 0;
	m_enemyMapDestroyPercent = 0;

	auto playerTileMap = dynamic_cast<cTileMap*> (OBJECTMANAGER->GetObjectList(OBJ_BOARD)->front());
	auto enemyTileMap = dynamic_cast<cTileMap*> (OBJECTMANAGER->GetObjectList(OBJ_BOARD)->back());

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (playerTileMap->GetTileByXY(j, i)->GetIsDestroy() &&
				playerTileMap->GetTileByXY(j, i)->GetOnUnit()) {
				m_playerMapDestroyPercent += 7;
			}
			if (enemyTileMap->GetTileByXY(j, i)->GetIsDestroy() &&
				enemyTileMap->GetTileByXY(j, i)->GetOnUnit()) {
				m_enemyMapDestroyPercent += 7;
			}
		}
	}
	if (m_playerMapDestroyPercent > 50) {
		m_playerMapDestroyPercent += 2;
	}
	if (m_enemyMapDestroyPercent > 50) {
		m_enemyMapDestroyPercent += 2;
	}
	if (m_PlayerScore < 0)
		m_PlayerScore = 0;
}

void cGameManager::SetTurnOwner(INT owner)
{
	if (m_TurnOwner != owner) {
		m_TurnOwner = owner;
		if (m_TurnOwner == false) {
			OBJECTMANAGER->AddObject(new cImageUI(IMAGEMANAGER->FindImage("YourTurn"), D3DXVECTOR2(WINSIZEX / 2, 500), TRUE, g_nowTime + 1000), OBJ_GUI);
			GAMEMANAGER->SetPlayerScore(GAMEMANAGER->GetPlayerScore() - 1);
		}
		m_TurnChangeTime = 15;
	}
	else {
		m_TurnChangeTime += 5;
		return;
	}
}
