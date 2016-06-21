#include "stdafx.h"
#include "Game.h"
#include "Device.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "TextureMgr.h"

CGame::CGame() 
: m_hInstance(0)
, m_hwnd(0)
, m_nCmd(0)
{
}


CGame::~CGame()
{
}


bool CGame::Initialize(HINSTANCE hInstance, LPSTR pScmdline, int iCmdshow, LPCWSTR applicationName)
{
	m_hInstance = hInstance;
	m_applicationName = applicationName;

	int screenWidth = 0;
	int screenHeight = 0;

	if (InitializeWindow(pScmdline, iCmdshow, screenWidth, screenHeight) != true)
	{
		assert(false);
		return false;
	}

	if (g_pDevice == nullptr ||
		g_pInputMgr == nullptr ||
		g_pSceneMgr == nullptr ||
		g_pTextureMgr == nullptr)
	{
		assert(false);
		return false;
	}

	bool result = false;
	result =   (g_pDevice->Init(hInstance, m_hwnd, screenWidth, screenHeight) &&
				g_pInputMgr->Init() &&
				g_pSceneMgr->Init() &&
				g_pTextureMgr->Init());
	
	//TODO : Replace function LoadScene(0) (load by Index)
	g_pSceneMgr->LoadScene("BeginScene");
	return result;
}


bool CGame::InitializeWindow(LPSTR pScmdline, int iCmdShow, int& screenWidth, int& screenHeight)
{
	ApplicationHandle = this;

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = m_hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = m_applicationName;

	RegisterClassEx(&wc);

	m_hwnd = CreateWindowEx(NULL,
		m_applicationName,    // name of the window class
		m_applicationName,   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		300,    // x-position of the window
		300,    // y-position of the window
		500,    // width of the window
		400,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		m_hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	DWORD errorCode = GetLastError();

	// display the window on the screen
	ShowWindow(m_hwnd, iCmdShow);

	bool result = (errorCode == 0);
	return result;
}


void CGame::Shutdown()
{
	g_pTextureMgr->Release();
	g_pSceneMgr->Release();
	g_pInputMgr->Release();
	g_pDevice->Release();
	
	ShutdownWindow();
	
	return;
}


void CGame::Run()
{
	MSG msg;
	bool bRequestExit = false;
	ZeroMemory(&msg, sizeof(MSG));

	while(!bRequestExit)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			bRequestExit = true;
		}
		else
		{
			if(!Frame())
			{
				bRequestExit = true;
			}
		}
	}

	return;
}


bool CGame::Frame()
{
	Update();
	Draw();

	return true;
}

bool CGame::Update()
{
	for (auto it : CSceneMgr::GetInstance()->m_loadedSceneMap)
	{
		shared_ptr<ISceneBase> spSceneBase = it.second;
		if (spSceneBase)
		{
			spSceneBase->Update();
		}
	}

	return true;
}

void CGame::Draw()
{
	if (!g_pd3dDevice)
	{
		return;
	}

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		for (auto &iter : CSceneMgr::GetInstance()->m_loadedSceneMap)
		{
			shared_ptr<ISceneBase> spScene = iter.second;
			if (spScene)
			{
				spScene->Draw();
			}
		}
	}

	g_pd3dDevice->EndScene();
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}


LRESULT CALLBACK CGame::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch(umsg)
	{
		case WM_KEYDOWN:
		{
			g_pInputMgr->KeyDown((unsigned int)wparam);
			return 0;
		}

		case WM_KEYUP:
		{
			g_pInputMgr->KeyUp((unsigned int)wparam);
			return 0;
		}

		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}


void CGame::ShutdownWindow()
{
	ShowCursor(true);
	DestroyWindow(m_hwnd);
	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = NULL;
	ApplicationHandle = NULL;
	m_hwnd = NULL;

	return;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}

	return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
}