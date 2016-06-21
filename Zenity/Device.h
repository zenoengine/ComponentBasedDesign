#pragma once
#include "stdafx.h"

class CDevice
{
private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	UINT m_Width, m_Height;
	UINT m_RealWindowWidth, m_RealWindowHeight;

	LPDIRECT3D9             m_pD3D;
	LPDIRECT3DDEVICE9       m_pd3dDevice;
	
	LPD3DXSPRITE  m_pSprite;
private:
	CDevice() {};

public:
	static CDevice* GetInstance();

	virtual ~CDevice();

	bool Init(HINSTANCE hInst, HWND hWnd, UINT Width, UINT Height);
	void Release();

	void SetResolution(LONG Width, LONG Height);

	bool IsThisHwnd(HWND hWnd);

	LPDIRECT3DDEVICE9 GetD3DDevice() { return m_pd3dDevice; }
	LPD3DXSPRITE GetD3DSprite() { return m_pSprite; }

	UINT GetWidth() { return m_Width; }
	UINT GetHeight() { return m_Height; }

	UINT GetWindowWidth() { return m_Width; }
	UINT GetWindowHeight() { return m_Height; }

	UINT GetRealWindowWidth() { return m_RealWindowWidth; }
	UINT GetRealWindowHeight() { return m_RealWindowHeight; }

	HINSTANCE GetWinInst() { return m_hInst; }
	HWND GetHwnd() { return m_hWnd; };
};

//TODO : TextureMgr Á¦ÀÛ
#define g_pDevice CDevice::GetInstance()
#define g_pd3dDevice CDevice::GetInstance()->GetD3DDevice()
#define g_pd3dSprite CDevice::GetInstance()->GetD3DSprite()