#include "DXUT.h"
#include "maingame.h"


//scene include

#include "cLoadingScene.h"	// �ε�		[1]
#include "cIntroScene.h"	// ��Ʈ��	[2]
#include "cMainmenuScene.h"	// ���θ޴�	[3]
#include "cShipPlaceScene.h"// �� ��ġ  [4]
#include "cIngameScene.h"	// �ΰ���	[5]

//

maingame::maingame()
{
}


maingame::~maingame()
{
}

void maingame::Init()
{
	SCENEMANAGER->AddScene("loading", new cLoadingScene);
	SCENEMANAGER->AddScene("intro", new cIntroScene);
	SCENEMANAGER->AddScene("mainmenu", new cMainmenuScene);
	SCENEMANAGER->AddScene("shipplace", new cShipPlaceScene);
	SCENEMANAGER->AddScene("ingame", new cIngameScene);

	// ������ ������ �� ����
	SCENEMANAGER->ChangeScene("loading");
}

void maingame::Update()
{
	FADE->Update();

	INPUTMANAGER->KeyInputUpdate(); // Ű �Է�
	SCENEMANAGER->Update();			// ������Ʈ
	SOUNDMANAGER->Update();
}

void maingame::Render()
{
	IMAGEMANAGER->Begin();

	SCENEMANAGER->Render();

	IMAGEMANAGER->End();
}

void maingame::Release()
{
	// MANAGER RELEASE

	cMapLoader::ReleaseInstance();

	cGameManager	::ReleaseInstance();
	cSceneManager	::ReleaseInstance();
	cInputManager	::ReleaseInstance();
	cObjectManager	::ReleaseInstance();
	cTextManager	::ReleaseInstance();
	cImageManager	::ReleaseInstance();
	cSoundManager	::ReleaseInstance();

	cFade			::ReleaseInstance();
}

void maingame::ResetDevice()
{
	IMAGEMANAGER->OnResetDevice();
}

void maingame::LostDevice()
{
	IMAGEMANAGER->OnLostDevice();
}
