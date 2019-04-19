#include "DXUT.h"
#include "cShipPlaceScene.h"

#include "cTileObjectUnit.h"

#include "cTileMap.h"
#include "cTileObject.h"
#include "cViewPointMover.h"
#include "cScroolMap.h"


cShipPlaceScene::cShipPlaceScene()
{
}


cShipPlaceScene::~cShipPlaceScene()
{
}

void cShipPlaceScene::Init()
{
	OBJECTMANAGER->Reset();

	m_tileMap = dynamic_cast<cTileMap*>(OBJECTMANAGER->AddObject(new cTileMap(582, 395), OBJ_BOARD));

	OBJECTMANAGER->AddObject(new cScroolMap(IMAGEMANAGER->FindImage("placeMapScene")), OBJ_GAMEMAP);

	OBJECTMANAGER->AddObject(new cTileObjectUnit(WINSIZEX - 300, WINSIZEY / 2 - 200, "p2_up", "p2_down", 2, 0, D3DXVECTOR2(0, -35)), OBJ_PLAYER_OBJ);
	OBJECTMANAGER->AddObject(new cTileObjectUnit(WINSIZEX - 300, WINSIZEY / 2 - 100, "p2_up2", "p2_down2", 2, 0, D3DXVECTOR2(0, -49)), OBJ_PLAYER_OBJ);
	OBJECTMANAGER->AddObject(new cTileObjectUnit(WINSIZEX - 300, WINSIZEY / 2, "p3_up", "p3_down", 3, 0, D3DXVECTOR2(30, -49)), OBJ_PLAYER_OBJ);
	OBJECTMANAGER->AddObject(new cTileObjectUnit(WINSIZEX - 300, WINSIZEY / 2 + 100, "p3_up2", "p3_down2", 3, 0, D3DXVECTOR2(20, -59)), OBJ_PLAYER_OBJ);
	OBJECTMANAGER->AddObject(new cTileObjectUnit(WINSIZEX - 300, WINSIZEY / 2 + 200, "p4_up", "p4_down", 4, 0, D3DXVECTOR2(49, -24.5)), OBJ_PLAYER_OBJ);

	SOUNDMANAGER->pPlayBgm(5, 8000);

	m_changeScene = false;
	FADE->FadeOut();
}

void cShipPlaceScene::Update()
{
	TilePaint();

	if (GETKEY_DOWN(VK_RETURN)) {
		int count = 0;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {

				if (m_tileMap->GetTileByXY(j, i)->GetOnUnit())
					count++;
			}
		}
		if (count == 14) {
			m_changeScene = true;
			FADE->FadeIn();
		}
		else
			TIMER_STRING("Place all objects.", 1200, D3DXVECTOR2(WINSIZEX / 2 - 200, WINSIZEY / 2),50);
	}
	if(!m_changeScene)
	OBJECTMANAGER->Update();
	TileMouseDownSetting();

	if (m_changeScene && FADE->Finish())
	{
		for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_PLAYER_OBJ))) {
			iter->SetPos((iter)->GetPos().x + 15, iter->GetPos().y - 370);
		}

		RamdomEnemyUnitSetting();

		MAPLOADER->UploadTileObjects();
		SCENEMANAGER->ChangeScene("ingame");
	}
}

void cShipPlaceScene::Render()
{
	OBJECTMANAGER->Render();
	TEXTMANAGER->drawText("Place the Units [!]", D3DXVECTOR2(WINSIZEX / 2 - 200, 70), 50);
}

void cShipPlaceScene::Release()
{
	OBJECTMANAGER->Reset();
	m_tileMap = nullptr;
}

void cShipPlaceScene::TilePaint()
{
	// 모든 타일의 선택 여부를 FALSE 로 해제
	m_tileMap->SetAllTilesOnUnitToFalse();

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

			} // 타일의 좌표와 오브젝트의 좌표가 같은지 검사하는 if문

		} // 플레이어 오브젝트 iterator for 문
	} // 맵 타일 iterator for 문
}

void cShipPlaceScene::TileMouseDownSetting()
{
	bool flag = false;

	for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_TILEMAPS))) {
		if (dynamic_cast<cTile*>(iter)->GetMouseDown() == TRUE) {
			flag = true;
		}
	}

	if (!flag)
		return;

	for (auto iter1 : (*OBJECTMANAGER->GetObjectList(OBJ_PLAYER_OBJ))) {
		for (auto iter2 : (*OBJECTMANAGER->GetObjectList(OBJ_TILEMAPS))) {

			if (dynamic_cast<cTileObjectUnit*>(iter1)->GetOnMouse() == TRUE) {

				if (INPUTMANAGER->GetMouseOnTilePos() == iter2->GetPos()) {

					switch (dynamic_cast<cTileObjectUnit*>(iter1)->GetTileScale()->dir) {

					case TileObjectInfo::DIR::right_top:
						for (int i = 0; i < dynamic_cast<cTileObjectUnit*>(iter1)->GetTileScale()->TileTotal; i++) {
							auto tile_t = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter2), 0, -i);
							if (tile_t == nullptr)
								continue;
							tile_t->SetOnMouse(true);
						}
						continue;

					case TileObjectInfo::DIR::right_bottom:
						for (int i = 0; i < dynamic_cast<cTileObjectUnit*>(iter1)->GetTileScale()->TileTotal; i++) {
							auto tile_t = m_tileMap->GetSurroundTile(dynamic_cast<cTile*>(iter2), i, 0);
							if (tile_t == nullptr)
								continue;
							tile_t->SetOnMouse(true);
						}
						continue;
					}
				}
			}
		}
	}
}

void cShipPlaceScene::RamdomEnemyUnitSetting()
{
	cTileObjectUnit* objs[5];

	bool isFiled[10][10] = { false, };

	const int ReferencePointX = 3210;
	const int ReferencePointY = 25;

	int curInX = 0;
	int curInY = 0;

	bool re = false;

	curInX = RandomNumber(0, 9), curInY = RandomNumber(0, 9);
	objs[0] = dynamic_cast<cTileObjectUnit*>(OBJECTMANAGER->AddObject(
		new cTileObjectUnit(curInX, curInY,
			"e2_up", "e2_down", 2, RandomNumber(0, 1), D3DXVECTOR2(0, -35)), OBJ_ENEMY_OBJ));

	curInX = RandomNumber(0, 9), curInY = RandomNumber(0, 9);
	objs[1] = dynamic_cast<cTileObjectUnit*>(OBJECTMANAGER->AddObject(
		new cTileObjectUnit(curInX, curInY,
			"e2_up2", "e2_down2", 2, RandomNumber(0, 1), D3DXVECTOR2(0, -49)), OBJ_ENEMY_OBJ));

	curInX = RandomNumber(0, 9), curInY = RandomNumber(0, 9);
	objs[2] = dynamic_cast<cTileObjectUnit*>(OBJECTMANAGER->AddObject(
		new cTileObjectUnit(curInX, curInY,
			"e3_up", "e3_down", 3, RandomNumber(0, 1), D3DXVECTOR2(30, -49)), OBJ_ENEMY_OBJ));

	curInX = RandomNumber(0, 9), curInY = RandomNumber(0, 9);
	objs[3] = dynamic_cast<cTileObjectUnit*>(OBJECTMANAGER->AddObject(
		new cTileObjectUnit(curInX, curInY,
			"e3_up2", "e3_down2", 3, RandomNumber(0, 1), D3DXVECTOR2(20, -59)), OBJ_ENEMY_OBJ));

	curInX = RandomNumber(0, 9), curInY = RandomNumber(0, 9);
	objs[4] = dynamic_cast<cTileObjectUnit*>(OBJECTMANAGER->AddObject(
		new cTileObjectUnit(curInX, curInY,
			"e4_up", "e4_down", 4, RandomNumber(0, 1), D3DXVECTOR2(49,-24.5)), OBJ_ENEMY_OBJ));

	do {
		re = false;

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < objs[i]->GetTileScale()->TileTotal; j++) {
				if (objs[i]->GetTileScale()->dir == TileObjectInfo::DIR::right_top) {

					D3DXVECTOR2 pos;

					pos = objs[i]->GetPos() + D3DXVECTOR2(0, -j);

					if (pos.x > 9 || pos.x < 0)
						re = true;
					else if (pos.y > 9 || pos.y < 0)
						re = true;
					else if (isFiled[(int)pos.y][(int)pos.x] == true)
						re = true;
					else
						isFiled[(int)pos.y][(int)pos.x] = true;
				}
				else if (objs[i]->GetTileScale()->dir == TileObjectInfo::DIR::right_bottom) {

					D3DXVECTOR2 pos;

					pos = objs[i]->GetPos() + D3DXVECTOR2(j, 0);

					if (pos.x > 9 || pos.x < 0)
						re = true;
					else if (pos.y > 9 || pos.y < 0)
						re = true;
					else if (isFiled[(int)pos.y][(int)pos.x] == true)
						re = true;
					else
						isFiled[(int)pos.y][(int)pos.x] = true;
				}
			}
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				isFiled[i][j] = false;
			}
		}
		if (re) {
			for (int i = 0; i < 5; i++) {
				objs[i]->SetPos(RandomNumber(0, 9), RandomNumber(0, 9));
			}
		}
	} while (re);


	for (int i = 0; i < 5; i++) {
		objs[i]->SetPos(ReferencePointX + objs[i]->GetPos().x * 49 - objs[i]->GetPos().y * 49, ReferencePointY + objs[i]->GetPos().y * 24.5 + objs[i]->GetPos().x * 24.5);
	}
}