#include "DXUT.h"
#include "cTileObjectUnit.h"


#include "cTileMap.h"

cTileObjectUnit::cTileObjectUnit(float x, float y)
{
	t_info = new TileObjectInfo;

	info.m_pos.x = x;
	info.m_pos.y = y;

	m_image[0] = IMAGEMANAGER->FindImage("tileObject2_right_bottom");
	m_image[1] = IMAGEMANAGER->FindImage("tileObject2_right_top");
	
	t_info->TileTotal = 2;

	t_info->dir = TileObjectInfo::DIR::right_bottom;
}

cTileObjectUnit::cTileObjectUnit(float x, float y, int totalTile)
{
	t_info = new TileObjectInfo;

	info.m_pos.x = x;
	info.m_pos.y = y;

	m_image[0] = IMAGEMANAGER->FindImage("tileObject2_right_bottom");
	m_image[1] = IMAGEMANAGER->FindImage("tileObject2_right_top");

	t_info->TileTotal = totalTile;

	t_info->dir = TileObjectInfo::DIR::right_bottom;
}

cTileObjectUnit::cTileObjectUnit(float x, float y,const string & right_top, const string & right_bottom, int totalTile)
{
	t_info = new TileObjectInfo;

	info.m_pos.x = x;
	info.m_pos.y = y;

	m_image[0] = IMAGEMANAGER->FindImage(right_bottom);
	m_image[1] = IMAGEMANAGER->FindImage(right_top);

	t_info->TileTotal = totalTile;

	t_info->dir = TileObjectInfo::DIR::right_bottom;
}

cTileObjectUnit::cTileObjectUnit(float x, float y, const string & right_top, const string & right_bottom, int totalTile, int dir, D3DXVECTOR2 plusRenderPos)
{
	t_info = new TileObjectInfo;

	info.m_pos.x = x;
	info.m_pos.y = y;

	t_info->plusRenderPos = plusRenderPos;

	m_image[0] = IMAGEMANAGER->FindImage(right_bottom);
	m_image[1] = IMAGEMANAGER->FindImage(right_top);

	t_info->TileTotal = totalTile;
	t_info->dir = dir;
}


cTileObjectUnit::~cTileObjectUnit()
{
}

void cTileObjectUnit::Init()
{
	m_state = onMap;
	m_OnMouse = false;
}

void cTileObjectUnit::Update()
{
	MouseColision();

	if (m_OnMouse && GETKEY_DOWN(VK_RBUTTON)) {
		if (!INPUTMANAGER->GetMouseOnTile()) {
			m_state = onMouse;
			SOUNDMANAGER->pPlaySound(3);
			INPUTMANAGER->SetMouseOnTile(true);
		}
	}

	if (m_state == onMouse && GETKEY_DOWN(VK_LBUTTON)) {

		bool isCanDrop = true;

		for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_TILEMAPS))) {

			if (dynamic_cast<cTile*>(iter)->GetMouseDown()) {

				switch (t_info->dir) {

				case TileObjectInfo::DIR::right_bottom:
					for (int i = 0; i < t_info->TileTotal; i++) {
						if (cGameObject::info.m_objectTag == OBJ_PLAYER_OBJ) {
							auto tile = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->front())
								->GetSurroundTile(dynamic_cast<cTile*>(iter), i, 0);
							if (tile == nullptr) {
								isCanDrop = false;
							}
							else if (tile->GetOnUnit() == true)
							{
								isCanDrop = false;
							}
						}
						else if (cGameObject::info.m_objectTag == OBJ_ENEMY_OBJ) {
							auto tile = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->back())
								->GetSurroundTile(dynamic_cast<cTile*>(iter), i, 0);
							if (tile == nullptr) {
								isCanDrop = false;
							}
							else if (tile->GetOnUnit() == true)
							{
								isCanDrop = false;
							}
						}
					}
					break;

				case TileObjectInfo::DIR::right_top:
					for (int i = 0; i < t_info->TileTotal; i++) {
						if (cGameObject::info.m_objectTag == OBJ_PLAYER_OBJ) {
							auto tile = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->front())
								->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, -i);
							if (tile == nullptr) {
								isCanDrop = false;
							}
							else if (tile->GetOnUnit() == true)
							{
								isCanDrop = false;
							}
						}
						else if (cGameObject::info.m_objectTag == OBJ_ENEMY_OBJ) {
							auto tile = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->back())
								->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, -i);
							if (tile == nullptr) {
								isCanDrop = false;
							}
							else if (tile->GetOnUnit() == true)
							{
								isCanDrop = false;
							}
						}
					}
					break;

				case TileObjectInfo::DIR::left_right_bottom:
					for (int i = 0; i < t_info->TileTotal; i++) {
						if (cGameObject::info.m_objectTag == OBJ_PLAYER_OBJ) {
							auto tile = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->front())
								->GetSurroundTile(dynamic_cast<cTile*>(iter), i, 0);
							if (tile == nullptr) {
								isCanDrop = false;
							}
							else if (tile->GetOnUnit() == true)
							{
								isCanDrop = false;
							}
							tile = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->front())
								->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, i);
							if (tile == nullptr) {
								isCanDrop = false;
							}
							else if (tile->GetOnUnit() == true)
							{
								isCanDrop = false;
							}
						}
						else if (cGameObject::info.m_objectTag == OBJ_ENEMY_OBJ) {
							auto tile = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->back())
								->GetSurroundTile(dynamic_cast<cTile*>(iter), i, 0);
							if (tile == nullptr) {
								isCanDrop = false;
							}
							else if (tile->GetOnUnit() == true)
							{
								isCanDrop = false;
							}
							tile = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->back())
								->GetSurroundTile(dynamic_cast<cTile*>(iter), 0, i);
							if (tile == nullptr) {
								isCanDrop = false;
							}
							else if (tile->GetOnUnit() == true)
							{
								isCanDrop = false;
							}
						}
					}
					break;
				} // 스위치 문 종료
			}
		}

		if (isCanDrop) {
			if (INPUTMANAGER->GetMouseOnTile())
				INPUTMANAGER->SetMouseOnTile(false);
			m_state = onTile;

			bool is_d = false;
			if (cGameObject::info.m_objectTag == OBJ_PLAYER_OBJ) {
				auto tilemap = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->front());
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						if (dynamic_cast<cTile*>(tilemap->GetTileByXY(j, i))->GetMouseDown()) {
							is_d = true;
						}
					}
				}
			}
			else if (cGameObject::info.m_objectTag == OBJ_ENEMY_OBJ) {
				auto tilemap = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->back());
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						if (dynamic_cast<cTile*>(tilemap->GetTileByXY(j, i))->GetMouseDown()) {
							is_d = true;
						}
					}
				}
			}
			if (is_d == true) {
				info.m_pos = INPUTMANAGER->GetMouseOnTilePos();
				SOUNDMANAGER->pPlaySound(4);
			}
			else {
				m_state = onMouse;
			}
		}

	}

	if (m_state == onMouse && GETKEY_DOWN('R')) {
		SOUNDMANAGER->pPlaySound(3);
		if (t_info->dir == TileObjectInfo::DIR::right_bottom) {
			t_info->dir = TileObjectInfo::DIR::right_top;

		}
		else if (t_info->dir == TileObjectInfo::DIR::right_top) {
			t_info->dir = TileObjectInfo::DIR::right_bottom;
		}
	}

	if (m_state == onMouse) {
		info.m_pos.x = INPUTMANAGER->GetMousePos().x - 73.5;
		info.m_pos.y = INPUTMANAGER->GetMousePos().y - 12.25 - 12.25*(t_info->TileTotal - 1);
	}
}

void cTileObjectUnit::Render()
{
	if (t_info->dir == TileObjectInfo::DIR::right_bottom)
		if (t_info->TileTotal == 4)
			m_image[0]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y + t_info->plusRenderPos.y - 49, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));
		else 
			m_image[0]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y + t_info->plusRenderPos.y, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));

	else if (t_info->dir == TileObjectInfo::DIR::right_top) {
		if (t_info->TileTotal == 4) {
			if (m_state == onMouse)
				m_image[1]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y - 12.25 * (t_info->TileTotal - 1) + t_info->plusRenderPos.y, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));
			else
				m_image[1]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y - 24.5 * (t_info->TileTotal - 1) + t_info->plusRenderPos.y, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));
		}
		else {
			if (m_state == onMouse)
				m_image[1]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y - 12.25 * (t_info->TileTotal - 1) + t_info->plusRenderPos.y + 49, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));
			else
				m_image[1]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y - 24.5 * (t_info->TileTotal - 1) + t_info->plusRenderPos.y, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));
		}
	}
}

void cTileObjectUnit::Release()
{
	SAFE_DELETE(t_info);
}

void cTileObjectUnit::MouseColision()
{
	switch (t_info->dir) {
		// 오른쪽 아래
	case TileObjectInfo::DIR::right_bottom:
		for (int i = 0; i < t_info->TileTotal; i++) {
			if (CoillsionCheck_Mouse_Tile(D3DXVECTOR3(INPUTMANAGER->GetMousePos().x,
				INPUTMANAGER->GetMousePos().y, 0),
				D3DXVECTOR3(info.m_pos.x + 50 + i * 50, info.m_pos.y + 25 + 25 * i, 0),
				D3DXVECTOR3(75, 50, 0)))
			{
				m_OnMouse = true;
				return;
			}
			else
				m_OnMouse = false;
		}
		// 왼쪽 아래
		break;

	case TileObjectInfo::DIR::right_top:
		for (int i = 0; i < t_info->TileTotal; i++) {
			if (CoillsionCheck_Mouse_Tile(D3DXVECTOR3(INPUTMANAGER->GetMousePos().x,
				INPUTMANAGER->GetMousePos().y, 0),
				D3DXVECTOR3(info.m_pos.x + 50 + 50 * i, info.m_pos.y + 25 - 25 * i, 0),
				D3DXVECTOR3(75, 50, 0)))
			{
				m_OnMouse = true;
				return;
			}
			else
				m_OnMouse = false;
		}
		break;
	case TileObjectInfo::DIR::left_right_bottom:
		for (int i = 0; i < t_info->TileTotal; i++) {
			if (CoillsionCheck_Mouse_Tile(D3DXVECTOR3(INPUTMANAGER->GetMousePos().x,
				INPUTMANAGER->GetMousePos().y, 0),
				D3DXVECTOR3(info.m_pos.x + 50 + 50 * i, info.m_pos.y + 25 - 25 * i, 0),
				D3DXVECTOR3(75, 50, 0)) || 
				CoillsionCheck_Mouse_Tile(D3DXVECTOR3(INPUTMANAGER->GetMousePos().x,
					INPUTMANAGER->GetMousePos().y, 0),
					D3DXVECTOR3(info.m_pos.x + 50 + i * 50, info.m_pos.y + 25 + 25 * i, 0),
					D3DXVECTOR3(75, 50, 0)))
			{
				m_OnMouse = true;
				return;
			}
			else
				m_OnMouse = false;
		}
		break;
	}
}
