#ifndef GAME_H
#define GAME_H

#include "Draw.h"
#include "Map.h"
#include "Player.h"

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
	std::vector<Player> _players;
	Player* _localPlayer;

	static const int _sleepTimeInMs = 50;
	bool _gameOver = false;

public:
	Game(HWND);
	~Game() {};

	void Run();
	void DrawScreen();

	int GetSleepTimeInMs();
	bool GetGameOver();
	void InitGame();
	void SetPlayerKeyDown(Game::PlayerControl, bool);

private:
	Draw* GetDraw();
};

#endif // !GAME_H