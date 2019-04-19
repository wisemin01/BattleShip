#include "DXUT.h"
#include "cFade.h"


cFade::cFade()
{
	renderPos.x = 1930;
	renderPos.y = 0;
	bFade = false;
}


cFade::~cFade()
{
}

void cFade::Init() {
	fadeImg = IMAGEMANAGER->FindImage("changeSceneImage");
	isFinish = true;
}

void cFade::Render()
{
	//fadeImg->Render(-1980 + (1930 - renderPos.x), renderPos.y);
	fadeImg->Render(renderPos.x, renderPos.y, 1.0, 0.0, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void cFade::Update()
{
	if (bFade) {
		if (renderPos.x >= 0)
			renderPos.x -= 1500 * g_deltaTime;
		else isFinish = true;
	}
	else {
		if (renderPos.x <= 1930)
			renderPos.x += 1500 * g_deltaTime;
		else isFinish = true;
	}
}

void cFade::FadeIn()
{
	bFade = true;
	isFinish = false;
}

void cFade::FadeOut()
{
	bFade = false;
	isFinish = false;
}

BOOL cFade::Finish()
{
	return isFinish;
}
