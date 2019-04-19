#pragma once

// ������Ʈ�� ������ ���� ����ü D3DXVECTOR (��ġ), INT (�±�), RECT (�浹����), D3DXCOLOR (��)
struct OBJECT_INFO {

	D3DXVECTOR2 m_pos; // ��ġ��
	INT m_objectTag; // ������Ʈ �±�
	RECT m_collider; // �浹����
	D3DXCOLOR m_color; // �� ����
	FLOAT m_size; // ������Ʈ ũ��

	OBJECT_INFO() :m_pos(D3DXVECTOR2(0, 0)), m_objectTag(0), m_collider({0,0,0,0}),m_color(D3DCOLOR_ARGB(255,255,255,255)),m_size(1.0) {}
};

class cGameObject
{
protected:
	OBJECT_INFO info; // ������Ʈ ����
	BOOL m_deleteFlag; // true �� �Ǹ� ������Ʈ�� ����Ʈ���� ������
public:
	// ������
	cGameObject();
	cGameObject(float x, float y);
	cGameObject(D3DXVECTOR2 startPos);

	virtual ~cGameObject();

	// �⺻ ������Ʈ �Լ�

	virtual void Init	() PURE;
	virtual void Update	() PURE;
	virtual void Render	() PURE;
	virtual void Release() PURE;

	// �ܺ� ���� �ռ�

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

