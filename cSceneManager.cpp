#include "DXUT.h"
#include "cSceneManager.h"

#include "cScene.h"

cSceneManager::cSceneManager()
	:m_nowScene(nullptr),m_nextScene(nullptr)
{
	Init();
}


cSceneManager::~cSceneManager()
{
	Release();
}

void cSceneManager::Init()
{
	m_AutoUpdate_ObjectManager = true;
}

void cSceneManager::Update()
{
	if (m_nextScene)
	{
		if (m_nowScene) {
			m_nowScene->Release();
			if (m_AutoUpdate_ObjectManager)
				OBJECTMANAGER->Reset();
		}

		m_nextScene->Init();

		m_nowScene = m_nextScene;
		m_nextScene = nullptr;
	}
	if (m_nowScene) {
		m_nowScene->Update();
		if (m_AutoUpdate_ObjectManager)
			OBJECTMANAGER->Update();
	}
}

void cSceneManager::Render()
{
	if (m_nowScene) {
		m_nowScene->Render();
		if (m_AutoUpdate_ObjectManager)
			OBJECTMANAGER->Render();
	}
	if (GetNowScene() != "loading")
		FADE->Render();
}

void cSceneManager::Release()
{
	if (m_nowScene)
		m_nowScene->Release();

	for (auto iter : m_scenes)
	{
		SAFE_DELETE(iter.second);
	}
	m_scenes.clear();
}

cScene * cSceneManager::AddScene(const string & key, cScene * scenePtr)
{
	if (!scenePtr)
		return nullptr;

	auto find = m_scenes.find(key);

	if (find != m_scenes.end())
		return find->second;
	
	m_scenes.insert(make_pair(key, scenePtr));

	return scenePtr;
}

cScene * cSceneManager::ChangeScene(const string & key)
{
	auto find = m_scenes.find(key);

	if (find == m_scenes.end()) {
		DEBUG_LOG(key + "씬 을(를) 찾을 수 없습니다.");
		return nullptr;
	}

	m_nextScene = find->second;
	return find->second;
}

string cSceneManager::GetNowScene()
{
	for (auto iter : m_scenes)
	{
		if (iter.second == m_nowScene) {
			return iter.first;
		}
	}
}
