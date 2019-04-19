#pragma once
#include "singleton.h"

class cScene;

class cSceneManager :
	public singleton<cSceneManager>
{
private:
	cScene * m_nowScene;
	cScene * m_nextScene;

	map<string, cScene*> m_scenes;

	BOOL m_AutoUpdate_ObjectManager;
public:
	cSceneManager();
	~cSceneManager();

	void Init();
	void Update();
	void Render();
	void Release();

	cScene* AddScene(const string& key, cScene* scenePtr);
	cScene* ChangeScene(const string& key);

	void SetAutoObjectManager_Update(BOOL flag) { m_AutoUpdate_ObjectManager = flag; }
	BOOL GetAutoObjectManager_Update()			{ return m_AutoUpdate_ObjectManager; }

	string GetNowScene();
};

#define SCENEMANAGER cSceneManager::GetInstance()