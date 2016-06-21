#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr::CSceneMgr()
{
	m_wpCurrentScene.reset();
}

CSceneMgr::~CSceneMgr()
{
	m_wpCurrentScene.reset();
}

void CSceneMgr::UnloadAllScene()
{
	auto iter = m_loadedSceneMap.begin();
	while (iter != m_loadedSceneMap.end())
	{
		UnloadScene(iter->first);
		iter = m_loadedSceneMap.begin();
	}
}

CSceneMgr* CSceneMgr::GetInstance()
{
	static CSceneMgr instance;
	return &instance;
}

bool CSceneMgr::Init()
{
	return true;
}

void CSceneMgr::Release()
{
	UnloadAllScene();
}

void CSceneMgr::LoadScene(const string& name)
{
	if (m_loadedSceneMap.find(name) != m_loadedSceneMap.end())
	{
		OutputDebugString(L"Warning : Already exist scene");
		return;
	}

	auto iter = m_sceneFactoryRegistry.find(name);
	if (iter == m_sceneFactoryRegistry.end())
	{
		assert("You must register Scene then call eg) \"BeginScene\" ");
		return;
	}

	UnloadAllScene();

	auto sceneFactoryFunc = iter->second;
	shared_ptr<ISceneBase> spNewScene = shared_ptr<ISceneBase>(sceneFactoryFunc());
	if (spNewScene == nullptr)
	{
		OutputDebugString(L"Can't find Scene");
		return;
	}

	spNewScene->Init();
	m_loadedSceneMap.insert(make_pair(name, spNewScene));
}

void CSceneMgr::UnloadScene(const string& name)
{
	auto iter = m_loadedSceneMap.find(name);
	if (iter == m_loadedSceneMap.end())
	{
		OutputDebugString(L"Can't find Scene");
		return;
	}

	shared_ptr<ISceneBase> spSceneBase = iter->second;
	if (spSceneBase)
	{
		spSceneBase->Clear();
		spSceneBase = nullptr;
	}

	m_loadedSceneMap.erase(iter);
}

void CSceneMgr::RegisterScene(const string& sceneName, std::function<shared_ptr<ISceneBase>(void)> generatorFunc)
{
	m_sceneFactoryRegistry[sceneName] = generatorFunc;
}