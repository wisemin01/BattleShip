#pragma once
#include "cGameObject.h"
class cButton :
	public cGameObject
{
private:
	texture * OnMouseTexture;
	texture * OffMouseTexture;

	BOOL m_buttonState;

	DWORD m_delay;

	void(*m_fuction)();
public:
	cButton(D3DXVECTOR2 pos, texture* OnMouseImg, texture* OffMouseImg, void(*pFunc)());
	virtual ~cButton();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

};

