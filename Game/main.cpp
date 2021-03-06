#include "Graphics.h"
#include <Windows.h>
#include "IO.h"
#include <sys\timeb.h> 

int timeDiff(timeb firstTime, timeb secondTime)
{
	int secDiff = (int)(secondTime.time - firstTime.time);
	int milliSecDiff = secDiff * 1000 + (secondTime.millitm - firstTime.millitm);
	return milliSecDiff;
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	IO* io = new IO();
	std::string windowName = "Game";

	HWND hWnd = InitWindow(&hInstance, windowName, io);

	Game *game = new Game(hWnd);
	io->InitIO(game);

	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	while (true)
	{
		struct timeb start, end;
		ftime(&start);

		game->Run();
		game->DrawScreen();
		if (game->GetGameOver())
		{
			io->EndGame();
		}
		MSG msg = { 0 };
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
		ftime(&end);
		int sleepTime = max(game->GetSleepTimeInMs() - timeDiff(start, end), 0);
		Sleep(sleepTime);
	}
	return 0;
}