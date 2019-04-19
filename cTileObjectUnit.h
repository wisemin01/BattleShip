#pragma once
#include "cTileObject.h"

class cTileObjectUnit :
	public cTileObject
{
private:
	enum {
		onTile,
		onMap,
		onMouse
	};

	texture * m_image[2];
	INT m_state;
	BOOL m_OnMouse;
public:
	cTileObjectUnit(float x,float y);
	cTileObjectUnit(float x, float y, int totalTile);
	cTileObjectUnit(float x, float y,const string & right_top, const string & right_bottom, int totalTile);
	cTileObjectUnit(float x, float y, const string & right_top, const string & right_bottom, int totalTile, int dir,D3DXVECTOR2 plusRenderPos = D3DXVECTOR2(0,0));

	virtual ~cTileObjectUnit();

	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

	virtual void MouseColision() override;

	virtual TileObjectInfo* GetTileScale() override { return t_info; }

	texture* Get_RightBottom_Image() { return m_image[0]; }
	texture* Get_RightTop_Image() { return m_image[1]; }

	BOOL GetOnMouse() {return m_OnMouse;}
	void SetOnMouse(bool b) { m_OnMouse = b; }
};

