#include "IO.h"

const int ID_NEW_GAME = 0;
const int ID_EXIT = 1;
const int ID_HELP = 10;
const int ID_CONTROLS = 11;

struct PlayerInput
{
	int up;
	int down;
	int right;
	int left;
	PlayerInput() {};
	PlayerInput(int upIn, int downIn, int rightIn, int leftIn)
	{
		up = upIn;
		down = downIn;
		right = rightIn;
		left = leftIn;
	}
};

Game* IO::_game;

const PlayerInput playerInput =
PlayerInput(VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT);

IO::IO()
{}

void IO::InitIO(Game* game)
{
	_game = game;
}

void IO::SetKeyAction(Game* game, bool keyDown, WPARAM wParam)
{
	if (wParam == playerInput.right)
	{
		_game->SetPlayerKeyDown(Game::EAST, keyDown);
	}
	if (wParam == playerInput.left)
	{
		_game->SetPlayerKeyDown(Game::WEST, keyDown);
	}
	if (wParam == playerInput.up)
	{
		_game->SetPlayerKeyDown(Game::NORTH, keyDown);
	}
	if (wParam == playerInput.down)
	{
		_game->SetPlayerKeyDown(Game::SOUTH, keyDown);
	}
}

void InitWinMain(HINSTANCE* hInst, std::string winName, IO* io)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = io->MsgProc;
	wc.hInstance = *hInst;
	wc.lpszClassName = winName.c_str();
	wc.hCursor = (HCURSOR)LoadCursor(0, IDC_ARROW);
	RegisterClass(&wc);
}

HWND InitWindow(HINSTANCE* hInst, std::string winName, IO* io)
{
	InitWinMain(hInst, winName, io);

	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	RECT windowRect = { 1, 1, Player::SCREENXSIZE*Map::TILESIZE, Player::SCREENYSIZE*Map::TILESIZE };
	AdjustWindowRect(&windowRect, windowStyle, false);
	HWND hWnd = CreateWindow(
		winName.c_str(),
		winName.c_str(),
		windowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		*hInst,
		NULL);

	return hWnd;
}

LRESULT CALLBACK IO::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		SetKeyAction(_game, true, wParam);
		break;
	}
	case WM_KEYUP:
	{
		SetKeyAction(_game, false, wParam);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		ValidateRect(hWnd, 0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void IO::EndGame()
{
	std::string text = "Spelet är slut." 
		"\nVill du spela en ny omgång?";
	int result = MessageBox(NULL, text.c_str(),
		"Spelet Slut", MB_YESNO);
	if (result == IDYES)
	{
		//TODO
	}
	else if (result == IDNO)
	{
		PostQuitMessage(0);
	}
}