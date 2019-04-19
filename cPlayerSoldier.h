#pragma once
#include "cSoldier.h"
class cPlayerSoldier :
	public cSoldier
{
public:
	cPlayerSoldier(float x,float y);
	virtual ~cPlayerSoldier();

	virtual void Init() override;
	virtual void Update() override;
};

