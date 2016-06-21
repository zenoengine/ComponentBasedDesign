#include "stdafx.h"
#include "PlayerController.h"
#include "GameObject.h"
#include "Transform.h"

CPlayerController::CPlayerController()
	: m_fSpeed(5)
{
}

CPlayerController::~CPlayerController()
{
}

void CPlayerController::Init()
{
	assert(m_thisGameObject != nullptr);

	m_wpTransform = m_thisGameObject->GetComponent<CTransform>();
}

void CPlayerController::Update()
{
	if (m_wpTransform.expired())
	{
		return;
	}

	UpdateMovement();
}

void CPlayerController::UpdateMovement()
{
	shared_ptr<CTransform> spTransform = m_wpTransform.lock();
	D3DXVECTOR3 addPos(0, 0, 0);
	if (g_pInputMgr->IsKeyDown(VK_RIGHT))
	{
		addPos.x += 1;
	}

	if (g_pInputMgr->IsKeyDown(VK_LEFT))
	{
		addPos.x += -1;
	}

	if (g_pInputMgr->IsKeyDown(VK_UP))
	{
		addPos.y -= 1;
	}

	if (g_pInputMgr->IsKeyDown(VK_DOWN))
	{
		addPos.y += 1;
	}

	D3DXVec3Normalize(&addPos, &addPos);

	spTransform->Translate(addPos * m_fSpeed);
}

void CPlayerController::Clear()
{
}