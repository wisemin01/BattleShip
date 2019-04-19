#include "DXUT.h"
#include "cLoadingScene.h"


BOOL m_loadingEnd = FALSE;
BOOL m_loadingEnd2 = FALSE;


cLoadingScene::cLoadingScene()
{
}

cLoadingScene::~cLoadingScene()
{
}

void cLoadingScene::Init()
{
	SOUNDMANAGER->AddSound(L"./sound/sound1.wav");
	SOUNDMANAGER->AddSound(L"./sound/explodeSound.wav");
	SOUNDMANAGER->AddSound(L"./sound/tileset.wav");
	SOUNDMANAGER->AddSound(L"./sound/tileset2.wav");

	SOUNDMANAGER->AddSound(L"./sound/sound2.wav");
	SOUNDMANAGER->AddSound(L"./sound/mainmenu.wav");

	IMAGEMANAGER->AddAnimation("./image/loading/", 5);

	_beginthreadex(nullptr, 0, LoadImages, nullptr, 0, nullptr);
	_beginthreadex(nullptr, 0, LoadImages2, nullptr, 0, nullptr);

	m_loading = new cAnimation("./image/loading/", 5, 100);
}

void cLoadingScene::Update()
{
	Sleep(1);
	m_loading->Update();

	if (m_loadingEnd && m_loadingEnd2) {
		FADE->Init();
		SCENEMANAGER->ChangeScene("intro");
	}
}

void cLoadingScene::Render()
{
	m_loading->Render(0, -40);
}

void cLoadingScene::Release()
{
	SAFE_DELETE(m_loading);
}

UINT __stdcall cLoadingScene::LoadImages(void * arg)
{
	//-----------------------------------------------
	// Loading Images
	//-----------------------------------------------

	Sleep(1);

	//

	IMAGEMANAGER->AddAnimation("./image/tiles/tile", 6);
	IMAGEMANAGER->AddAnimation("./image/Effects/smoke", 3);

	IMAGEMANAGER->AddAnimation("./image/effect/explode/", 9);
	IMAGEMANAGER->AddAnimation("./image/effect/smoke/",5);

	IMAGEMANAGER->AddAnimation("./image/ui/HpBar/e", 6);
	IMAGEMANAGER->AddAnimation("./image/ui/HpBar/p", 6);

	IMAGEMANAGER->AddAnimation("./image/ui/logo/", 3);

	IMAGEMANAGER->AddAnimation("./image/intro/", 3);
	//

	IMAGEMANAGER->AddImage("playerCastle", "./image/map/castles/player/B.png");
	IMAGEMANAGER->AddImage("enemyCastle", "./image/map/castles/enemy/B.png");

	IMAGEMANAGER->AddImage("backGround", "./image/map/scroolMap.png");
	IMAGEMANAGER->AddImage("changeSceneImage", "./image/map/changeScene.png");

	IMAGEMANAGER->AddImage("placeMapScene","./image/map/placeMapScene.png");

	IMAGEMANAGER->AddImage("p2_up", "./image/tiles/p2_up.png");
	IMAGEMANAGER->AddImage("p2_down", "./image/tiles/p2_down.png");

	IMAGEMANAGER->AddImage("p2_up2", "./image/tiles/p2_up2.png");
	IMAGEMANAGER->AddImage("p2_down2", "./image/tiles/p2_down2.png");

	IMAGEMANAGER->AddImage("p3_up", "./image/tiles/p3_up.png");
	IMAGEMANAGER->AddImage("p3_down", "./image/tiles/p3_down.png");

	IMAGEMANAGER->AddImage("p3_up2", "./image/tiles/p3_up2.png");
	IMAGEMANAGER->AddImage("p3_down2", "./image/tiles/p3_down2.png");

	IMAGEMANAGER->AddImage("p4_up", "./image/tiles/p4_up.png");
	IMAGEMANAGER->AddImage("p4_down", "./image/tiles/p4_down.png");

	IMAGEMANAGER->AddImage("e2_up", "./image/tiles/e2_up.png");
	IMAGEMANAGER->AddImage("e2_down", "./image/tiles/e2_down.png");

	IMAGEMANAGER->AddImage("e2_up2", "./image/tiles/e2_up2.png");
	IMAGEMANAGER->AddImage("e2_down2", "./image/tiles/e2_down2.png");

	IMAGEMANAGER->AddImage("e3_up", "./image/tiles/e3_up.png");
	IMAGEMANAGER->AddImage("e3_down", "./image/tiles/e3_down.png");

	IMAGEMANAGER->AddImage("e3_up2", "./image/tiles/e3_up2.png");
	IMAGEMANAGER->AddImage("e3_down2", "./image/tiles/e3_down2.png");

	IMAGEMANAGER->AddImage("e4_up", "./image/tiles/e4_up.png");
	IMAGEMANAGER->AddImage("e4_down", "./image/tiles/e4_down.png");

	IMAGEMANAGER->AddImage("./image/enemyObjs/1.png", "./image/enemyObjs/1.png");
	IMAGEMANAGER->AddImage("./image/enemyObjs/1_.png", "./image/enemyObjs/1_.png");

	IMAGEMANAGER->AddImage("./image/enemyObjs/2.png", "./image/enemyObjs/2.png");
	IMAGEMANAGER->AddImage("./image/enemyObjs/2_.png", "./image/enemyObjs/2_.png");

	IMAGEMANAGER->AddImage("./image/enemyObjs/3.png", "./image/enemyObjs/3.png");
	IMAGEMANAGER->AddImage("./image/enemyObjs/3_.png", "./image/enemyObjs/3_.png");

	IMAGEMANAGER->AddImage("./image/enemyObjs/4.png", "./image/enemyObjs/4.png");
	IMAGEMANAGER->AddImage("./image/enemyObjs/4_.png", "./image/enemyObjs/4_.png");

	IMAGEMANAGER->AddImage("./image/enemyObjs/5.png", "./image/enemyObjs/5.png");
	IMAGEMANAGER->AddImage("./image/enemyObjs/5_.png", "./image/enemyObjs/5_.png");

	IMAGEMANAGER->AddImage("./image/ui/playerFace/A.png", "./image/ui/playerFace/A.png");
	IMAGEMANAGER->AddImage("./image/ui/playerFace/B.png", "./image/ui/playerFace/B.png");

	IMAGEMANAGER->AddImage("./image/ui/AttackCountUI/1_.png", "./image/ui/AttackCountUI/1_.png");
	IMAGEMANAGER->AddImage("./image/ui/AttackCountUI/1.png", "./image/ui/AttackCountUI/1.png");

	IMAGEMANAGER->AddImage("gameStartOff", "./image/ui/mainmenuButtons/1.png");
	IMAGEMANAGER->AddImage("gameStartOn", "./image/ui/mainmenuButtons/1_.png");

	IMAGEMANAGER->AddImage("gameInfoOff", "./image/ui/mainmenuButtons/2.png");
	IMAGEMANAGER->AddImage("gameInfoOn", "./image/ui/mainmenuButtons/2_.png");

	IMAGEMANAGER->AddImage("gameInputHelpOff", "./image/ui/mainmenuButtons/3.png");
	IMAGEMANAGER->AddImage("gameInputHelpOn", "./image/ui/mainmenuButtons/3_.png");

	IMAGEMANAGER->AddImage("gameQuitOff", "./image/ui/mainmenuButtons/5.png");
	IMAGEMANAGER->AddImage("gameQuitOn", "./image/ui/mainmenuButtons/5_.png");

	IMAGEMANAGER->AddImage("mainmenuBG", "./image/map/mainmenuBG.png");

	IMAGEMANAGER->AddImage("win", "./image/ui/win.png");
	IMAGEMANAGER->AddImage("lose", "./image/ui/lose.png");

	IMAGEMANAGER->AddImage("Info", "image/ui/Info.png");
	IMAGEMANAGER->AddImage("InputHelp", "image/ui/InputHelp.png");

	IMAGEMANAGER->AddImage("Time", "./image/ui/Time.png");

	IMAGEMANAGER->AddImage("introBG", "./image/intro/introBG.png");
	IMAGEMANAGER->AddImage("ScoreBoard", "./image/ui/scoreBoard.png");
	IMAGEMANAGER->AddImage("YourTurn", "./image/ui/yourturn.png");
	m_loadingEnd = TRUE;

	return 0;
}

UINT __stdcall cLoadingScene::LoadImages2(void * arg)
{
	Sleep(1);

	IMAGEMANAGER->AddAnimation("./image/Soldier/bAttack/", 41);
	IMAGEMANAGER->AddAnimation("./image/Soldier/bDeath/", 41);
	IMAGEMANAGER->AddAnimationVer2("./image/Soldier/bLose/B00", 41);
	IMAGEMANAGER->AddAnimationVer2("./image/Soldier/bWalk/C00", 41);
	IMAGEMANAGER->AddAnimationVer2("./image/Soldier/bWin/E00", 21);

	IMAGEMANAGER->AddAnimationVer2("./image/Soldier/rAttack/C00", 41);
	IMAGEMANAGER->AddAnimationVer2("./image/Soldier/rDeath/E00", 41);
	IMAGEMANAGER->AddAnimationVer2("./image/Soldier/rLose/D00", 41);
	IMAGEMANAGER->AddAnimationVer2("./image/Soldier/rWalk/A00", 41);
	IMAGEMANAGER->AddAnimationVer2("./image/Soldier/rWin/B00", 21);

	m_loadingEnd2 = TRUE;

	return 0;
}
