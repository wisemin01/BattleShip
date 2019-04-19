#pragma once
#include "cGameObject.h"
class cHpBar :
	public cGameObject
{
private:
	cAnimation * m_hpbar;
	int &hp;
public:
	cHpBar(const string& path,int& hp,D3DXVECTOR2 pos);
	virtual ~cHpBar();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	
};

