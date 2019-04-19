#include "DXUT.h"
#include "cViewPointMover.h"


cViewPointMover::cViewPointMover()
{
}


cViewPointMover::~cViewPointMover()
{
}

void cViewPointMover::Init()
{
	m_viewPointX = 0;
	m_viewPointY = 0;

	RightFlag = false;
	LeftFlag = false;
}

void cViewPointMover::Update()
{
	Detection();
}

void cViewPointMover::Render()
{
}

void cViewPointMover::Release()
{
}

void cViewPointMover::Detection()
{
	// ============== 움직이는 오브젝트 ==============
	// e_gameMaps,
	// e_boards,
	// e_tileMaps
	// e_playerObjects,
	// e_enemyObjects,
	// e_effects,
	// ===============================================

	// ============== 고정되는 오브젝트 ==============
	// e_anyObjects,
	// e_GUIs
	// ===============================================

	if ((/*WINSIZEX > INPUTMANAGER->GetMousePos().x && */INPUTMANAGER->GetMousePos().x > WINSIZEX - 100 ||
		(GETKEY_RETAIN(VK_RIGHT)) || RightFlag) && m_viewPointX + WINSIZEX <= 3900) {
		
		// 우측으로 이동
		
		OBJECTMANAGER->MoveObjectGroup(OBJ_GAMEMAP,		D3DXVECTOR2(-17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_BOARD,		D3DXVECTOR2(-17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_CASTLE,		D3DXVECTOR2(-17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_TILEMAPS,	D3DXVECTOR2(-17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_ENEMY_OBJ,	D3DXVECTOR2(-17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_PLAYER_OBJ,	D3DXVECTOR2(-17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_EFFECT,		D3DXVECTOR2(-17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_PLAYER_SOL,	D3DXVECTOR2(-17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_ENEMY_SOL,	D3DXVECTOR2(-17, 0));

		m_viewPointX += 17;
	}
	if ((/*-10 < INPUTMANAGER->GetMousePos().x && */INPUTMANAGER->GetMousePos().x < 100 ||
		(GETKEY_RETAIN(VK_LEFT)) || LeftFlag) && m_viewPointX > 0) {
		
		// 좌측으로 이동
		
		OBJECTMANAGER->MoveObjectGroup(OBJ_GAMEMAP,		D3DXVECTOR2(17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_BOARD,		D3DXVECTOR2(17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_CASTLE,		D3DXVECTOR2(17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_TILEMAPS,	D3DXVECTOR2(17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_ENEMY_OBJ,	D3DXVECTOR2(17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_PLAYER_OBJ,	D3DXVECTOR2(17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_EFFECT,		D3DXVECTOR2(17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_PLAYER_SOL,	D3DXVECTOR2(17, 0));
		OBJECTMANAGER->MoveObjectGroup(OBJ_ENEMY_SOL,	D3DXVECTOR2(17, 0));

		m_viewPointX -= 17;
	}
	if (RightFlag && m_viewPointX + WINSIZEX >= 3900)
		RightFlag = false;
	if (LeftFlag && m_viewPointX + WINSIZEX <= 0)
		LeftFlag = false;
}

void cViewPointMover::FlagSetting(BOOL rightFlag, BOOL leftFlag)
{
	RightFlag = rightFlag;
	LeftFlag = leftFlag;
}
