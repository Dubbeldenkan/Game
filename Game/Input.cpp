#include "Input.h"

Game* Input::_game;
Draw::Pos Input::_mousePos = Draw::Pos(0, 0);

Input::Input()
{}

void Input::MouseClick()
{
	
}

void Input::SetGame(Game* game)
{
	_game = game;
}

LRESULT CALLBACK Input::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM
	lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		MouseClick();
		break;
	}
	case WM_MOUSEMOVE:
	{
		_mousePos.x = LOWORD(lParam);
		_mousePos.y = HIWORD(lParam);
		break;
	}
	case WM_KEYDOWN :
	{
		switch (wParam)
		{
		case VK_SPACE:
		{
			break;
		}
		default:
			break;
		}
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

void InitWinMain(HINSTANCE* hInst, char winName[], Input* input)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = input->MsgProc;
	wc.hInstance = *hInst;
	wc.lpszClassName = winName;
	wc.hCursor = (HCURSOR)LoadCursor(0, IDC_ARROW);
	RegisterClass(&wc);
}

HWND InitWindow(HINSTANCE* hInst, char winName[], Input* input)
{
	InitWinMain(hInst, winName, input);

	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	RECT windowRect = { 1, 1, 1300, 660 };
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