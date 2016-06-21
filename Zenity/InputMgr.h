#pragma once

class CInputMgr
{
private:
	bool m_keys[256];

public:
	CInputMgr();
	~CInputMgr();

	static CInputMgr* GetInstance();

	bool Init();
	void Release();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

};

#define g_pInputMgr CInputMgr::GetInstance()
