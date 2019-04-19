#pragma once
#include "cCannon.h"
class cPlayerCannon :
	public cCannon
{
public:
	cPlayerCannon();
	virtual ~cPlayerCannon();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual void CannonShoot(D3DXVECTOR2 startPos) override;
	virtual bool Shot() override;
};

