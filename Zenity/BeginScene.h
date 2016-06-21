#pragma once
#include "SceneBase.h"

class CBeginScene : public CSceneBase
{
private:
	void InitPlayerCharacter();
	void InitBulletSpawner();

public:
	CBeginScene();
	virtual ~CBeginScene();

	void Init() override;
	void Clear() override;
};

static SceneRegistrar<CBeginScene> registrar("BeginScene");