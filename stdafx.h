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

#define g_device	DXUTGetD3D9Device()		// ����̽�
#define g_deltaTime DXUTGetElapsedTime()	// �����Ӱ� ���� �ð�
#define g_nowTime	timeGetTime()			//���� �ð�

//ADD MANAGERS

#include "cGameManager.h"
#include "cImageManager.h"
#include "cObjectManager.h"
#include "cSceneManager.h"
#include "cTextManager.h"
#include "cInputManager.h"
#include "cSoundManager.h"

// �̸� ������

#include "cAnimation.h"
#include "cTimerString.h"

#include "cMapLoader.h"
#include "cFade.h"