#pragma once
#include "cGameObject.h"
class cSoldier :
	public cGameObject
{
public:
	enum soldier_state {
		e_attack,
		e_death,
		e_walk,
		e_win,
		e_lose
	};
protected:
	cAnimation * m_attack;
	cAnimation * m_death;
	cAnimation * m_walk;
	cAnimation * m_win;
	cAnimation * m_lose;

	INT m_soldierState;

	DWORD m_CheeringTime;
	DWORD m_SadTime;
	DWORD m_DyingMin;
	INT m_DyingTime;

	BOOL isCollision;
public:
	cSoldier();
	virtual ~cSoldier();

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() override;
	virtual void Release() override;

	virtual void AssistUpdate();

	void SetSoldierState(INT newState);
	INT GetSoldierState() { return m_soldierState; }
	void SetCheeringTime(DWORD time) { m_CheeringTime = time; }
	void SetSadTime(DWORD time) { m_SadTime = time; }
	void SetCollision(bool b) { isCollision = b; }
	BOOL GetCollision() { return isCollision; }
};

