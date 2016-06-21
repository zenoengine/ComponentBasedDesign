#pragma once
#include "ComponentType.h"
#include "GameObject.h"
#include "TextureMgr.h"
#include "SceneMgr.h"
#include "InputMgr.h"

class CGameObject;
class CTransform;

class CComponentBase
{
protected:
	CGameObject* m_thisGameObject;

public:
	CComponentBase();
	virtual ~CComponentBase();

	virtual const ComponentFamilyType GetFamilyComponentType() const;
	
	virtual void Init() {};
	virtual void Update() {};
	virtual void Clear() {};

	void SetParent(CGameObject* pGameObject);
};