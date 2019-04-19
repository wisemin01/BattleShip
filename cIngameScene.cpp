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
	// ��� Ÿ���� ���� ���θ� FALSE �� ����
	m_tileMap->SetAllTilesOnUnitToFalse();
	m_enemyTileMap->SetAllTilesOnUnitToFalse();

	// itertor�� ����ؼ� Ÿ�ϸʰ� ������Ʈ ���� ��ǥ�� ����Ѵ�

	for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_TILEMAPS))) {

		for (auto iter2 : (*OBJECTMANAGER->GetObjectList(OBJ_PLAYER_OBJ))) {

			// ��ǥ ��ġ ��
			if (iter->GetPos() == iter2->GetPos()) {

				// ������Ʈ�� ���̿� ���Ⱚ�� ����

				for (int i = 0; i < dynamic_cast<cTileObject*>(iter2)->GetTileScale()->TileTotal; i++) {
					switch (dynamic_cast<cTileObject*>(iter2)->GetTileScale()->dir) {

						// ���⿡ ���� ���� Ÿ���� ������ŭ �ݺ����Ѽ� ���ÿ��θ� TRUE �� �����

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
					} // ����ġ �� ����

				} // Ÿ�� ������ŭ �ݺ��ϴ� for��

				  // ������Ʈ�� ���̿� ���Ⱚ�� ����

				for (int i = 0; i < dynamic_cast<cTileObject*>(iter2)->GetTileScale()->TileTotal; i++) {
					switch (dynamic_cast<cTileObject*>(iter2)->GetTileScale()->dir) {

						// ���⿡ ���� ���� Ÿ���� ������ŭ �ݺ����Ѽ� ���ÿ��θ� TRUE �� �����

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

					}// ����ġ �� ����

				} // Ÿ�� ������ŭ �ݺ��ϴ� for��
			} // Ÿ���� ��ǥ�� ������Ʈ�� ��ǥ�� ������ �˻��ϴ� if��

		} // �÷��̾� ������Ʈ iterator for ��

		for (auto iter2 : (*OBJECTMANAGER->GetObjectList(OBJ_ENEMY_OBJ))) {

			// ��ǥ ��ġ ��
			if (iter->GetPos() == iter2->GetPos()) {

				// ������Ʈ�� ���̿� ���Ⱚ�� ����

				for (int i = 0; i < dynamic_cast<cTileObject*>(iter2)->GetTileScale()->TileTotal; i++) {
					switch (dynamic_cast<cTileObject*>(iter2)->GetTileScale()->dir) {

						// ���⿡ ���� ���� Ÿ���� ������ŭ �ݺ����Ѽ� ���ÿ��θ� TRUE �� �����

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
					} // ����ġ �� ����

				} // Ÿ�� ������ŭ �ݺ��ϴ� for��

				  // ������Ʈ�� ���̿� ���Ⱚ�� ����

				for (int i = 0; i < dynamic_cast<cTileObject*>(iter2)->GetTileScale()->TileTotal; i++) {
					switch (dynamic_cast<cTileObject*>(iter2)->GetTileScale()->dir) {

						// ���⿡ ���� ���� Ÿ���� ������ŭ �ݺ����Ѽ� ���ÿ��θ� TRUE �� �����

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

					}// ����ġ �� ����

				} // Ÿ�� ������ŭ �ݺ��ϴ� for��
			} // Ÿ���� ��ǥ�� ������Ʈ�� ��ǥ�� ������ �˻��ϴ� if��

		} // �� ������Ʈ iterator for ��

	} // �� Ÿ�� iterator for ��
}