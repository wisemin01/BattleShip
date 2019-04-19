#pragma once
#include "cGameObject.h"

class cTimerString :
	public cGameObject
{
private:
	string	str;
	DWORD	timer;
	INT		size;
public:
	cTimerString(const string& str,DWORD timer,D3DXVECTOR2 pos,INT size = 50);
	virtual ~cTimerString();

	virtual void Init	()	override;
	virtual void Update	()	override;
	virtual void Render	()	override;
	virtual void Release()	override;
};


#define TIMER_STRING(str,timer,pos,size) OBJECTMANAGER->AddObject(new cTimerString(str,timer,pos,size),OBJ_GUI)