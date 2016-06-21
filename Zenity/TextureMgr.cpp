#include "stdafx.h"
#include "TextureMgr.h"
#include "Device.h"

LPDIRECT3DTEXTURE9 CTextureMgr::LoadTexture(const WCHAR * filename, D3DCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	D3DXIMAGE_INFO texture_info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filename, &texture_info);
	if (result != D3D_OK)
		return nullptr;

	result = D3DXCreateTextureFromFileEx(g_pd3dDevice, filename, texture_info.Width, texture_info.Height, 1, 0, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, transcolor, NULL, NULL, &texture);
	if (result != D3D_OK)
		return nullptr;

	return texture;
}

CTextureMgr::CTextureMgr()
{
}

CTextureMgr::~CTextureMgr()
{
}

CTextureMgr * CTextureMgr::GetInstance()
{
	static CTextureMgr instance;
	return &instance;
}

bool CTextureMgr::Init()
{
	//TODO : load from file.

	vector<wstring> tempTextureNameVec;
	tempTextureNameVec.push_back(L"../Bin/Resource/Texture/Player.png");
	tempTextureNameVec.push_back(L"../Bin/Resource/Texture/Bullet.png");

	for (auto iter : tempTextureNameVec)
	{
		WCHAR fileName[256] = {0,};
		lstrcpyW(fileName, iter.c_str());
		LPDIRECT3DTEXTURE9 pTexture = LoadTexture(fileName, 0);
		
		if (pTexture != nullptr)
		{
			m_textureMap.insert(make_pair(fileName, make_shared<LPDIRECT3DTEXTURE9>(pTexture)));
		}
	}
	return true;
}

void CTextureMgr::Release()
{
	for (auto iter : m_textureMap)
	{
		LPDIRECT3DTEXTURE9 pTexture = *iter.second;
		if (pTexture)
		{
			pTexture->Release();
		}
		iter.second.reset();
	}

	m_textureMap.clear();
}

shared_ptr<LPDIRECT3DTEXTURE9> CTextureMgr::GetTexture(const WCHAR * fileName)
{
	auto iter = m_textureMap.find(fileName);

	if (iter != m_textureMap.end())
	{
		return iter->second;
	}

	return nullptr;
}
