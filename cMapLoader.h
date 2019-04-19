#pragma once
#include "singleton.h"

class cTile;
struct TileObjectInfo;
class cTileObject;

class cMapLoader :
	public singleton<cMapLoader>
{
private:
	vector<cTileObject*> m_playerObjs;
	vector<cTileObject*> m_enemyObjs;
public:
	cMapLoader();
	~cMapLoader();

	void UploadTileObjects();
	void DownloadPlayerObjs();
	void DownloadEnemyObjs();

	void ResetVectors();

};

#define MAPLOADER cMapLoader::GetInstance()