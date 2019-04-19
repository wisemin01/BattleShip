#include "DXUT.h"
#include "cObjectManager.h"
#include "cGameObject.h"

#include "cSoldier.h"

cObjectManager::cObjectManager()
{
	Init();
}


cObjectManager::~cObjectManager()
{
	Release();
}

void cObjectManager::Init()
{
#if defined(DEBUG) | defined(_DEBUG)
	debug_ObjectCount = 0;
#endif

	//	e_gameMaps,
	m_obj.insert(make_pair(e_gameMaps, new list<cGameObject*>));
	//	e_boards,
	m_obj.insert(make_pair(e_boards, new list<cGameObject*>));
	//  e_castles,
	m_obj.insert(make_pair(e_castles, new list<cGameObject*>));
	//  e_tileMaps,
	m_obj.insert(make_pair(e_tileMaps, new list<cGameObject*>));
	//	e_playerObjects,
	m_obj.insert(make_pair(e_playerObjects, new list<cGameObject*>));
	//	e_enemyObjects,
	m_obj.insert(make_pair(e_enemyObjects, new list<cGameObject*>));
	//	e_playerSoldier,
	m_obj.insert(make_pair(e_playerSoldier, new list<cGameObject*>));
	//e_enemySoldier,
	m_obj.insert(make_pair(e_enemySoldier, new list<cGameObject*>));
	//	e_anyObjects,
	m_obj.insert(make_pair(e_anyObjects, new list<cGameObject*>));
	//	e_effects,
	m_obj.insert(make_pair(e_effects, new list<cGameObject*>));
	//	e_GUIs
	m_obj.insert(make_pair(e_GUIs, new list<cGameObject*>));
	//  e_viewer
	m_obj.insert(make_pair(e_viewer, new list<cGameObject*>));

	//  ADD OBJECT LIST !
}

void cObjectManager::Update()
{
	for (auto iter : m_obj) {
		for (auto iter2 : (*iter.second)) {
			if (iter2)
				iter2->Update();
		}
	}
	DeleteObjectCheck();
}

void cObjectManager::Render()
{
	for (auto iter : m_obj) {
		for (auto iter2 : (*iter.second)) {
			if (iter2)
				iter2->Render();
		}
	}
}

void cObjectManager::Release()
{
	Reset();
	for (auto iter : m_obj) {
		SAFE_DELETE(iter.second);
	}
	m_obj.clear();
}

void cObjectManager::Reset()
{
	for (auto iter : m_obj) {
		for (auto iter2 : (*iter.second)) {
			if (iter2)
				iter2->Release();
			SAFE_DELETE(iter2);
#if defined(DEBUG) | defined(_DEBUG)
			debug_ObjectCount--;
#endif
		}
		iter.second->clear();
	}
}

cGameObject * cObjectManager::AddObject(cGameObject * g_obj, INT obj_tag)
{
	auto find = m_obj.find(obj_tag);

	if (find == m_obj.end())
		return nullptr;

	(*find->second).push_back(g_obj);

	g_obj->SetObjectTag(obj_tag);
	g_obj->Init();

#if defined(DEBUG) | defined(_DEBUG)
	debug_ObjectCount++;
#endif

	return g_obj;
}

list<cGameObject*>* cObjectManager::GetObjectList(INT obj_tag)
{
	auto find = m_obj.find(obj_tag);

	if (find == m_obj.end())
		return nullptr;

	return find->second;
}

void cObjectManager::MoveObjectGroup(INT obj_tag, D3DXVECTOR2 plusVector)
{
	auto find = m_obj.find(obj_tag);

	if (find == m_obj.end())
		return;

	for (auto iter :(*find->second)) {
		iter->SetPos(iter->GetPos().x + plusVector.x, iter->GetPos().y + plusVector.y);
	}
}

void cObjectManager::DeleteObjectCheck()
{
	for (auto iter : m_obj) {

		for (auto iter2 = (*iter.second).begin(); iter2 != (*iter.second).end();) {

			if ((*iter2)->GetDeleteFlag()) {
				(*iter2)->Release();
				SAFE_DELETE(*iter2);
				iter2 = iter.second->erase(iter2);
			}
			else {
				iter2++;
			}

		}

	}

}
