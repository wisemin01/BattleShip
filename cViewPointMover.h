#pragma once
#include "cGameObject.h"
class cViewPointMover :
	public cGameObject
{
private:
	float m_viewPointX;
	float m_viewPointY;

	BOOL RightFlag;
	BOOL LeftFlag;
public:
	cViewPointMover();
	~cViewPointMover();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void Detection();
	FLOAT GetViewPointX() { return m_viewPointX; }

	void FlagSetting(BOOL rightFlag, BOOL leftFlag);
	BOOL GetRightFlag() { return RightFlag; }
	BOOL GetLeftFlag() { return LeftFlag; }
};

#define VIEWPOINT_X dynamic_cast<cViewPointMover*>(OBJECTMANAGER->GetObjectList(OBJ_VIEWER)->front())->GetViewPointX()
#define VIEWPOINTMOVER dynamic_cast<cViewPointMover*>(OBJECTMANAGER->GetObjectList(OBJ_VIEWER)->front())
