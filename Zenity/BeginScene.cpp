#include "stdafx.h"
#include "BeginScene.h"
#include "Camera.h"
#include "Transform.h"
#include "QuadRenderer.h"
#include "PlayerController.h"
#include "BulletSpawner.h"

CBeginScene::CBeginScene()
{
}

CBeginScene::~CBeginScene()
{
}

void CBeginScene::Init()
{
	InitPlayerCharacter();
	InitBulletSpawner();
}

void CBeginScene::InitPlayerCharacter()
{
	shared_ptr<CGameObject> spPlayerObject = make_shared<CGameObject>();
	assert(spPlayerObject != nullptr);

	spPlayerObject->Init();
	spPlayerObject->SetName("Player").SetTagName("Player");

	shared_ptr<CQuadRenderer> spQuadRenderer = make_shared<CQuadRenderer>();
	assert(spQuadRenderer != nullptr);
	spQuadRenderer->SetTexture(L"../Bin/Resource/Texture/Player.png");
	spPlayerObject->AddComponent(spQuadRenderer);

	shared_ptr<CPlayerController> spPlayerController = make_shared<CPlayerController>();
	assert(spPlayerController != nullptr);
	spPlayerObject->AddComponent(spPlayerController);

	weak_ptr<CTransform> wpTransform = spPlayerObject->GetComponent<CTransform>();
	shared_ptr<CTransform> spTransform = wpTransform.lock();
	assert(spTransform != nullptr);
	spTransform->SetPosition(D3DXVECTOR3(100, 100, 0));

	//TODO(make more) : Replace SceneGraph SceneBase->AppendChild(PlayerCharacterObject)
	AppendChild(spPlayerObject);
}

void CBeginScene::InitBulletSpawner()
{
	shared_ptr<CGameObject> spBulletSpawner = make_shared<CGameObject>();
	assert(spBulletSpawner != nullptr);
	spBulletSpawner->Init();
	spBulletSpawner->SetName("BulletSpawner").SetTagName("BulletSpawner");

	shared_ptr<CBulletSpawner> spBulletSpawnerComponent = make_shared<CBulletSpawner>();
	assert(spBulletSpawnerComponent != nullptr);
	spBulletSpawner->AddComponent(spBulletSpawnerComponent);

	weak_ptr<CTransform> wpTransform = spBulletSpawner->GetComponent<CTransform>();
	shared_ptr<CTransform> spTransform = wpTransform.lock();
	assert(spTransform != nullptr);
	spTransform->SetPosition(D3DXVECTOR3(300, 300, 0));

	//TODO(make more) : Replace SceneGraph SceneBase->AppendChild(PlayerCharacterObject)
	AppendChild(spBulletSpawner);
}

void CBeginScene::Clear()
{

}