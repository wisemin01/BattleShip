#include "DXUT.h"
#include "cIngameScene.h"

#include "cTileMap.h"
#include "cScroolMap.h"

#include "cViewPointMover.h"

#include "cPlayerCannon.h"
#include "cEnemyCannon.h"

#include "cTileObject.h"
#include "cPlayerCastle.h"
#include "cEnemyCastle.h"

#include "cImageUI.h"
#include "cHpBar.h"

cIngameScene::cIngameScene()
{
}


cIngameScene::~cIngameScene()
{
}


void cIngameScene::Init()
{
	OBJECTMANAGER->Reset();

	m_tileMap = dynamic_cast<cTileMap*>(OBJECTMANAGER->AddObject(new cTileMap(597, 25), OBJ_BOARD));
	m_enemyTileMap = dynamic_cast<cTileMap*>(OBJECTMANAGER->AddObject(new cTileMap(3210, 25), OBJ_BOARD));

	OBJECTMANAGER->AddObject(new cViewPointMover(), OBJ_VIEWER);
	OBJECTMANAGER->AddObject(new cScroolMap(), OBJ_GAMEMAP);

	OBJECTMANAGER->AddObject(new cPlayerCastle(D3DXVECTOR2(0, -100)), OBJ_CASTLE);
	OBJECTMANAGER->AddObject(new cEnemyCastle(D3DXVECTOR2(2620, -100)), OBJ_CASTLE);

	OBJECTMANAGER->AddObject(new cPlayerCannon(), OBJ_ANY);
	OBJECTMANAGER->AddObject(new cEnemyCannon(), OBJ_ANY);

	OBJECTMANAGER->AddObject(new cImageUI(IMAGEMANAGER->FindImage("./image/ui/playerFace/A.png"), D3DXVECTOR2(50, WINSIZEY - 330)), OBJ_GUI);
	OBJECTMANAGER->AddObject(new cImageUI(IMAGEMANAGER->FindImage("./image/ui/playerFace/B.png"), D3DXVECTOR2(WINSIZEX + 70 - 389, WINSIZEY - 330)), OBJ_GUI);

	imageUI1 = dynamic_cast<cImageUI*>(OBJECTMANAGER->AddObject(new cImageUI(IMAGEMANAGER->FindImage("./image/ui/AttackCountUI/1_.png"),
		D3DXVECTOR2(299, WINSIZEY - 300)), OBJ_GUI));
	imageUI1 = dynamic_cast<cImageUI*>(OBJECTMANAGER->AddObject(new cImageUI(IMAGEMANAGER->FindImage("./image/ui/AttackCountUI/1.png"),
		D3DXVECTOR2(WINSIZEX + 180 - 723, WINSIZEY - 300)), OBJ_GUI));

	OBJECTMANAGER->AddObject(new cHpBar("./image/ui/HpBar/p",
		dynamic_cast<cCastle*>(OBJECTMANAGER->GetObjectList(OBJ_CASTLE)->front())->hp,
		D3DXVECTOR2(289, WINSIZEY - 190)), OBJ_GUI);
	OBJECTMANAGER->AddObject(new cHpBar("./image/ui/HpBar/e",
		dynamic_cast<cCastle*>(OBJECTMANAGER->GetObjectList(OBJ_CASTLE)->back())->hp,
		D3DXVECTOR2(WINSIZEX + 70 - 723, WINSIZEY - 190)), OBJ_GUI);

	m_Time = IMAGEMANAGER->FindImage("Time");

	SOUNDMANAGER->pPlayBgm(1, 42000);

	MAPLOADER->DownloadEnemyObjs();
	MAPLOADER->DownloadPlayerObjs();

	FADE->FadeOut();
}

void cIngameScene::Update()
{
	TilePaint();

	OBJECTMANAGER->Update();
	GAMEMANAGER->Update();
}

void cIngameScene::Render()
{
	OBJECTMANAGER->Render();
	m_Time->CenterRender(WINSIZEX / 2, 50);

	TEXTMANAGER->drawNumber((int)GAMEMANAGER->GetTurnChangeTime(), 2, D3DXVECTOR2(WINSIZEX / 2 - 40, 80));
	TEXTMANAGER->drawNumber((int)GAMEMANAGER->GetPlayerScore(), 6, D3DXVECTOR2(WINSIZEX / 2 - 95, 110));
}

void cIngameScene::Release()
{
	OBJECTMANAGER->Reset();
	SOUNDMANAGER->pStopSound(1);
}
void cIngameScene::TilePaint()
{
	// 모든 타일의 선택 여부를 FALSE 로 해제
	m_tileMap->SetAllTilesOnUnitToFalse();
	m_enemyTileMap->SetAllTilesOnUnitToFalse();

	// itertor을 사용해서 타일맵과 오브젝트 간의 좌표를 계산한다

	for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_TILEMAPS))) {

		for (auto iter2 : (*OBJECTMANAGER->GetObjectList(OBJ_PLAYER_OBJ))) {

			// 좌표 일치 시
			if (iter->GetPos() == iter2->GetPos()) {

				// 오브젝트의 길이와 방향값을 얻어와

				for (int i = 0; i < dynamic_cast<cTileObject*>(iter2)->GetTileScale()->TileTotal; i++) {
					switch (dynamic_cast<cTileObject*>(iter2)->GetTileScale()->dir) {

						// 방향에 따라 그쪽 타일을 개수만큼 반복시켜서 선택여부를 TRUE 로 만든다

					case TileObjectInfo::DIR::right_top: {
						auto tile = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, -i);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::right_bottom: {
						auto tile = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), i, 0);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::left_right_bottom: {
						auto tile = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, i);
						if (tile)
							tile->SetOnUnit(true);
						tile = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), i, 0);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::left_top: {
						auto tile = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), -i, 0);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::left_bottom: {
						auto tile = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, i);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					} // 스위치 문 종료

				} // 타일 개수만큼 반복하는 for문

				  // 오브젝트의 길이와 방향값을 얻어와

				for (int i = 0; i < dynamic_cast<cTileObject*>(iter2)->GetTileScale()->TileTotal; i++) {
					switch (dynamic_cast<cTileObject*>(iter2)->GetTileScale()->dir) {

						// 방향에 따라 그쪽 타일을 개수만큼 반복시켜서 선택여부를 TRUE 로 만든다

					case TileObjectInfo::DIR::right_top: {
						auto tile = m_enemyTileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, -i);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::right_bottom: {
						auto tile = m_enemyTileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), i, 0);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::left_right_bottom: {
						auto tile = m_enemyTileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, i);
						if (tile)
							tile->SetOnUnit(true);
						tile = m_enemyTileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), i, 0);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::left_top: {
						auto tile = m_enemyTileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), -i, 0);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::left_bottom: {
						auto tile = m_enemyTileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, i);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}

					}// 스위치 문 종료

				} // 타일 개수만큼 반복하는 for문
			} // 타일의 좌표와 오브젝트의 좌표가 같은지 검사하는 if문

		} // 플레이어 오브젝트 iterator for 문

		for (auto iter2 : (*OBJECTMANAGER->GetObjectList(OBJ_ENEMY_OBJ))) {

			// 좌표 일치 시
			if (iter->GetPos() == iter2->GetPos()) {

				// 오브젝트의 길이와 방향값을 얻어와

				for (int i = 0; i < dynamic_cast<cTileObject*>(iter2)->GetTileScale()->TileTotal; i++) {
					switch (dynamic_cast<cTileObject*>(iter2)->GetTileScale()->dir) {

						// 방향에 따라 그쪽 타일을 개수만큼 반복시켜서 선택여부를 TRUE 로 만든다

					case TileObjectInfo::DIR::right_top: {
						auto tile = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, -i);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::right_bottom: {
						auto tile = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), i, 0);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::left_right_bottom: {
						auto tile = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, i);
						if (tile)
							tile->SetOnUnit(true);
						tile = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), i, 0);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::left_top: {
						auto tile = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), -i, 0);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::left_bottom: {
						auto tile = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, i);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					} // 스위치 문 종료

				} // 타일 개수만큼 반복하는 for문

				  // 오브젝트의 길이와 방향값을 얻어와

				for (int i = 0; i < dynamic_cast<cTileObject*>(iter2)->GetTileScale()->TileTotal; i++) {
					switch (dynamic_cast<cTileObject*>(iter2)->GetTileScale()->dir) {

						// 방향에 따라 그쪽 타일을 개수만큼 반복시켜서 선택여부를 TRUE 로 만든다

					case TileObjectInfo::DIR::right_top: {
						auto tile = m_enemyTileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, -i);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::right_bottom: {
						auto tile = m_enemyTileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), i, 0);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::left_right_bottom: {
						auto tile = m_enemyTileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, i);
						if (tile)
							tile->SetOnUnit(true);
						tile = m_enemyTileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), i, 0);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::left_top: {
						auto tile = m_enemyTileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), -i, 0);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}
					case TileObjectInfo::DIR::left_bottom: {
						auto tile = m_enemyTileMap->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, i);
						if (tile)
							tile->SetOnUnit(true);
						continue;
					}

					}// 스위치 문 종료

				} // 타일 개수만큼 반복하는 for문
			} // 타일의 좌표와 오브젝트의 좌표가 같은지 검사하는 if문

		} // 적 오브젝트 iterator for 문

	} // 맵 타일 iterator for 문
}