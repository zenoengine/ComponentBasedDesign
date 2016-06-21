#include "stdafx.h"
#include "Transform.h"

CTransform::CTransform()
	: m_vPosition(0,0,0)
	, m_vRotation(0,0,0)
{
}

CTransform::~CTransform()
{
}

const ComponentFamilyType CTransform::GetFamilyComponentType() const
{
	return ComponentFamilyType::TRANSFORM;
}

void CTransform::Init()
{
}

void CTransform::Update()
{
}

void CTransform::Clear()
{
}

const D3DXVECTOR3 & CTransform::GetPosition() const
{
	return m_vPosition;
}

const D3DXVECTOR3 & CTransform::GetRotation() const
{
	return m_vRotation;
}
