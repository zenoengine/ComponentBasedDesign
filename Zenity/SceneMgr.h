#pragma once
#include "ISceneBase.h"
#include "SceneRegistrar.h"

class CGame;
class ISceneBase;

class CSceneMgr
{
	friend class CGame;

private:
	weak_ptr<ISceneBase> m_wpCurrentScene;
	map<string, shared_ptr<ISceneBase>> m_loadedSceneMap;
	map<string, std::function<shared_ptr<ISceneBase>(void)>> m_sceneFactoryRegistry;

private:
	CSceneMgr();
	~CSceneMgr();

	void UnloadAllScene();

public:
	static CSceneMgr* GetInstance();

	bool Init();
	void Release();
	void LoadScene(const string& name);
	void UnloadScene(const string& name);
	void RegisterScene(const string& sceneName, std::function<shared_ptr<ISceneBase>(void)> generatorFunc);
};

#define g_pSceneMgr CSceneMgr::GetInstance()

