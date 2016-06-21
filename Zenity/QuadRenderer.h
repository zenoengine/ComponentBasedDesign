#pragma once
#include "ComponentBase.h"

class CTransform;

class CQuadRenderer : public CComponentBase
{
private:
	weak_ptr<LPDIRECT3DTEXTURE9> m_wpTexture;
	weak_ptr<CTransform> m_wpTransform;
	RECT m_rect;
	D3DXCOLOR m_color;

public:
	CQuadRenderer();
	virtual ~CQuadRenderer();

	const ComponentFamilyType GetFamilyComponentType() const final;
	void Init() override;
	void Update() override;
	void Clear() override;

	void SetTexture(const wstring& textureName);
	void SetTexture(shared_ptr<LPDIRECT3DTEXTURE9> spTexture);
	weak_ptr<LPDIRECT3DTEXTURE9> GetTexture();

	inline void SetColor(const D3DXCOLOR& color) { m_color = color; }
	inline const D3DXCOLOR& GetColor() { return m_color; }

	inline void SetRect(const RECT& rect) { m_rect = rect; }
	inline const RECT& GetRect() const { return m_rect; }

	void Draw();
};