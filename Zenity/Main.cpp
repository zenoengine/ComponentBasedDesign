#pragma once
#include "stdafx.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pScmdline, int iCmdshow)
{
	unique_ptr<CGame> spGame = make_unique<CGame>();
	assert(spGame != nullptr);
	if(spGame->Initialize(hInstance, pScmdline, iCmdshow))
	{
		spGame->Run();
	}
	spGame->Shutdown();
	spGame.reset();

	return 0;
}