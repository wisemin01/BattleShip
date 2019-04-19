#pragma once
#include "cGameObject.h"

struct TileObjectInfo {
	enum DIR{
		right_bottom,
		right_top,
		left_bottom,
		left_top,
		left_right_bottom
	};

	int TileTotal;
	int dir;
	int dir02;

	D3DXVECTOR2 plusRenderPos;

	TileObjectInfo() { dir02 = dir; }
};

class cTileObject :
	public cGameObject
{
protected:
	TileObjectInfo* t_info;
public:
	cTileObject();
	virtual ~cTileObject();

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

	virtual void MouseColision() PURE;

	virtual TileObjectInfo* GetTileScale() PURE;
};

