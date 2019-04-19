#pragma once
#include "singleton.h"

struct texture {
	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;

	texture(LPDIRECT3DTEXTURE9 texturePtr, D3DXIMAGE_INFO info)
	: texturePtr(texturePtr),info(info) {}

	void Render(float x, float y, float size = 1.0, float rot = 0.0, D3DXCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void RectRender(RECT rc, float x, float y, float size, float rot, D3DXCOLOR color);
	void CenterRender(float x, float y, float size = 1.0, float rot = 0.0, D3DXCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
};

class cImageManager :
	public singleton<cImageManager>
{
private:
	LPD3DXSPRITE m_sprite;
	map<string, texture*> m_images;
public:
	cImageManager();
	~cImageManager();

	void Render			(texture* texturePtr, float x, float y, float size, float rot, D3DXCOLOR color);
	void RectRender		(texture* texturePtr, RECT rc, float x, float y, float size, float rot, D3DXCOLOR color);
	void CenterRender	(texture* texturePtr, float x, float y, float size, float rot, D3DXCOLOR color);

	texture* AddImage	(const string & key, const string & path);
	texture* FindImage	(const string & key);

	void Begin();
	void End();

	LPD3DXSPRITE& GetM_Sprite() { return m_sprite; }

	void OnResetDevice() { m_sprite->OnResetDevice(); }
	void OnLostDevice() { m_sprite->OnLostDevice(); }

public:
	// 경로 , 총 프레임 수
	void AddAnimation(const string& path, int totalFrame);
	void AddAnimationVer2(const string& path, int totalFrame);
};

#define IMAGEMANAGER cImageManager::GetInstance()

