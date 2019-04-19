#pragma once
#include "cGameObject.h"
class cScoreBoard :
	public cGameObject
{
private:
	texture * m_scoreBoard;
	DWORD m_curntTime;
	INT m_curntScore;
	BOOL m_isEnd;
	BOOL m_changeScene;
public:
	cScoreBoard();
	virtual ~cScoreBoard();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

