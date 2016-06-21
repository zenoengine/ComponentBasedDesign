#pragma once
#include "Device.h"
#include "ComponentBase.h"

class CCamera : public CComponentBase
{
private:
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vLookAt;
	D3DXVECTOR3 m_vRight;

	D3DXMATRIXA16		m_matView;
	D3DXMATRIXA16		m_matProj;

public:
	CCamera();
	~CCamera();

	const ComponentFamilyType GetFamilyComponentType() const final;
	void Init() override;
	void Update() override;
	void Clear() override;

	void UpdateView();

	const D3DXMATRIXA16& GetViewMatrix() const { return m_matView; }
	const D3DXMATRIXA16& GetProjMatrix() const { return m_matProj; }
	const D3DXVECTOR3& GetvEye() const { return m_vEye; }
};

