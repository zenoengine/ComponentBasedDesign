#include "stdafx.h"
#include "BulletSpawner.h"
#include "Bullet.h"
#include "QuadRenderer.h"
#include "Transform.h"


CBulletSpawner::CBulletSpawner()
{
}

CBulletSpawner::~CBulletSpawner()
{
}

void CBulletSpawner::Init()
{
	m_wpTransform = m_thisGameObject->GetComponent<CTransform>();

	//HACK : Not yet, Dosen't exist method like Removechild(). so intead of activate/deactivate method
	for (int idx = 0; idx < 50; idx++)
	{
		shared_ptr<CGameObject> spGameObject = make_shared<CGameObject>();
		assert(spGameObject);
		
		shared_ptr<CBullet> spBullet = make_shared<CBullet>();
		assert(spBullet);
		spGameObject->AddComponent(spBullet);

		shared_ptr<CQuadRenderer> spQuadRenderer = make_shared<CQuadRenderer>();
		assert(spQuadRenderer != nullptr);
		spQuadRenderer->SetTexture(L"../Bin/Resource/Texture/Bullet.png");
		spGameObject->AddComponent(spQuadRenderer);

		InitBulletPosition(spGameObject);

		spGameObject->SetActive(false);
		m_thisGameObject->AppendChild(spGameObject);
		m_bulletVec.push_back(spGameObject);
	}
}

void CBulletSpawner::Update()
{
	m_dwTicker += 1;
	if (m_dwTicker > 5)
	{
		for (auto iter : m_bulletVec)
		{
			if (!iter->IsActive())
			{
				iter->SetActive(true);
				InitBulletPosition(iter);
				break;
			}
		}

		m_dwTicker = 0;
	}
}

void CBulletSpawner::Clear()
{
}

void CBulletSpawner::InitBulletPosition(weak_ptr<CGameObject> wpBullet)
{
	if (wpBullet.expired())
	{
		return;
	}

	shared_ptr<CGameObject> spGameObject = wpBullet.lock();

	weak_ptr<CTransform> wpTransform = spGameObject->GetComponent<CTransform>();
	if (!wpTransform.expired())
	{
		shared_ptr<CTransform> spTransform = wpTransform.lock();

		if (!m_wpTransform.expired())
		{
			spTransform->SetPosition(m_wpTransform.lock()->GetPosition());
		}
	}
}
