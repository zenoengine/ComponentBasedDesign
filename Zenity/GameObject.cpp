#include "stdafx.h"
#include "GameObject.h"
#include "ComponentBase.h"
#include "Transform.h"
#include "QuadRenderer.h"

unsigned int CGameObject::g_objectuuid = 0;

CGameObject::CGameObject()
	: m_bIsActive(true)
{
	CGameObject::g_objectuuid += 1;
	m_uuid = CGameObject::g_objectuuid;

	shared_ptr<CTransform> spTransform = make_shared<CTransform>();
	if (spTransform != nullptr)
	{
		spTransform->Init();
		this->AddComponent(spTransform);
	}
}

CGameObject::~CGameObject()
{
	m_componentVec.clear();
}

CGameObject & CGameObject::SetTagName(const string & tagName)
{
	m_strTagName = tagName;

	return (*this);
}

CGameObject & CGameObject::SetName(const string & tagName)
{
	m_strName = tagName;
	return (*this);
}

void CGameObject::UpdateComponent()
{
	for(auto it : m_componentVec) 
	{
		shared_ptr<CComponentBase> spComponent = it;

		if (spComponent) 
		{
			spComponent->Update();
		}
	}
	
}

void CGameObject::AddComponent(shared_ptr<CComponentBase> spComponent)
{
	if (spComponent == nullptr)
	{
		return;
	}

	spComponent->SetParent(this);
	spComponent->Init();
	m_componentVec.push_back(spComponent);
}

void CGameObject::Init()
{
}

void CGameObject::Update()
{
	if(!m_bIsActive)
	{
		return;
	}

	for(auto it : m_componentVec)
	{
		auto spComponent = it;
		if (spComponent)
		{
			spComponent->Update();
			UpdateChild();
		}
	}
}

void CGameObject::Draw()
{
	if (!m_bIsActive)
	{
		return;
	}

	weak_ptr<CQuadRenderer> wpQuadRenderer = GetComponent<CQuadRenderer>();
	if (wpQuadRenderer.expired() != true)
	{
		shared_ptr<CQuadRenderer> spRenderer = wpQuadRenderer.lock();
		spRenderer->Draw();
	}

	DrawChild();
}

void CGameObject::Clear()
{
	ClearComponentMap();
}

void CGameObject::UpdateChild()
{
	for (auto iter : m_gameObjectVec)
	{
		if (iter)
		{
			iter->Update();
		}
	}
}

void CGameObject::DrawChild()
{
	for (auto iter : m_gameObjectVec)
	{
		if (iter)
		{
			iter->Draw();
		}
	}
}

void CGameObject::ClearChild()
{
	for (auto iter : m_gameObjectVec)
	{
		iter->Clear();
	}
	m_gameObjectVec.clear();
}

void CGameObject::AppendChild(shared_ptr<CGameObject> spGameObject)
{
	m_gameObjectVec.push_back(spGameObject);
}

void CGameObject::RemoveChild(shared_ptr<CGameObject> spGameObject)
{
	auto iter = find(m_gameObjectVec.begin(), m_gameObjectVec.end(), spGameObject);
	if (iter != m_gameObjectVec.end())
	{
		m_gameObjectVec.erase(iter);
	}
}

void CGameObject::ClearComponentMap()
{
	for (auto it : m_componentVec)
	{
		auto spComponent = it;
		if (spComponent)
		{
			spComponent->Clear();
		}
	}

	m_componentVec.clear();
}