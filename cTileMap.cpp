#include "DXUT.h"
#include "cTileMap.h"

#include "cTileSmoke.h"

//-----------------------------------------------------------------
// class cTile - public cGameObject
//-----------------------------------------------------------------

cTile::cTile()
	:cGameObject()
{
}

cTile::cTile(cTile * tile)
{
	info.m_pos.x = tile->info.m_pos.x;
	info.m_pos.y = tile->info.m_pos.y;
}

cTile::cTile(float x, float y)
	:cGameObject(x, y)
{
}

cTile::~cTile()
{
}

void cTile::Init()
{
	m_frames = new cAnimation("./image/tiles/tile", 6, 50);
	m_down = false;
	m_onUnit = false;
	m_MouseChick = false;
	m_destroys = false;
}

void cTile::Update()
{
	m_frames->Update();

	if (CoillsionCheck_Mouse_Tile(D3DXVECTOR3(INPUTMANAGER->GetMousePos().x,
		INPUTMANAGER->GetMousePos().y, 0),
		D3DXVECTOR3(info.m_pos.x + 50, info.m_pos.y + 25, 0),
		D3DXVECTOR3(75, 50, 0))) {
		INPUTMANAGER->SetMouseOnTilePos(info.m_pos);
		m_down = true;
	}
	else m_down = false;

	if (GETKEY_RETAIN(VK_LBUTTON) || GETKEY_RETAIN(VK_RBUTTON))
		m_MouseChick = true;
	else m_MouseChick = false;
}

void cTile::Render()
{
	if (m_down) {
		if (m_MouseChick)
			m_frames->FrameRender(info.m_pos.x, info.m_pos.y, 2, info.m_size, 0.0, info.m_color);
		else
			m_frames->FrameRender(info.m_pos.x, info.m_pos.y, 1, info.m_size, 0.0, info.m_color);
	}
	else
		m_frames->FrameRender(info.m_pos.x, info.m_pos.y, 0, info.m_size, 0.0, info.m_color);
	//if (m_onUnit) {
	//	m_frames->FrameRender(info.m_pos.x, info.m_pos.y, 3, info.m_size, 0.0, info.m_color);
	//}
	if (m_destroys == true) {
		m_frames->FrameRender(info.m_pos.x, info.m_pos.y, 4, info.m_size, 0.0, info.m_color);
		if (m_onUnit == true) {
			m_frames->FrameRender(info.m_pos.x, info.m_pos.y, 5, info.m_size, 0.0, info.m_color);
		}
	}
}

void cTile::Release()
{
	SAFE_DELETE(m_frames);
}

bool cTile::IsOnMouse()
{
	if (INPUTMANAGER->GetMousePos().x > info.m_collider.left &&
		INPUTMANAGER->GetMousePos().y > info.m_collider.top &&
		INPUTMANAGER->GetMousePos().x < info.m_collider.right &&
		INPUTMANAGER->GetMousePos().y < info.m_collider.bottom)
		return true;
	else
		return false;
}

void cTile::SetDestroy(bool b)
{
	if (m_onUnit)
		OBJECTMANAGER->AddObject(new cTileSmoke(info.m_pos.x, info.m_pos.y - 160), OBJ_EFFECT);
	m_destroys = b;
}


//-----------------------------------------------------------------
// class cTileMap - public cGameObject
//-----------------------------------------------------------------

cTileMap::cTileMap(float x,float y)
	:cGameObject(x,y)
{
}


cTileMap::~cTileMap()
{
}

void cTileMap::Init()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			D3DXVECTOR2 pos;
			pos.x = info.m_pos.x - i * 49 + j * 49;
			pos.y = info.m_pos.y + i * 24.5 + j * 24.5;

			m_mapTiles[i][j] = dynamic_cast<cTile*>(OBJECTMANAGER->AddObject(
				new cTile(pos.x, pos.y), OBJ_TILEMAPS));
			m_mapTiles[i][j]->SetArrayPos(j, i);
		}
	}
}

void cTileMap::Update()
{
}

void cTileMap::Render()
{
}

void cTileMap::Release()
{
}

cTile * cTileMap::GetSurroundTile(cTile * tile, int x, int y)
{
	POINT tilePosition;

	if (tile == nullptr)
		return nullptr;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (m_mapTiles[i][j] == tile) {
				tilePosition.x = j;
				tilePosition.y = i;
			}
		}
	}

	if (tilePosition.y + y >= 10)
		return nullptr;
	if (tilePosition.y + y < 0)
		return nullptr;
	if (tilePosition.x + x >= 10)
		return nullptr;
	if (tilePosition.x + x < 0)
		return nullptr;

	return m_mapTiles[tilePosition.y + y][tilePosition.x + x];
}

cTile * cTileMap::GetTileByXY(int x, int y)
{
	return m_mapTiles[y][x];
}

void cTileMap::SetAllTilesOnUnitToFalse()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			m_mapTiles[i][j]->SetOnUnit(false);
		}
	}

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------