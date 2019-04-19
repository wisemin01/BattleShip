#include "DXUT.h"
#include "cButton.h"


cButton::cButton(D3DXVECTOR2 pos, texture * OnMouseImg, texture * OffMouseImg, void(*pFunc)())
{
	OnMouseTexture = OnMouseImg;
	OffMouseTexture = OffMouseImg;

	m_buttonState = false;

	m_fuction = pFunc;

	info.m_pos = pos;
	m_delay = 0;
}

cButton::~cButton()
{
}

void cButton::Init()
{
	info.m_collider.left = info.m_pos.x - 234.5;
	info.m_collider.right = info.m_pos.x + 234.5;
	info.m_collider.top = info.m_pos.y - 82;
	info.m_collider.bottom = info.m_pos.y + 82;
}

void cButton::Update()
{
	if (nIntersectRectToPoint(info.m_collider, INPUTMANAGER->GetMousePos())) {
		m_buttonState = true;
		if (m_delay < g_nowTime) {
			if (GETKEY_DOWN(VK_LBUTTON)) {
				SOUNDMANAGER->pPlaySound(4);
				m_fuction();
				m_delay = g_nowTime + 100;
			}
		}
	}
	else
		m_buttonState = false;
}

void cButton::Render()
{
	if (m_buttonState)
		OnMouseTexture->CenterRender(info.m_pos.x, info.m_pos.y);
	else
		OffMouseTexture->CenterRender(info.m_pos.x, info.m_pos.y);
}

void cButton::Release()
{
}
