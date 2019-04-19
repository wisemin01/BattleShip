#pragma once
#include "cSoldier.h"
class cEnemySoldier :
	public cSoldier
{
public:
	cEnemySoldier(float x,float y);
	virtual ~cEnemySoldier();

	virtual void Init() override;
	virtual void Update() override;
};

