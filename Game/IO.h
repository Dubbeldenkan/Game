#ifndef IO_H
#define IO_H

#include <Windows.h>

#include "Game.h"
#include "Draw.h"
#include "HelpStructs.h"

class IO
{
private:
	static Game* _game;

public:
	IO();
	~IO() {};

	void InitIO(Game*);
	void EndGame();

	static LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);
	static void SetKeyAction(Game* game, bool keyDown, WPARAM);
};

void InitWinMain(HINSTANCE*, std::string, IO*);

HWND InitWindow(HINSTANCE*, std::string, IO*);

#endif // !CONTROL_H