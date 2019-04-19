#pragma once
#include "cGameObject.h"
class cScroolMap :
	public cGameObject
{
private:
	texture * m_scroolMap;
	//texture * m_topUIBase;
	//cAnimation* m_smoke;
public:
	cScroolMap();
	cScroolMap(texture* text);
	~cScroolMap();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

