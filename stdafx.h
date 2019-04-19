#pragma once

#include <functional>
#include <process.h>
#include <algorithm>
#include <mmsystem.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <list>
#include <map>

using namespace std;

const int WINSIZEX = 1920;
const int WINSIZEY = 1080;

const int WINSIZEX_CENTER = 800;
const int WINSIZEY_CENTER = 450;


const int TOP_UI_Y = 168;

BOOL CoillsionCheck_Mouse_Tile(const D3DXVECTOR3& vPoint, const D3DXVECTOR3& vPos, const D3DXVECTOR3& vSize);
BOOL nIntersectRect(RECT rc1, RECT rc2);
BOOL nIntersectRectToPoint(RECT rc, D3DXVECTOR2 point);

int RandomNumber(int min, int max);

#if _DEBUG
#define DEBUG_LOG(log) cout << log << endl
#else
#define DEBUG_LOG(log)  
#endif

#define g_device	DXUTGetD3D9Device()		// 디바이스
#define g_deltaTime DXUTGetElapsedTime()	// 프레임간 측정 시간
#define g_nowTime	timeGetTime()			//현재 시간

//ADD MANAGERS

#include "cGameManager.h"
#include "cImageManager.h"
#include "cObjectManager.h"
#include "cSceneManager.h"
#include "cTextManager.h"
#include "cInputManager.h"
#include "cSoundManager.h"

// 미리 컴파일

#include "cAnimation.h"
#include "cTimerString.h"

#include "cMapLoader.h"
#include "cFade.h"