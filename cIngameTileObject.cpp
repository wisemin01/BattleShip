#include "DXUT.h"
#include "cIngameTileObject.h"

#include "cTileObjectUnit.h"
#include "cTileMap.h"


cIngameTileObject::cIngameTileObject()
{
	t_info = new TileObjectInfo;

	t_info->dir = 0;
	t_info->TileTotal = 1;

	info.m_pos = D3DXVECTOR2(0, 0);
	info.m_color = D3DCOLOR_ARGB(255, 255, 255, 255);
	info.m_size = 1.0;
}

cIngameTileObject::cIngameTileObject(cTileObject * obj)
{
	t_info = new TileObjectInfo;

	t_info->dir = obj->GetTileScale()->dir;
	t_info->TileTotal = obj->GetTileScale()->TileTotal;

	t_info->plusRenderPos = obj->GetTileScale()->plusRenderPos;

	info.m_pos = obj->GetObjectInfo().m_pos;
	info.m_color = obj->GetObjectInfo().m_color;
	info.m_objectTag = obj->GetObjectInfo().m_objectTag;
	info.m_size = obj->GetObjectInfo().m_size;

	m_image[0] = dynamic_cast<cTileObjectUnit*>(obj)->Get_RightBottom_Image();
	m_image[1] = dynamic_cast<cTileObjectUnit*>(obj)->Get_RightTop_Image();
}

cIngameTileObject::cIngameTileObject(cIngameTileObject * obj)
{
	t_info = new TileObjectInfo;

	t_info->dir = obj->GetTileScale()->dir;
	t_info->TileTotal = obj->GetTileScale()->TileTotal;

	t_info->plusRenderPos = obj->GetTileScale()->plusRenderPos;

	info.m_pos = obj->GetObjectInfo().m_pos;
	info.m_color = obj->GetObjectInfo().m_color;
	info.m_objectTag = obj->GetObjectInfo().m_objectTag;
	info.m_size = obj->GetObjectInfo().m_size;

	m_image[0] = dynamic_cast<cIngameTileObject*>(obj)->Get_RightBottom_Image();
	m_image[1] = dynamic_cast<cIngameTileObject*>(obj)->Get_RightTop_Image();
}


cIngameTileObject::~cIngameTileObject()
{
}

void cIngameTileObject::Init()
{
}

void cIngameTileObject::Update()
{
	DestroyCheck();
}

void cIngameTileObject::Render()
{
	if (info.m_objectTag == OBJ_PLAYER_OBJ) {
		PlayerRender();
	}
	else if (info.m_objectTag == OBJ_ENEMY_OBJ) {
		EnemyRender();
	}
}

void cIngameTileObject::Release()
{
	SAFE_DELETE(t_info);
}

void cIngameTileObject::MouseColision()
{
}

void cIngameTileObject::DestroyCheck()
{
	if (info.m_objectTag == OBJ_PLAYER_OBJ) {
		auto PlayerTileMap = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->front())->GetMapTile();
		cTile* pivotTile;

		for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_TILEMAPS))) {
			if (iter->GetObjectInfo().m_pos == info.m_pos) {
				pivotTile = dynamic_cast<cTile*>(iter);
			}
		}
		m_isDestroy = true;
		for (int i = 0; i < t_info->TileTotal; i++) {
			switch (t_info->dir) {
			case TileObjectInfo::DIR::right_top:
				if (!PlayerTileMap[pivotTile->GetArrayYPos() - i][pivotTile->GetArrayXPos()]->GetIsDestroy()) {
					m_isDestroy = false;
				}
				break;
			case TileObjectInfo::DIR::right_bottom:
				if (!PlayerTileMap[pivotTile->GetArrayYPos()][pivotTile->GetArrayXPos() + i]->GetIsDestroy()) {
					m_isDestroy = false;
				}
				break;
			}
		}
	}
	else if (info.m_objectTag == OBJ_ENEMY_OBJ) {
		auto EnemyTileMap = dynamic_cast<cTileMap*>(OBJECTMANAGER->GetObjectList(OBJ_BOARD)->back())->GetMapTile();
		cTile* pivotTile;

		for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_TILEMAPS))) {
			if (iter->GetObjectInfo().m_pos == info.m_pos) {
				pivotTile = dynamic_cast<cTile*>(iter);
			}
		}
		m_isDestroy = true;
		for (int i = 0; i < t_info->TileTotal; i++) {
			switch (t_info->dir) {
			case TileObjectInfo::DIR::right_top:
				if (!EnemyTileMap[pivotTile->GetArrayYPos() - i][pivotTile->GetArrayXPos()]->GetIsDestroy()) {
					m_isDestroy = false;
				}
				break;
			case TileObjectInfo::DIR::right_bottom:
				if (!EnemyTileMap[pivotTile->GetArrayYPos()][pivotTile->GetArrayXPos() + i]->GetIsDestroy()) {
					m_isDestroy = false;
				}
				break;
			}
		}
	}
}

void cIngameTileObject::PlayerRender()
{
	if (t_info->TileTotal == 4) {
		if (t_info->dir == TileObjectInfo::DIR::right_bottom)
			m_image[0]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y + t_info->plusRenderPos.y - 49, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));
		else if (t_info->dir == TileObjectInfo::DIR::right_top) {
			m_image[1]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y - 24.5 * (t_info->TileTotal - 1) + t_info->plusRenderPos.y, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));
		}
	}
	else {
		if (t_info->dir == TileObjectInfo::DIR::right_bottom)
			m_image[0]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y + t_info->plusRenderPos.y, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));
		else if (t_info->dir == TileObjectInfo::DIR::right_top) {
			m_image[1]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y - 24.5 * (t_info->TileTotal - 1) + t_info->plusRenderPos.y, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));
		}
	}
}

void cIngameTileObject::EnemyRender()
{
	if (m_isDestroy) {
		if (t_info->TileTotal == 4) {
			if (t_info->dir == TileObjectInfo::DIR::right_bottom)
				m_image[0]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y + t_info->plusRenderPos.y - 49, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));
			else if (t_info->dir == TileObjectInfo::DIR::right_top) {
				m_image[1]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y - 24.5 * (t_info->TileTotal - 1) + t_info->plusRenderPos.y, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));
			}
		}
		else {
			if (t_info->dir == TileObjectInfo::DIR::right_bottom)
				m_image[0]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y + t_info->plusRenderPos.y, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));
			else if (t_info->dir == TileObjectInfo::DIR::right_top) {
				m_image[1]->Render(info.m_pos.x + t_info->plusRenderPos.x, info.m_pos.y - 24.5 * (t_info->TileTotal - 1) + t_info->plusRenderPos.y, 1.0, 0, D3DCOLOR_ARGB(200, 255, 255, 255));
			}
		}
	}
}
