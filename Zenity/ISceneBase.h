#pragma once
#include "SceneRegistrar.h"
class CGameObject;

class ISceneBase abstract
{
public:
	virtual ~ISceneBase() {};
	virtual void Init() = 0;
	virtual void Clear() = 0;

	virtual void Update() = 0;
	virtual void Draw() = 0;
	
	virtual void AppendChild(shared_ptr<CGameObject> spGameObject) = 0;
	virtual void RemoveChild(shared_ptr<CGameObject> spGameObject) = 0;
	virtual void RemoveChild(const string& name) = 0;
	virtual void RemoveChild(const string tagName) = 0;

};