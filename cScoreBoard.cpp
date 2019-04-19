#include "DXUT.h"
#include "cScoreBoard.h"


cScoreBoard::cScoreBoard()
{
}


cScoreBoard::~cScoreBoard()
{
}

void cScoreBoard::Init()
{
	m_scoreBoard = IMAGEMANAGER->FindImage("ScoreBoard");
	m_curntScore = 0;
	m_curntTime = 0;
	m_isEnd = false;
	m_changeScene = false;
}

void cScoreBoard::Update()
{
	if (m_curntScore < GAMEMANAGER->GetPlayerScore()) {
		m_curntScore += 20;
	}
	else m_isEnd = true;

	if (m_isEnd && m_curntScore > GAMEMANAGER->GetPlayerScore()) {
		m_curntScore = GAMEMANAGER->GetPlayerScore();
	}

	if (m_isEnd && GETKEY_DOWN(VK_LBUTTON)) {
		FADE->FadeIn();
		m_changeScene = true;
	}

	if (m_changeScene && FADE->Finish())
		SCENEMANAGER->ChangeScene("mainmenu");
}

void cScoreBoard::Render()
{
	m_scoreBoard->CenterRender(WINSIZEX / 2, WINSIZEY / 2);
	TEXTMANAGER->drawNumber(m_curntScore, 6, D3DXVECTOR2(WINSIZEX / 2 - 95, WINSIZEY / 2));
}

void cScoreBoard::Release()
{
}
