#pragma once
class cAnimation
{
private:
	vector<texture*> m_images;

	INT m_totalFrames;
	INT m_nowFrame;

	DWORD m_changeTime;
	DWORD m_nowChangeTimeCur;
public:
	cAnimation(const string & path, int totalFrames, float switchingTime, bool flag = false);
	virtual ~cAnimation();

	void Update();
	
	void Render(float x, float y, float size = 1.0, float rot = 0.0, D3DXCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRender(float x, float y, float size = 1.0, float rot = 0.0, D3DXCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void FrameRender(float x, float y, int renderFrame, float size = 1.0, float rot = 0.0, D3DXCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterFrameRender(float x, float y, int renderFrame, float size = 1.0, float rot = 0.0, D3DXCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void RectRender(float x, float y, RECT rc, float size = 1.0, float rot = 0.0, D3DXCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

	void SetFrame(INT frame) {
		m_nowFrame = frame;
	}
};