#pragma once
#include "singleton.h"

class cGameObject;

class cObjectManager :
	public singleton<cObjectManager>
{
public:
	enum GAMEOBJECT_TAGS {
		e_gameMaps,
		e_boards,
		e_castles,
		e_tileMaps,
		e_playerObjects,
		e_enemyObjects,
		e_playerSoldier,
		e_enemySoldier,
		e_anyObjects,
		e_effects,
		e_GUIs,
		e_viewer
	};
private:
	map<INT, list<cGameObject*>*> m_obj;
public:
	cObjectManager();
	~cObjectManager();

	void Init();
	void Update();
	void Render();
	void Release();

	void Reset();

	cGameObject* AddObject(cGameObject* g_obj, INT obj_tag);
	list<cGameObject*>* GetObjectList(INT obj_tag);

	void MoveObjectGroup(INT obj_tag, D3DXVECTOR2 plusVector);

private:
	// delete 
	void DeleteObjectCheck();
public:
	// debug mode
#if defined(DEBUG) | defined(_DEBUG)
	INT debug_ObjectCount;
#endif
};

#define OBJECTMANAGER cObjectManager::GetInstance()

// 외부에서 enum 쓸때 줄여 쓰기 위한 define

#define OBJ_GAMEMAP		cObjectManager::GAMEOBJECT_TAGS::e_gameMaps
#define OBJ_TILEMAPS	cObjectManager::GAMEOBJECT_TAGS::e_tileMaps
#define OBJ_BOARD		cObjectManager::GAMEOBJECT_TAGS::e_boards
#define OBJ_CASTLE		cObjectManager::GAMEOBJECT_TAGS::e_castles
#define OBJ_PLAYER_OBJ	cObjectManager::GAMEOBJECT_TAGS::e_playerObjects
#define OBJ_ENEMY_OBJ	cObjectManager::GAMEOBJECT_TAGS::e_enemyObjects
#define OBJ_ANY			cObjectManager::GAMEOBJECT_TAGS::e_anyObjects
#define OBJ_EFFECT		cObjectManager::GAMEOBJECT_TAGS::e_effects
#define OBJ_GUI			cObjectManager::GAMEOBJECT_TAGS::e_GUIs
#define OBJ_VIEWER		cObjectManager::GAMEOBJECT_TAGS::e_viewer
#define OBJ_PLAYER_SOL	cObjectManager::GAMEOBJECT_TAGS::e_playerSoldier
#define OBJ_ENEMY_SOL	cObjectManager::GAMEOBJECT_TAGS::e_enemySoldier
//--
