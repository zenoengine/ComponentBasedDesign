#pragma once
#include "ComponentBase.h"
#include "Device.h"

class CTransform : public CComponentBase
{
private:
	D3DXVECTOR3 m_vPosition;
	D3DXVECTOR3 m_vRotation;

public:
	CTransform();
	virtual ~CTransform();

	const ComponentFamilyType GetFamilyComponentType() const final;
	void Init() override;
	void Update() override;
	void Clear() override;

	inline void Translate(const D3DXVECTOR3& addPos) { m_vPosition += addPos; }
	inline void SetPosition(const D3DXVECTOR3& pos) { m_vPosition = pos; }

	const D3DXVECTOR3& GetPosition() const;
	const D3DXVECTOR3& GetRotation() const;
};