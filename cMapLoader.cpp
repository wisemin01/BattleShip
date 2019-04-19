#include "DXUT.h"
#include "cMapLoader.h"

#include "cTileMap.h"
#include "cTileObject.h"
#include "cIngameTileObject.h"

cMapLoader::cMapLoader()
{
}


cMapLoader::~cMapLoader()
{
}

void cMapLoader::UploadTileObjects()
{
	for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_PLAYER_OBJ))) {
		m_playerObjs.push_back(new cIngameTileObject(dynamic_cast<cTileObject*>(iter)));
	}
	for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_ENEMY_OBJ))) {
		m_enemyObjs.push_back(new cIngameTileObject(dynamic_cast<cTileObject*>(iter)));
	}
}

void cMapLoader::DownloadPlayerObjs()
{
	for (auto iter : m_playerObjs) {
		OBJECTMANAGER->AddObject(new cIngameTileObject(dynamic_cast<cIngameTileObject*>(iter)), OBJ_PLAYER_OBJ);
	}

	for (auto iter : m_playerObjs) {
		iter->Release();
		SAFE_DELETE(iter);
	}

	m_playerObjs.clear();
}

void cMapLoader::DownloadEnemyObjs()
{
	for (auto iter : m_enemyObjs) {
		OBJECTMANAGER->AddObject(new cIngameTileObject(dynamic_cast<cIngameTileObject*>(iter)), OBJ_ENEMY_OBJ);
	}

	for (auto iter : m_enemyObjs) {
		iter->Release();
		SAFE_DELETE(iter);
	}

	m_enemyObjs.clear();
}


void cMapLoader::ResetVectors()
{
	m_playerObjs.clear();
	m_enemyObjs.clear();
}
