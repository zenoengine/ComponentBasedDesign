#include "stdafx.h"
#include "SceneBase.h"
#include "QuadRenderer.h"

CSceneBase::CSceneBase()
{
}

CSceneBase::~CSceneBase()
{
	for (auto it : m_gameObjectVec)
	{
		CGameObject* pGameObject = it.get();
		if (pGameObject != nullptr)
		{
			pGameObject->Clear();
		}
	}

	m_gameObjectVec.clear();
}

void CSceneBase::Init()
{
}

void CSceneBase::Clear()
{
}

void CSceneBase::Update()
{
	for (auto it : m_gameObjectVec)
	{
		CGameObject* pGameObject = it.get();
		if (pGameObject != nullptr)
		{
			pGameObject->Update();
		}
	}
}

void CSceneBase::Draw()
{
	for (auto iter : m_gameObjectVec)
	{
		assert(iter);
		iter->Draw();
	}
}

void CSceneBase::AppendChild(shared_ptr<CGameObject> spGameObject)
{
	m_gameObjectVec.push_back(spGameObject);
}

void CSceneBase::RemoveChild(shared_ptr<CGameObject> spGameObject)
{
	auto iter = find(m_gameObjectVec.begin(), m_gameObjectVec.end(), spGameObject);
	if (iter != m_gameObjectVec.end()) 
	{
		m_gameObjectVec.erase(iter);
	}
}

void CSceneBase::RemoveChild(const string & name)
{
	auto iter = m_gameObjectVec.begin();
	while (iter != m_gameObjectVec.end())
	{
		CGameObject* pGameObject = iter->get();
		if (pGameObject)
		{
			if (pGameObject->GetName() == name)
			{
				m_gameObjectVec.erase(iter);
				break;
			}
		}
		++iter;
	}
}

void CSceneBase::RemoveChild(const string tagName)
{
	auto iter = m_gameObjectVec.begin();
	while (iter != m_gameObjectVec.end())
	{
		CGameObject* pGameObject = iter->get();
		if (pGameObject)
		{
			if (pGameObject->GetTagName() == tagName)
			{
				m_gameObjectVec.erase(iter);
				break;
			}
		}
		++iter;
	}
}
