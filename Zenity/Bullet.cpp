#include "stdafx.h"
#include "Bullet.h"
#include "Transform.h"


CBullet::CBullet()
	: m_vDir(0,0,0)
{
}


CBullet::~CBullet()
{
}

void CBullet::Init()
{
	float randX = 0;
	float randY = 0;
	while (randX == 0 && randY == 0)
	{
		randX = (int)rand() % 4 - 2;
		randY = (int)rand() % 4 - 2;
	}

	m_vDir.x = randX;
	m_vDir.y = randY;

	m_wpTransform = m_thisGameObject->GetComponent<CTransform>();
}

void CBullet::Update()
{
	if (!m_wpTransform.expired())
	{
		shared_ptr<CTransform> spTransform = m_wpTransform.lock();
		spTransform->Translate(m_vDir);

		const D3DXVECTOR3& pos = spTransform->GetPosition();

		//HACK : Not yet, Dosen't exist method like Removechild(). so intead of activate/deactivate method
		if (pos.x < 0 || pos.x > 500)
		{
			m_thisGameObject->SetActive(false);
		}
		if (pos.y < 0 || pos.y > 500)
		{
			m_thisGameObject->SetActive(false);
		}
	}
}
