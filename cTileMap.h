#pragma once
#include "cGameObject.h"

//-----------------------------------------------------------------
// class cTile
//-----------------------------------------------------------------

class cTile : public cGameObject {
private:
	cAnimation * m_frames;

	INT ArrayXPos;
	INT ArrayYPos;

	bool m_down;
	bool m_onUnit;
	bool m_MouseChick;
	bool m_destroys;
public:
	cTile();
	cTile(cTile* tile);
	cTile(float x, float y);

	virtual ~cTile();

	virtual void Init	() override;
	virtual void Update	() override;
	virtual void Render	() override;
	virtual void Release() override;

	bool IsOnMouse();

	void SetOnUnit(bool flag) { m_onUnit = flag; }
	void SetOnMouse(bool flag) { m_down = flag; }
	void SetDestroy(bool b);
	void SetArrayPos(INT x, INT y) { ArrayXPos = x; ArrayYPos = y; }
	
	BOOL GetOnUnit() { return m_onUnit; }
	BOOL GetMouseDown() { return m_down; }
	BOOL GetIsDestroy() { return m_destroys; }

	INT GetArrayXPos() { return ArrayXPos; }
	INT GetArrayYPos() { return ArrayYPos; }
};

//-----------------------------------------------------------------
// class cTileMap
//-----------------------------------------------------------------

class cTileMap :
	public cGameObject
{
private:
	cTile * m_mapTiles[10][10];
public:
	cTileMap(float x = 0,float y = 0);
	virtual ~cTileMap();

	virtual void Init	() override;
	virtual void Update	() override;
	virtual void Render	() override;
	virtual void Release() override;

	// 주위 타일을 얻어옴
	cTile* GetSurroundTile(cTile* tile, int x, int y);
	cTile* GetTileByXY(int x, int y);
	cTile * (*GetMapTile(void))[10]	{ return m_mapTiles; }
	// 모든 타일을 선택 해제 상태로 만듬
	void SetAllTilesOnUnitToFalse();
};

