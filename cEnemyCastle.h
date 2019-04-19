#pragma once
#include "cCastle.h"

class cImageUI;
class cEnemyCastle :
	public cCastle
{
private:
	cImageUI * m_imageUI;
	BOOL isCreate;
	BOOL isCreate2;
public:
	cEnemyCastle(D3DXVECTOR2 pos);
	virtual ~cEnemyCastle();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual void HPUpdate() override;
};

