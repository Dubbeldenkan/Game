#include "Input.h"

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

Game* Input::_game;

const PlayerInput playerInput =
PlayerInput(VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT);

Input::Input()
{}

void Input::InitInput(Game* game)
{
	_game = game;
}

void Input::SetKeyAction(Game* game, bool keyDown, WPARAM wParam)
{
	//TODO
}

void InitWinMain(HINSTANCE* hInst, char* winName, Input* input)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = input->MsgProc;
	wc.hInstance = *hInst;
	wc.lpszClassName = winName;
	wc.hCursor = (HCURSOR)LoadCursor(0, IDC_ARROW);
	RegisterClass(&wc);
}

HWND InitWindow(HINSTANCE* hInst, char* winName, Input* input)
{
	InitWinMain(hInst, winName, input);

	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	RECT windowRect = { 1, 1, Map::MAPXSIZE*Map::TILESIZE, Map::MAPXSIZE*Map::TILESIZE};
	AdjustWindowRect(&windowRect, windowStyle, false);
	HWND hWnd = CreateWindow(
		winName,
		winName,
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

LRESULT CALLBACK Input::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

void Input::EndGame()
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