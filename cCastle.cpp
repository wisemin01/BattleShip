#include "DXUT.h"
#include "cCastle.h"


cCastle::cCastle(D3DXVECTOR2 pos)
{
	info.m_pos = pos;
	info.m_collider = { 0 };
	info.m_color = D3DCOLOR_ARGB(255, 255, 255, 255);
	info.m_objectTag = OBJ_CASTLE;
	info.m_size = 1.0;

	hp = 6000;
}


cCastle::~cCastle()
{
}

void cCastle::HPUpdate()
{
}
