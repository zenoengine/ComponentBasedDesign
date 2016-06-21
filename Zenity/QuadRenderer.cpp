#include "stdafx.h"
#include "QuadRenderer.h"
#include "Device.h"
#include "TextureMgr.h"
#include "GameObject.h"
#include "Transform.h"

CQuadRenderer::CQuadRenderer()
	: m_color(255, 255, 255, 255)
{
	m_rect = { 0, 0, 256, 256 };
}

CQuadRenderer::~CQuadRenderer()
{
}

const ComponentFamilyType CQuadRenderer::GetFamilyComponentType() const
{
	return ComponentFamilyType::RENDERER;
}

void CQuadRenderer::Init()
{
	if (m_thisGameObject == nullptr)
	{
		return;
	}

	m_wpTransform = m_thisGameObject->GetComponent<CTransform>();
}

void CQuadRenderer::Update()
{
}

void CQuadRenderer::Clear()
{
	m_wpTransform.reset();
	m_wpTexture.reset();
}

void CQuadRenderer::SetTexture(const wstring & textureName)
{
	m_wpTexture = g_pTextureMgr->GetTexture(textureName.c_str());
}

void CQuadRenderer::SetTexture(shared_ptr<LPDIRECT3DTEXTURE9> spTexture)
{
	m_wpTexture = spTexture;
}

weak_ptr<LPDIRECT3DTEXTURE9> CQuadRenderer::GetTexture()
{
	return m_wpTexture;
}

void CQuadRenderer::Draw()
{
	if (m_wpTexture.expired() || m_wpTransform.expired())
	{
		return ;
	}

	shared_ptr<LPDIRECT3DTEXTURE9> spTexture = m_wpTexture.lock();
	shared_ptr<CTransform> spTransform= m_wpTransform.lock();

	if (SUCCEEDED(g_pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE)))
	{
		//TODO : Replace member variable
		LONG width = m_rect.right - m_rect.left;
		LONG height = m_rect.bottom - m_rect.top;
		
		const D3DXVECTOR3& pos = spTransform->GetPosition();
		g_pd3dSprite->Draw(*spTexture.get(), &m_rect, &D3DXVECTOR3((float)width/2, (float)height/2, 0), &pos, D3DXCOLOR(255,255,255,255));
	}

	g_pd3dSprite->End();
}
