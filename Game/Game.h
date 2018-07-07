#ifndef GAME_H
#define GAME_H

#include "Draw.h"
#include "Map.h"

#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h> 

class Game
{
public:
	enum PlayerControl { EAST, WEST, NORTH, SOUTH};

private:
	Draw _draw = Draw();
	Map _map = Map();

	static const int _sleepTimeInMs = 10;
	bool _gameOver = false;

public:
	Game(HWND);
	~Game() {};

	void Run();
	void DrawGameBoard();

	int GetSleepTimeInMs();
	bool GetGameOver();
	void InitGame();

private:
	Draw* GetDraw();
};

#endif // !GAME_H