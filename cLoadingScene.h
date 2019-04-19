#pragma once
#include "cScene.h"
class cLoadingScene :
	public cScene
{
private:
	cAnimation * m_loading;
public:
	cLoadingScene();
	virtual ~cLoadingScene();

	virtual void Init	()	override;
	virtual void Update	()	override;
	virtual void Render	()	override;
	virtual void Release()	override;

	static UINT __stdcall LoadImages(void *arg);
	static UINT __stdcall LoadImages2(void *arg);
};

