// Game.cpp : Defines the entry point for the console application.
//

#include "Game.h"
#include "Input.h"
#include "Map.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	char windowName[] = "Game";
	Input* input = new Input();

	HWND hWnd = InitWindow(&hInstance, windowName, input);

	Game* game = new Game(hWnd);
	int sleepTime = 100;

	input->SetGame(game);

	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	bool isRunning = true;
	while (true)
	{
		game->Run();
		msg = { 0 };
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
		}
		Sleep(sleepTime);
	}
	return 0;
}