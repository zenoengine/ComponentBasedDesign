#include "stdafx.h"
#include "Device.h"

CDevice::~CDevice()
{
}

CDevice* CDevice::GetInstance()
{
	static CDevice Instance;
	return &Instance;
}

bool CDevice::Init(HINSTANCE hInst, HWND hWnd, UINT Width, UINT Height)
{
	// Init의 인자를 클래스 내의 인자로 복사한다.
	m_hInst = hInst;
	m_hWnd = hWnd;
	m_Width = Width;
	m_Height = Height;

	/// 디바이스를 생성하기위한 D3D객체 생성
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return false;

	/// 디바이스를 생성할 구조체
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pd3dDevice)))
	{
		return false;
	}

	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_pSprite)))
	{
		return false;
	}

	return true;
}

void CDevice::Release()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_pD3D);
}

void CDevice::SetResolution(LONG Width, LONG Height)
{
	DWORD style = (DWORD)GetWindowLongPtr(m_hWnd, GWL_STYLE);

	RECT rc = { 0, 0, Width, Height };
	AdjustWindowRect(&rc, style, false);

	m_RealWindowWidth = rc.right - rc.left;
	m_RealWindowHeight = rc.bottom - rc.top;

	m_Width = Width;
	m_Height = Height;

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(m_hWnd, HWND_NOTOPMOST, cx / 2 - m_RealWindowWidth / 2, cy / 2 - m_RealWindowHeight / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);
}


bool CDevice::IsThisHwnd(HWND hWnd)
{
	HWND SelecthWnd = hWnd;
	while (SelecthWnd)
	{
		if (SelecthWnd == m_hWnd)
			return true;

		SelecthWnd = GetParent(SelecthWnd);
	}

	return false;
};