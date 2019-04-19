#pragma once
#include "cGameObject.h"
class cTileSmoke :
	public cGameObject
{
private:
	cAnimation * m_smoke;
public:
	cTileSmoke(float x,float y);
	~cTileSmoke();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

};

