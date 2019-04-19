#pragma once
#include "cGameObject.h"
class cCannon :
	public cGameObject
{
public:
	cCannon();
	virtual ~cCannon();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual void CannonShoot(D3DXVECTOR2 startPos) PURE;
	virtual bool Shot() PURE;
};

