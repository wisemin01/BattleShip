#pragma once
#include "singleton.h"
class cFade :
	public singleton <cFade>
{
private:
	texture * fadeImg;
	D3DXVECTOR2 renderPos;

	bool bFade;
	bool isFinish;
public:
	cFade();
	virtual ~cFade();

	void Init();
	void Render();
	void Update();

	void FadeIn();
	void FadeOut();

	BOOL Finish();
};

#define FADE cFade::GetInstance()