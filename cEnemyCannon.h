#pragma once
#include "cCannon.h"
class cEnemyCannon :
	public cCannon
{
private:
	enum AISEARCH {
		E_NOSEARCH,
		E_BOTTOM,
		E_LEFT,
		E_TOP,
		E_RIGHT
	};
	enum AISEARCHMODE {
		E_HUNT,
		E_TARGET
	};
private:
	cTile * m_pivotTile;
	cTile * m_nowTile;

	INT m_AIMode;
	INT m_TargetDir;

	BOOL  m_prevAttack;
	DWORD m_AttackTime;
public:
	cEnemyCannon();
	virtual ~cEnemyCannon();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void Attack();

	void HuntAttack();
	void TargetAttack();

	virtual void CannonShoot(D3DXVECTOR2 startPos) override;
	virtual bool Shot() override;
};

