#pragma once
#include "ComponentBase.h"

class CBulletSpawner : public CComponentBase
{
private:
	DWORD m_dwTicker;
	weak_ptr<CTransform> m_wpTransform;

	vector<shared_ptr<CGameObject>> m_bulletVec;

	void InitBulletPosition(weak_ptr<CGameObject> wpBullet);
public:
	CBulletSpawner();
	virtual ~CBulletSpawner();

	void Init() override;
	void Update() override;
	void Clear() override;
};

