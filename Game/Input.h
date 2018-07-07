#ifndef INPUT_H
#define INPUT_H

#include <Windows.h>

#include "Game.h"
#include "Draw.h"
#include "HelpStructs.h"

class Input
{
private:
	static Game* _game;

public:
	Input();
	~Input() {};

	void InitInput(Game*);
	void EndGame();

	static LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);
	static void SetKeyAction(Game* game, bool keyDown, WPARAM);
};

void InitWinMain(HINSTANCE*, char*, Input*);

HWND InitWindow(HINSTANCE*, char*, Input*);

#endif // !CONTROL_H