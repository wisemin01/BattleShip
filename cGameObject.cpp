#include "DXUT.h"
#include "cGameObject.h"


cGameObject::cGameObject()
{
	m_deleteFlag = false;
}
cGameObject::cGameObject(float x, float y)
{
	info.m_pos = D3DXVECTOR2(x, y);
	m_deleteFlag = false;
}
cGameObject::cGameObject(D3DXVECTOR2 startPos)
{
	info.m_pos = startPos;
	m_deleteFlag = false;
}


cGameObject::~cGameObject()
{
}
