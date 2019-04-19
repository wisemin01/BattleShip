#include "DXUT.h"
#include "cAnimation.h"


cAnimation::cAnimation(const string & path, int totalFrames, float switchingTime,bool flag)
	:m_totalFrames(totalFrames), m_nowFrame(0), m_changeTime(switchingTime)
{
	if (!flag) {
		for (int i = 0; i < totalFrames; i++) {
			string str = (path + to_string(i)) + ".png";
			m_images.push_back(IMAGEMANAGER->FindImage(str));
		}
	}
	else {
		for (int i = 0; i < totalFrames; i++) {
			string str = path + (i < 10 ? "0" : "");
			str += to_string(i) + ".png";
			m_images.push_back(IMAGEMANAGER->FindImage(str));
		}
	}
	m_nowChangeTimeCur = g_nowTime;
}

cAnimation::~cAnimation()
{
	m_images.clear();
}

void cAnimation::Update()
{
	if (m_nowChangeTimeCur < g_nowTime) {

		m_nowFrame++;
		m_nowChangeTimeCur = g_nowTime + m_changeTime;

		if (m_nowFrame >= m_totalFrames) {
			m_nowFrame = 0;
		}
	}
}

void cAnimation::Render(float x, float y, float size, float rot, D3DXCOLOR color)
{
	m_images[m_nowFrame]->Render(x, y, size, rot, color);
}

void cAnimation::CenterRender(float x, float y, float size, float rot, D3DXCOLOR color)
{
	m_images[m_nowFrame]->CenterRender(x, y, size, rot, color);
}

void cAnimation::FrameRender(float x, float y, int renderFrame, float size, float rot, D3DXCOLOR color)
{
	m_images[renderFrame]->Render(x, y, size, rot, color);
}

void cAnimation::CenterFrameRender(float x, float y, int renderFrame, float size, float rot, D3DXCOLOR color)
{
	m_images[renderFrame]->CenterRender(x, y, size, rot, color);
}

void cAnimation::RectRender(float x, float y, RECT rc, float size, float rot, D3DXCOLOR color)
{
	m_images[m_nowFrame]->RectRender(rc, x, y, size, rot, color);
}
