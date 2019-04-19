#pragma once

// 오브젝트의 정보를 담은 구조체 D3DXVECTOR (위치), INT (태그), RECT (충돌범위), D3DXCOLOR (색)
struct OBJECT_INFO {

	D3DXVECTOR2 m_pos; // 위치값
	INT m_objectTag; // 오브젝트 태그
	RECT m_collider; // 충돌범위
	D3DXCOLOR m_color; // 색 정보
	FLOAT m_size; // 오브젝트 크기

	OBJECT_INFO() :m_pos(D3DXVECTOR2(0, 0)), m_objectTag(0), m_collider({0,0,0,0}),m_color(D3DCOLOR_ARGB(255,255,255,255)),m_size(1.0) {}
};

class cGameObject
{
protected:
	OBJECT_INFO info; // 오브젝트 정보
	BOOL m_deleteFlag; // true 가 되면 오브젝트를 리스트에서 삭제함
public:
	// 생성자
	cGameObject();
	cGameObject(float x, float y);
	cGameObject(D3DXVECTOR2 startPos);

	virtual ~cGameObject();

	// 기본 오브젝트 함수

	virtual void Init	() PURE;
	virtual void Update	() PURE;
	virtual void Render	() PURE;
	virtual void Release() PURE;

	// 외부 접근 합수

	virtual void SetPos(float x, float y) { info.m_pos = D3DXVECTOR2(x, y); }
	virtual void SetSize(float size) { info.m_size = size; }
	virtual D3DXVECTOR2 GetPos() { return info.m_pos; }
	virtual FLOAT GetSize() { return info.m_size; }
	
	void DeleteObject()			{ m_deleteFlag = true; }
	void SetObjectTag(INT tag)  { info.m_objectTag = tag;   }
	INT  GetDeleteFlag()		{ return m_deleteFlag; }
	INT	 GetObjectTag()			{ return info.m_objectTag;  }

	OBJECT_INFO GetObjectInfo() { return info; }
};

