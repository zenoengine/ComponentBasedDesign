#include "Camera.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

void CCamera::Init()
{
	m_vEye = D3DXVECTOR3(-5.0f, 3.0f, -1.0f);
	m_vLookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vDir = m_vLookAt - m_vEye;

	D3DXVec3Cross(&m_vRight, &m_vDir, &m_vUp);
	D3DXVec3Normalize(&m_vRight, &m_vRight);
	D3DXVec3Normalize(&m_vDir, &m_vDir);

	D3DXMatrixIdentity(&m_matProj);
	D3DXMatrixIdentity(&m_matView);

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookAt, &m_vUp);	/// 1,2,3의 값으로 뷰행렬 생성
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &m_matView);				/// 생성한 뷰행렬을 디바이스에 설정
}

void CCamera::Update()
{
	UpdateView();
}

void CCamera::Clear()
{
}

const ComponentType CCamera::GetFamilyComponentType() const
{
	return ComponentType::CAMERA;
}

void CCamera::UpdateView()
{
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &m_matView);
}
