#include "DXUT.h"
#include "cMainmenuScene.h"

#include "cButton.h"

BOOL m_isChangeScene = false;

cMainmenuScene::cMainmenuScene()
{
}


cMainmenuScene::~cMainmenuScene()
{
}

void cMainmenuScene::Init()
{
	SCENEMANAGER->SetAutoObjectManager_Update(false);

	OBJECTMANAGER->Reset();
	FADE->FadeOut();

	OBJECTMANAGER->AddObject(new cButton(D3DXVECTOR2(WINSIZEX - 400, 200), IMAGEMANAGER->FindImage("gameStartOn"),
		IMAGEMANAGER->FindImage("gameStartOff"), []() { FADE->FadeIn(); m_isChangeScene = true; }), OBJ_GUI);
	OBJECTMANAGER->AddObject(new cButton(D3DXVECTOR2(WINSIZEX - 400, 400), IMAGEMANAGER->FindImage("gameInfoOn"),
		IMAGEMANAGER->FindImage("gameInfoOff"), []() { GAMEMANAGER->SetInputHelpFlag(!GAMEMANAGER->GetInputHelpFlag()); }), OBJ_GUI);
	OBJECTMANAGER->AddObject(new cButton(D3DXVECTOR2(WINSIZEX - 400, 600), IMAGEMANAGER->FindImage("gameInputHelpOn"),
		IMAGEMANAGER->FindImage("gameInputHelpOff"), []() { GAMEMANAGER->SetInfoFlag(!GAMEMANAGER->GetInfoFlag()); }), OBJ_GUI);
	OBJECTMANAGER->AddObject(new cButton(D3DXVECTOR2(WINSIZEX - 400, 800), IMAGEMANAGER->FindImage("gameQuitOn"),
		IMAGEMANAGER->FindImage("gameQuitOff"), []() { PostQuitMessage(0); }), OBJ_GUI);

	m_background = IMAGEMANAGER->FindImage("mainmenuBG");

	m_Info = IMAGEMANAGER->FindImage("Info");
	m_InputHelp = IMAGEMANAGER->FindImage("InputHelp");

	m_logo = new cAnimation("./image/ui/logo/", 3, 250);
	SOUNDMANAGER->pPlayBgm(6,34000);
}

void cMainmenuScene::Update()
{
	OBJECTMANAGER->Update();
	m_logo->Update();
	if (m_isChangeScene == true &&
		FADE->Finish()) {
		SCENEMANAGER->ChangeScene("shipplace");
		m_isChangeScene = false;
	}
}

void cMainmenuScene::Render()
{
	m_background->Render(0, 0);
	m_logo->CenterRender(400, 300);

	OBJECTMANAGER->Render();

	if (GAMEMANAGER->GetInputHelpFlag())
		m_InputHelp->CenterRender(WINSIZEX / 2, WINSIZEY / 2);

	if (GAMEMANAGER->GetInfoFlag())
		m_Info->CenterRender(WINSIZEX / 2, WINSIZEY / 2);
}

void cMainmenuScene::Release()
{
	SOUNDMANAGER->pStopSound(6);
	OBJECTMANAGER->Reset();
	SAFE_DELETE(m_logo);
}
