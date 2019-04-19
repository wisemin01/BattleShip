#pragma once
#include "cScene.h"

class cTileMap;

class cImageUI;

class cIngameScene :
	public cScene
{
private:
	cTileMap * m_tileMap;
	cTileMap * m_enemyTileMap;

	cImageUI * imageUI1;
	cImageUI * imageUI2;

	texture* m_Time;

	BOOL	m_changeScene;
public:
	cIngameScene();
	~cIngameScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void TilePaint();
};

