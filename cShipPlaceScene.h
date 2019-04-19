#pragma once
#include "cScene.h"

class cTileMap;

class cShipPlaceScene :
	public cScene
{
private:
	cTileMap * m_tileMap;
	cTileMap * m_enemytileMap;

	BOOL	   m_changeScene;
public:
	cShipPlaceScene();
	~cShipPlaceScene();

	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

	void TilePaint();
	void TileMouseDownSetting();

	void RamdomEnemyUnitSetting();
};

