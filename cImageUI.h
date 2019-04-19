#pragma once
#include "cGameObject.h"
class cImageUI :
	public cGameObject
{
private:
	texture * m_image;
	bool IsCenterRender;
	bool IsRender;

	DWORD m_destoyTime;
public:
	cImageUI(texture* text, D3DXVECTOR2 pos, bool flag = false, DWORD DestroyTime = 0);
	virtual ~cImageUI();

	virtual void Init()	override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

	void SetIsRender(bool b) { IsRender = b; }
};

