#pragma once
#include "ComponentBase.h"

class CPlayerController : public CComponentBase
{
private:
	weak_ptr<CTransform> m_wpTransform;
	float m_fSpeed;

private:
	void UpdateMovement();

public:
	CPlayerController();
	virtual ~CPlayerController();

	void Init() override;
	void Update() override;
	void Clear() override;
};