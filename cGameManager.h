#pragma once
#include "singleton.h"
class cGameManager :
	public singleton<cGameManager>
{
	enum TURN {
		e_player,
		e_enemy
	};
	enum WINER {
		e_playerWin,
		e_enemyWin,
		e_nobodyWin
	};
private:
	INT m_TurnOwner;
	INT m_PlayerScore;
	INT m_playerPlusScore;

	INT m_gameWiner;

	INT m_playerMapDestroyPercent;
	INT m_enemyMapDestroyPercent;

	INT m_playerSoldierCount;
	INT m_enemySoldierCount;

	INT m_TurnChangeTime;

	BOOL m_InputHelpFlag;
	BOOL m_InfoFlag;

	DWORD m_curnTime;
public:
	cGameManager();
	~cGameManager();

	INT GetTurnOwner() { return m_TurnOwner; }
	INT GetPlayerScore() { return m_PlayerScore; }

	void Update();

	void SetPlayerScore(int score) { m_PlayerScore = score; }
	void SetTurnOwner(INT owner);

	INT GetPlayerMapDestroyPercent() { return m_playerMapDestroyPercent; }
	INT GetEnemyMapDestroyPercent() { return m_enemyMapDestroyPercent; }

	INT GetSoldierCount(bool flag) { if (flag)return m_playerSoldierCount; else return m_enemySoldierCount; }
	void SetSoldierCount(bool flag, int amount) { if (flag)m_playerSoldierCount = amount; else m_enemySoldierCount = amount; }

	INT GetTurnChangeTime() { return m_TurnChangeTime; }

	void SetInputHelpFlag(bool b) { m_InputHelpFlag = b; }
	BOOL GetInputHelpFlag() {return m_InputHelpFlag;}

	void SetInfoFlag(bool b) { m_InfoFlag = b; }
	BOOL GetInfoFlag() { return m_InfoFlag; }

	void SetWiner(INT iV) { m_gameWiner = iV; }
	INT GetWiner() { return m_gameWiner; }

	void SetPlusScore(INT score) { m_playerPlusScore = score; }
	INT GetPlusScore() { return m_playerPlusScore; }
};

#define GAMEMANAGER cGameManager::GetInstance()