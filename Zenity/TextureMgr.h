#pragma once
#include <unordered_map>

class CTextureMgr
{
private:
	unordered_map<wstring, shared_ptr<LPDIRECT3DTEXTURE9>> m_textureMap;
	
private:
	CTextureMgr();
	~CTextureMgr();

public:
	static CTextureMgr* GetInstance();

	bool Init();
	void Release();

	LPDIRECT3DTEXTURE9 LoadTexture(const WCHAR *filename, D3DCOLOR transcolor);
	shared_ptr<LPDIRECT3DTEXTURE9> GetTexture(const WCHAR* fileName);
};

#define g_pTextureMgr CTextureMgr::GetInstance()