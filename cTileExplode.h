#pragma once
#include "cGameObject.h"
class cTileExplode :
	public cGameObject
{
private:
	cAnimation * m_explode;
	DWORD m_MaintenanceTime;
public:
	cTileExplode(float x, float y, DWORD MaintenanceTime = 350);
	virtual ~cTileExplode();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

};

