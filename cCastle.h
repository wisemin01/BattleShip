#pragma once
#include "cGameObject.h"
class cCastle abstract:
	public cGameObject
{
protected:
	texture * m_castleImage;
	DWORD m_spawnTime;

public:
	cCastle(D3DXVECTOR2 pos);
	virtual ~cCastle();

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

	virtual void HPUpdate();

	INT hp;
};

