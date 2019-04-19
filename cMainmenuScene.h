#pragma once
#include "cScene.h"
class cMainmenuScene :
	public cScene
{
private:
	texture * m_background;
	texture* m_InputHelp;
	texture* m_Info;
	cAnimation* m_logo;
public:
	cMainmenuScene();
	~cMainmenuScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

