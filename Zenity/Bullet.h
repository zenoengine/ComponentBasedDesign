#pragma once
#include "ComponentBase.h"

class CBullet : public CComponentBase
{
private:
	D3DXVECTOR3 m_vDir;
	weak_ptr<CTransform> m_wpTransform;

public:
	CBullet();
	virtual ~CBullet();

	void Init() override;
	void Update() override;
};

