#include "DXUT.h"
#include "cImageManager.h"

//---------------------------------------------------------------------------
// struct texture - definition
//---------------------------------------------------------------------------

void texture::Render(float x, float y, float size, float rot, D3DXCOLOR color)
{
	IMAGEMANAGER->Render(this, x, y, size, rot, color);
}

void texture::RectRender(RECT rc, float x, float y, float size, float rot, D3DXCOLOR color)
{
	IMAGEMANAGER->RectRender(this, rc, x, y, size, rot, color);
}

void texture::CenterRender(float x, float y, float size, float rot, D3DXCOLOR color)
{
	IMAGEMANAGER->CenterRender(this, x, y, size, rot, color);
}

//---------------------------------------------------------------------------
// class cImageManager - definition
//---------------------------------------------------------------------------


cImageManager::cImageManager()
{
	D3DXCreateSprite(g_device, &m_sprite);
}


cImageManager::~cImageManager()
{
	for (auto iter : m_images) {
		SAFE_RELEASE(iter.second->texturePtr);
		SAFE_DELETE(iter.second);
	}

	m_images.clear();
	m_sprite->Release();
}

void cImageManager::Render(texture * texturePtr, float x, float y, float size, float rot, D3DXCOLOR color)
{
	if (texturePtr) {
		D3DXMATRIXA16 mat;
		D3DXMatrixAffineTransformation2D(&mat, size, 0, rot, &D3DXVECTOR2(x, y));
		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, color);
	}
}

void cImageManager::RectRender(texture * texturePtr, RECT rc, float x, float y, float size, float rot, D3DXCOLOR color)
{
	if (texturePtr) {
		D3DXMATRIXA16 mat;
		D3DXMatrixAffineTransformation2D(&mat, size, 0, rot, &D3DXVECTOR2(x, y));
		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, &rc, nullptr, nullptr, color);
	}
}

void cImageManager::CenterRender(texture * texturePtr, float x, float y, float size, float rot, D3DXCOLOR color)
{
	if (texturePtr) {
		D3DXMATRIXA16 mat;
		D3DXMatrixAffineTransformation2D(&mat, size, 0, rot, &D3DXVECTOR2(x - texturePtr->info.Width / 2, y - texturePtr->info.Height / 2));
		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, color);
	}
}

texture * cImageManager::AddImage(const string & key, const string & path)
{
	auto find = m_images.find(key);

	if (find != m_images.end())
		return find->second;

	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texturePtr;

	if (D3DXCreateTextureFromFileExA(g_device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &texturePtr) == S_OK) {
		texture *text = new texture(texturePtr, info);
		m_images.insert(make_pair(key, text));
		return text;
	}

	return nullptr;
}

texture * cImageManager::FindImage(const string & key)
{
	auto find = m_images.find(key);

	if (find == m_images.end()) {
		DEBUG_LOG(key << " 이미지를 찾을 수 없습니다.");
		return nullptr;
	}

	return find->second;
}

void cImageManager::Begin()
{
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void cImageManager::End()
{
	m_sprite->End();
}

void cImageManager::AddAnimation(const string & path, int totalFrame)
{
	for (int i = 0; i < totalFrame; i++) {
		string str = (path + to_string(i)) + ".png";
		AddImage(str, str);
	}
}

void cImageManager::AddAnimationVer2(const string & path, int totalFrame)
{
	for (int i = 0; i < totalFrame; i++) {
		string str = path + ((i < 10) ? "0" : "");
		str += to_string(i) + ".png";
		AddImage(str, str);
	}
}
