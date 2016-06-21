#pragma once
#include "ISceneBase.h"
#include "GameObject.h"
#include "SceneRegistrar.h"

class CSceneBase : 	public ISceneBase
{
private:
	vector<shared_ptr<CGameObject>> m_gameObjectVec;

public:
	CSceneBase();
	virtual ~CSceneBase();

	void Init() override;
	void Clear() override;

	void Update() final;
	void Draw() final;

	void AppendChild(shared_ptr<CGameObject> spGameObject) final;
	void RemoveChild(shared_ptr<CGameObject> spGameObject) final;
	void RemoveChild(const string& name) final;
	void RemoveChild(const string tagName) final;
};

