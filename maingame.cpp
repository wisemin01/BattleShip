#include "DXUT.h"
#include "maingame.h"


//scene include

#include "cLoadingScene.h"	// 로딩		[1]
#include "cIntroScene.h"	// 인트로	[2]
#include "cMainmenuScene.h"	// 메인메뉴	[3]
#include "cShipPlaceScene.h"// 배 배치  [4]
#include "cIngameScene.h"	// 인게임	[5]

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

	// 게임의 시작할 씬 설정
	SCENEMANAGER->ChangeScene("loading");
}

void maingame::Update()
{
	FADE->Update();

	INPUTMANAGER->KeyInputUpdate(); // 키 입력
	SCENEMANAGER->Update();			// 업데이트
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
