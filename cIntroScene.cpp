#include "DXUT.h"
#include "cIntroScene.h"


cIntroScene::cIntroScene()
{
}


cIntroScene::~cIntroScene()
{
}

void cIntroScene::Init()
{
	m_introImage = new cAnimation("./image/intro/", 3, 50);
	m_BG = IMAGEMANAGER->FindImage("introBG");
	m_aniIndex = 0;
	m_changeScene = false;
}

void cIntroScene::Update()
{
	if (GETKEY_DOWN(VK_LBUTTON)) {
		if (m_aniIndex == 3) {
			m_changeScene = true;
			FADE->FadeIn();
		}
		m_aniIndex++;
	}
	if (FADE->Finish() && m_changeScene)
		SCENEMANAGER->ChangeScene("mainmenu");
}

void cIntroScene::Render()
{
	m_BG->Render(-30, 0);

	if (m_aniIndex >= 1)
		m_introImage->FrameRender(0, 0, 0);

	if(m_aniIndex >= 2)
		m_introImage->FrameRender(0, 0, 1);

	if (m_aniIndex >= 3)
		m_introImage->FrameRender(0, 0, 2);
}

void cIntroScene::Release()
{
	SAFE_DELETE(m_introImage);
}
