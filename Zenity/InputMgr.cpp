#include "stdafx.h"
#include "InputMgr.h"

CInputMgr::CInputMgr()
{
}


CInputMgr::~CInputMgr()
{
}


CInputMgr* CInputMgr::GetInstance()
{
	static CInputMgr Instance;
	return &Instance;
}

bool CInputMgr::Init()
{
	// Initialize all the keys to being released and not pressed.
	for(int i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}

	return true;
}


void CInputMgr::Release()
{
	for (int i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}
}

void CInputMgr::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array.
	m_keys[input] = true;
	return;
}


void CInputMgr::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array.
	m_keys[input] = false;
	return;
}


bool CInputMgr::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return m_keys[key];
}