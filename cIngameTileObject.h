#pragma once
#include "cTileObject.h"
class cIngameTileObject :
	public cTileObject
{
private:
	texture* m_image[2];
	bool m_isDestroy;
public:
	cIngameTileObject();
	cIngameTileObject(cTileObject* obj);
	cIngameTileObject(cIngameTileObject* obj);
	virtual ~cIngameTileObject();

	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

	virtual void MouseColision() override;
	void DestroyCheck();

	void PlayerRender();
	void EnemyRender();

	virtual TileObjectInfo* GetTileScale() override { return t_info; }

	texture* Get_RightBottom_Image() { return m_image[0]; }
	texture* Get_RightTop_Image() { return m_image[1]; }
};

