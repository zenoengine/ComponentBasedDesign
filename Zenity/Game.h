#pragma once

class SceneMgr;
class ISceneBase;

class CGame
{
private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hwnd;
	int m_nCmd;
	
public:
	CGame();
	~CGame();

	bool Initialize(HINSTANCE hInstance, LPSTR pScmdline, int iCmdshow, LPCWSTR applicationName = L"Zenity");
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool InitializeWindow(LPSTR pScmdline, int iCmdShow, int& outScreenWidth, int& outScrennHeight);
	void ShutdownWindow();

	bool Frame();
	bool Update();
	void Draw();
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static CGame* ApplicationHandle = 0;