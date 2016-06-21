#include "stdafx.h"
#include "ComponentBase.h"

CComponentBase::CComponentBase()
{
}

CComponentBase::~CComponentBase()
{
}

const ComponentFamilyType CComponentBase::GetFamilyComponentType() const
{
	return ComponentFamilyType::DEFAULT;
}

void CComponentBase::SetParent(CGameObject* pGameObject)
{
	m_thisGameObject = pGameObject;
}