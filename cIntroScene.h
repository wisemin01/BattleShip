#pragma once
#include "cScene.h"
class cIntroScene :
	public cScene
{
private:
	cAnimation * m_introImage;
	texture* m_BG;
	INT m_aniIndex;
	BOOL m_changeScene;
public:
	cIntroScene();
	~cIntroScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

